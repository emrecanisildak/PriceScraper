#include "databuilder.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QTimer>


DataBuilder::DataBuilder(QObject *parent):
    QObject(parent),
    mCounter{0},
    mInvalidOperation{0},
    mStatus{AnalzeStatus::IDLE}
{
}

DataBuilder::~DataBuilder()
{
    qDebug()<<"Data builder destruction";
    mTimer->deleteLater();
}

void DataBuilder::init()
{
    mTimer = new QTimer;
    connect(mTimer,&QTimer::timeout,this,&DataBuilder::onAnalyzeProcess);

}

void DataBuilder::onFinishRequest()
{
    mStatus = AnalzeStatus::IDLE;
}

void DataBuilder::onAnalyzeProcess()
{
    // Analyze..
    if(mStatus == AnalzeStatus::IDLE)
    {
        qDebug()<<"Analiz bitiriliyor kullanici durdurma istegi geldi..";
        emit analyzeFinished(mRefinedData);
        mTimer->stop();
    }
    else
    {
        // Eğer liste boş ve kalmadıysa elemant
        if(mProductIdList.empty())
        {
            qDebug()<<"Ürün listesi bitti analiz bitiriliyor..";

            mStatus = AnalzeStatus::IDLE;
            mTimer->stop();
            emit analyzeFinished(mRefinedData);

        }
        else
        {
            auto barcode =  mProductIdList.front();
            auto productInfo = AmazonScraper::scrapeProduct(barcode.toStdString());
            QString price    = "";

            if(mPriceList.size() > mCounter)
            {
                price = mPriceList.at(mCounter);
                price = price.replace(".","").replace(",",".");
            }

            // Refine the data..
            bool isOk = refineData(productInfo,price);

            if(isOk)
            {
                productInfo.print();
               mProductIdList.erase(mProductIdList.begin());
               ++mCounter;
            }
            else
            {
                ++mInvalidOperation;

                // Ürün 2 den fazla kez fiyatı alınamazsa
                if(mInvalidOperation>2)
                {
                    qDebug()<<"Ürün analiz  edilemedi boş listeye ataniyor..";
                    mInvalidOperation = 0;
                    mProductIdList.erase(mProductIdList.begin());
                    ++mCounter;
                    mUnanalyzableList.push_back(barcode);
                }
            }
        }

    }

}


void DataBuilder::onStartAnalyzeRequest(const QString &filePath, const AnalyzeParameter &parameter)
{
    qDebug()<<"Start analyze request"<<filePath;
    mRefinedData.clear();
    mProductIdList.clear();
    mPriceList.clear();

    mAnalyzeParameter = parameter;

    mExcellReader.load(filePath);

    mProductIdList     = mExcellReader.readAllColumnn(tStockIdColumn);
    mPriceList         = mExcellReader.readAllColumnn(tStockPriceColumn);


    qDebug()<<"Toplam liste boyutu: "<<mProductIdList.size();

    for(const auto& barcode : mProductIdList)
    {
        qDebug()<<barcode <<" analiz edilecek.";
    }

    mTimeInfo.reset();
    mTimeInfo.totalProcess = static_cast<int>(mProductIdList.size());

    mStatus = AnalzeStatus::ANALYZE;
    mTimer->start(10);
    mCounter = 0;
    mInvalidOperation = 0;
    mUnanalyzableList.clear();

}

bool DataBuilder::refineData(const ProductInfo &amazonInfo, const QString &cost)
{
    qDebug()<<"Discount : "<<mAnalyzeParameter.discount;
    qDebug()<<"transportation_cost : "<<mAnalyzeParameter.transportation_cost;
    qDebug()<<"amazon_share : "<<mAnalyzeParameter.amazon_share;


    RefinedData data;
    data.rank              = 1;  // TODO

    data.info              = amazonInfo;
    data.list_price        = cost.toDouble();
    data.net_price         = data.list_price - (data.list_price * ( 0.01 * mAnalyzeParameter.discount));
    data.transfer_cost     = mAnalyzeParameter.transportation_cost;
    data.amazon_commission = amazonInfo.price.toDouble() * (mAnalyzeParameter.amazon_share* 0.01);
    data.total_cost        = data.transfer_cost  + data.net_price  + data.amazon_commission;
    data.profit            = amazonInfo.price.toDouble()  - data.total_cost;

    if(data.net_price == 0.0)
        data.profitRate  = -1.0;
    else
        data.profitRate        = data.profit / data.net_price * 100 ;

    data.info.print();
    mRefinedData.push_back(std::move(data));

    return data.isRefinedData();
}
