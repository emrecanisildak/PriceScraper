#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <QObject>
#include "amazonscraper.h"
#include "xmlreader.h"
#include "refineddata.h"
#include "analyzeprogressstatitics.h"
#include "analyzeparameters.h"

class QTimer;

enum class AnalzeStatus
{
    IDLE = 0,
    ANALYZE = 2,
};

class DataBuilder : public QObject
{
    Q_OBJECT
public:
    explicit DataBuilder(QObject* parent = nullptr);
    ~DataBuilder();
    void init();

signals:
    void analyzeFinished(const std::vector<RefinedData>& refinedData);
    void goingStatics(int total, int current);
    void logOccured(const QString& log);

public slots:
    void onStartAnalyzeRequest(const QString& filePath, const AnalyzeParameter& parameter);
    void onFinishRequest();
    void onAnalyzeProcess();

private:
    int                  mCounter;
    int                  mInvalidOperation;
    int                  mTotalSize;
    std::vector<QString> mUnanalyzableList;


    AnalzeStatus         mStatus;
    QTimer*              mTimer;
    std::vector<QString> mProductIdList;
    std::vector<QString> mPriceList;

    std::vector<RefinedData> mRefinedData;
    TimeInfo                 mTimeInfo;
    AmazonScraper            mScraper;
    XMLReader                mExcellReader;
    AnalyzeParameter         mAnalyzeParameter;

    static constexpr int tStockIdColumn    = 1;
    static constexpr int tStockPriceColumn = 2;

    bool    refineData(const ProductInfo& amazonInfo, const QString& cost);
};

#endif // DATABUILDER_H
