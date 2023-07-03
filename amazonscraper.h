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


    // METHODS..
    static std::string price();
    static std::string rating();
    static std::string title();
    static std::string reviews();
};

#endif // AMAZONSCRAPER_H
