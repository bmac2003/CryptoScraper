#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getUrlData.h"

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
