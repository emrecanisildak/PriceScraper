#ifndef REFINEDDATA_H
#define REFINEDDATA_H

#include "productinfo.h"

struct RefinedData
{
    ProductInfo info;

    bool isRefinedData()
    {
        return info.id != "NaN" && info.price != "NaN";
    }

    double      list_price;
    double      net_price; // iskonto düşmüş hali
    int         rank;
    int         transfer_cost;
    double      amazon_commission;
    double      total_cost;  // kargo + amazon_commission + net_price
    double      profit;
    double      profitRate;
};

#endif // REFINEDDATA_H
