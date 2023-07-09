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
        reviews{"NaN"},
        rank{"NaN"},
        url{"NaN"}
    {

    }

    ProductInfo(const QString& pTitle,const QString& pPrice,
                const QString& pRating,const QString& pReview,const QString& pRank, const QString& pURL):
        title{pTitle},
        price{pPrice},
        rating{pRating},
        reviews{pReview},
        rank{pRank},
        url{pURL}
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
        qDebug()<<"rank: "<<rank;
        qDebug()<<"url: "<<url;
    }
    QString id;
    QString title;
    QString price;
    QString rating;
    QString reviews;
    QString rank;
    QString url;


};


#endif // PRODUCTINFO_H
