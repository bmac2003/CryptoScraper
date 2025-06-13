/*
 * Brendan McLaughlin, 2025
 *
 * This was mostly copied from this website: https://www.zenrows.com/blog/web-scraping-c#get-the-html
 *
 * Modifications were then made to adapt this to my project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

#include "getUrlData.h"

size_t WriteHTMLCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct CURLResponse *mem = (struct CURLResponse *)userp;
    char *ptr = realloc(mem->html, mem->size + realsize + 1);

    if (!ptr) {
        printf("Not enough memory available (realloc returned NULL)\n");
        return 0;
    }

    mem->html = ptr;
    memcpy(&(mem->html[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->html[mem->size] = 0;

    return realsize;
}

struct CURLResponse GetRequest(CURL *curl_handle, const char *url) {
    CURLcode res;
    struct CURLResponse response;
    
    // Initialize Response
    response.html = malloc(1);
    response.size = 0;

    // Specify the URL to GetRequest
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    // send all data returned by server to WriteHTMLCallback
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteHTMLCallback);
    // pass "response" to the callback function
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&response);
    // set a User-Agent header
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36");
    // perform the GET GetRequest
    res = curl_easy_perform(curl_handle);

    // check for HTTP errors
    if (res != CURLE_OK) {
        fprintf(stderr, "GET request failed, %s\n", curl_easy_strerror(res));
    }    

    return response;
}

int main() {
    printf("Hello World!\n");

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_ALL);

    // Initialize a CURL instance
    CURL *curl_handle = curl_easy_init();

    // Retrieve the HTML Document of the target page
    struct CURLResponse response = GetRequest(curl_handle, "https://engineering.purdue.edu/ece264/24sp/");
    // Print the HTML contents
    printf("%s\n", response.html);

    // Cleanup the CURL instance
    curl_easy_cleanup(curl_handle);
    // Cleanup the CURL resources
    curl_global_cleanup();

    return 0;
}
