#include "analyzviewmodel.h"

AnalyzViewModel::AnalyzViewModel()
{
//    mRoles[AmazonId] = "id";
//    mRoles[AmazonPrice] = "price";
//    mRoles[AmazonRating] = "rating";
//    mRoles[AmazonReviewvs] = "reviews";
//    mRoles[Cost] = "cost";
//    mRoles[ProfitRate] = "profitRate";
}

int AnalyzViewModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}

QVariant AnalyzViewModel::data(const QModelIndex &index, int role) const
{


    if (role != Qt::DisplayRole)
        return {};

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const auto &item = mData.at(index.row());

    switch (index.column()) {
    case AmazonBarcode:
        return item.info.id;
    case AmazonTitle:
        return item.info.title;
    case ListPrice:
        return item.list_price;
    case NetPrice:
        return item.net_price;
    case AmazonPrice:
        return item.info.price.toDouble();
    case AmazonRank:
        return item.rank;
    case Cargo_Cost:
        return item.transfer_cost;
    case Amazon_Commission:
        return item.amazon_commission;
    case Total_Cost:
        return item.total_cost;
    case Net_Profit:
        return item.profit;
    case ProfitRate:
        return item.profitRate;
        break;
    default:
        return {};
    }

}

QHash<int, QByteArray> AnalyzViewModel::roleNames() const
{
    return mRoles;
}

int AnalyzViewModel::columnCount(const QModelIndex &parent) const
{
    return 11;
}

QVariant AnalyzViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case AmazonBarcode:
                return QString("BARKOD");
            case AmazonTitle:
                return QString("KİTAP");
            case ListPrice:
                return QString("LİSTE FİYATI");
            case NetPrice:
                return QString("NET FİYATI");
            case AmazonPrice:
                return QString("AMAZON FİYATI");
            case AmazonRank:
                return QString("SIRALAMA");
            case Cargo_Cost:
                return QString("KARGO");
            case Amazon_Commission:
                return QString("KOMİSYON");
            case Total_Cost:
                return QString("TOTAL MASRAF");
            case Net_Profit:
                return QString("NET KAR");
            case ProfitRate:
                return QString("ORAN");
            default:
                return {};
            }
        }
    }
    return QVariant();
}

void AnalyzViewModel::giveModelData(const std::vector<RefinedData> data)
{
    beginResetModel();
    mData = data;
    endResetModel();
}
