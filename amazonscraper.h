#ifndef AMAZONSCRAPER_H
#define AMAZONSCRAPER_H

#include <curl/curl.h>
#include <productinfo.h>

class AmazonScraper
{
public:
    static ProductInfo     scrapeProduct(const std::string& barcode);
private:
    static std::string mLastResponse;
    static std::string mRankResponse;


    // METHODS..
    static std::string price();
    static std::string rating();
    static std::string title();
    static std::string reviews();
    static std::string url();
    static std::string rank();

};

#endif // AMAZONSCRAPER_H
