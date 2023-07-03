#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include <QString>
#include <QDebug>

struct ProductInfo
{
    ProductInfo():
        id{"NaN"},
        title{"NaN"},
        price{"NaN"},
        rating{"NaN"},
        reviews{"NaN"}
    {

    }

    ProductInfo(const QString& pTitle,const QString& pPrice,
                const QString& pRating,const QString& pReview):
        title{pTitle},
        price{pPrice},
        rating{pRating},
        reviews{pReview}
    {

    }

    void print()
    {
        qDebug()<<"\n---------------------------------";
        qDebug()<<"Id: "<<id;
        qDebug()<<"Title: "<<title;
        qDebug()<<"price: "<<price;
        qDebug()<<"rating: "<<rating;
        qDebug()<<"reviews: "<<reviews;
    }
    QString id;
    QString title;
    QString price;
    QString rating;
    QString reviews;


};


#endif // PRODUCTINFO_H
