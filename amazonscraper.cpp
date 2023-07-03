#include "amazonscraper.h"

#include <iostream>
#include <string>
#include <QDebug>


std::string AmazonScraper::mLastResponse = "";

// Callback fonksiyonu, CURL'ün verileri almasını ve depolamasını sağlar
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


ProductInfo AmazonScraper::scrapeProduct(const std::string &barcode)
{
    std::string url = "https://www.amazon.com.tr/s?k=" + barcode;
    mLastResponse = "";

    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,false);
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST ,false);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mLastResponse);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    ProductInfo info;
    info.id      = QString::fromStdString(barcode);
    info.price   =  QString::fromStdString( price()).replace(".","").replace(",",".");
    info.rating  =  QString::fromStdString( rating());
    info.reviews =  QString::fromStdString( reviews());
    info.title   =  QString::fromStdString( title());
    return info;
}

std::string AmazonScraper::price()
{
    static std::string priceStartTag = "<span class=\"a-offscreen\">";
    static std::string priceEndTag = "TL</span>";


    std::size_t start = mLastResponse.find(priceStartTag);
    std::size_t end = mLastResponse.find(priceEndTag, start + priceStartTag.length());

    if (start != std::string::npos &&
        end   != std::string::npos) {
        return mLastResponse.substr(start + priceStartTag.length(), end - start - priceStartTag.length());
    }

    return "NaN";
}

std::string AmazonScraper::rating()
{
    std::string ratingStartTag = "<span class=\"a-icon-alt\">5 yıldız üzerinden";
    std::string ratingEndTag = "</span>";
    std::size_t start = mLastResponse.find(ratingStartTag);
    std::size_t end = mLastResponse.find(ratingEndTag, start + ratingStartTag.length());

    if (start != std::string::npos && end != std::string::npos) {
        return mLastResponse.substr(start + ratingStartTag.length(), end - start - ratingStartTag.length());
    }
    return "NaN";
}

std::string AmazonScraper::title()
{
    std::string nameStartTag = "a-size-base-plus a-color-base a-text-normal\">";
    std::string nameEndTag = "</span";
    std::size_t start = mLastResponse.find(nameStartTag);
    std::size_t end = mLastResponse.find(nameEndTag, start + nameStartTag.length());

    if (start != std::string::npos && end != std::string::npos) {
        return mLastResponse.substr(start + nameStartTag.length(), end - start - nameStartTag.length());
    }

    return "NaN";
}

std::string AmazonScraper::reviews()
{
    std::string nameStartTag = "</i></a></span> </span><span aria-label=\"";
    std::string nameEndTag = "\">";
    std::size_t start = mLastResponse.find(nameStartTag);
    std::size_t end = mLastResponse.find(nameEndTag, start + nameStartTag.length());


    if (start != std::string::npos && end != std::string::npos) {
        return mLastResponse.substr(start + nameStartTag.length(), end - start - nameStartTag.length());
    }

    return "NaN";
}
