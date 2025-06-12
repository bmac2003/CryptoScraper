#ifndef SCRAPER_H
#define SCRAPER_H

#include <stdlib.h>
#include <curl/curl.h>

struct CURLResponse {
    char *html;
    size_t size;
};

size_t WriteHTMLCallback(void *contents, size_t size, size_t nmemb, void *userp);
struct CURLResponse GetRequest(CURL *curl_handle, const char *url);

#endif
