#include "exportcontroller.h"
#include "xlsxdocument.h"
#include <QDebug>



void ExportController::onExportRequest(const std::vector<RefinedData> &data,const QString& path)
{
    QXlsx::Document xlsxW;



    static constexpr int tBarcodeColumn{1};
    static constexpr int tNameColumn{2};
    static constexpr int tListPriceColumn{3};
    static constexpr int tNetPriceColumn{4};
    static constexpr int tAmazonPriceColumn{5};
    static constexpr int tRankColumn{6};
    static constexpr int tCargoColumn{7};
    static constexpr int tCommissionColumn{8};
    static constexpr int tTotalCostColumn{9};
    static constexpr int tNetProfitColumn{10};
    static constexpr int tProfitRateColumn{11};

    static int counter = 0;
    counter = 1;

    QXlsx::Format headerFormat;
    headerFormat.setFontBold(true);
    headerFormat.setFontColor(QColor(0,0,0));
    headerFormat.setBorderColor(QColor(0,0,0));
    headerFormat.setBorderStyle(QXlsx::Format::BorderThin);
    headerFormat.setPatternBackgroundColor(QColor(200,200,200));

    headerFormat.setFillPattern(QXlsx::Format::PatternSolid);


    QXlsx::Format dataFormat;
    dataFormat.setBorderColor(QColor(0,0,0));
    dataFormat.setBorderStyle(QXlsx::Format::BorderThin);



    xlsxW.write(counter, tBarcodeColumn, "Barkod",headerFormat);
    xlsxW.write(counter, tNameColumn, "Kitap",headerFormat);
    xlsxW.write(counter, tListPriceColumn, "Liste Fiyatı",headerFormat);
    xlsxW.write(counter, tNetPriceColumn, "Net Fiyat",headerFormat);
    xlsxW.write(counter, tAmazonPriceColumn, "Amazon Fiyatı",headerFormat);
    xlsxW.write(counter, tRankColumn, "Sıralama",headerFormat);
    xlsxW.write(counter, tCargoColumn, "Kargo",headerFormat);
    xlsxW.write(counter, tCommissionColumn, "Amazon Komisyon",headerFormat);
    xlsxW.write(counter, tTotalCostColumn, "Toplam Maliyet",headerFormat);
    xlsxW.write(counter, tNetProfitColumn, "Kar",headerFormat);
    xlsxW.write(counter, tProfitRateColumn, "Kar Oranı",headerFormat);

    counter++;




    for(const auto& val : data )
    {
        xlsxW.write(counter, tBarcodeColumn, val.info.id,dataFormat);
        xlsxW.write(counter, tNameColumn, val.info.title,dataFormat);
        xlsxW.write(counter, tListPriceColumn, val.list_price,dataFormat);
        xlsxW.write(counter, tNetPriceColumn, val.net_price,dataFormat);
        xlsxW.write(counter, tAmazonPriceColumn, val.info.price,dataFormat);
        xlsxW.write(counter, tRankColumn, val.rank,dataFormat);
        xlsxW.write(counter, tCargoColumn, val.transfer_cost,dataFormat);
        xlsxW.write(counter, tCommissionColumn, val.amazon_commission,dataFormat);
        xlsxW.write(counter, tTotalCostColumn, val.total_cost,dataFormat);
        xlsxW.write(counter, tNetProfitColumn, val.profit,dataFormat);
        xlsxW.write(counter, tProfitRateColumn, val.profitRate,dataFormat);

        counter++;

    }

    xlsxW.autosizeColumnWidth(tBarcodeColumn, tProfitRateColumn);

    if ( xlsxW.saveAs(path) ) // save the document as 'Test.xlsx'
    {
        qDebug() << "[debug] success to write xlsx file";
    }
    else
    {
        qDebug() << "[debug][error] failed to write xlsx file";
    }
}
