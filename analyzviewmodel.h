#ifndef ANALYZVIEWMODEL_H
#define ANALYZVIEWMODEL_H

#include <QAbstractListModel>
#include "refineddata.h"

class AnalyzViewModel : public QAbstractListModel
{
    enum MyRoles {
        AmazonBarcode = 0,
        AmazonTitle,
        ListPrice,
        NetPrice,
        AmazonPrice,
        AmazonRank,
        Cargo_Cost,
        Amazon_Commission,
        Total_Cost,
        Net_Profit,
        ProfitRate
        };

public:
    AnalyzViewModel();

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray>  roleNames() const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    void giveModelData(const std::vector<RefinedData> data);



private:
    std::vector<RefinedData> mData;
    QHash<int,QByteArray> mRoles;




};

#endif // ANALYZVIEWMODEL_H
