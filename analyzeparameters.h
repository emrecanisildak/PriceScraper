#ifndef ANALYZEPARAMETERS_H
#define ANALYZEPARAMETERS_H

#include <QMetaType>

struct AnalyzeParameter{
    double discount;
    int transportation_cost;
    double amazon_share;
    int additional_cost;
};
Q_DECLARE_METATYPE(AnalyzeParameter)

#endif // ANALYZEPARAMETERS_H
