/*
 * Brendan McLaughlin, 2025
 *
 * This is designed to spin up accounts to crawl across Twitter
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

#include "botCreator.h"
#include "getUrlData.h"

#define MAX_ACCOUNTS 5
#define TWITTER_SIGNUP_URL "https://twitter.com/i/flow/signup"
#define TWITTER_THREAD_URL "https://twitter.com/username/status/thread_id"

// Create a new Twitter account (simplified, no CAPTCHA)
void createAccount(struct Account *account, int index) {
    CURL *curl;
    CURLcode res;
    struct CURLResponse response = {0};
    response.html = malloc(1);
    response.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Generate fake credentials
        snprintf(account->username, sizeof(account->username), "research_bot%d", index);
        snprintf(account->email, sizeof(account->email), "research%d@example.com", index);
        snprintf(account->password, sizeof(account->password), "SecurePass%d!", index);

        // Prepare POST data (simplified, real form requires more fields and CAPTCHA)
        char post_data[256];
        snprintf(post_data, sizeof(post_data),
                 "user[username]=%s&user[email]=%s&user[password]=%s",
                 account->username, account->email, account->password);

        curl_easy_setopt(curl, CURLOPT_URL, TWITTER_SIGNUP_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteHTMLCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Account creation failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Account created: %s, %s, %s\n", account->username, account->email, account->password);
            // Note: Real implementation needs to parse response for session token
            strcpy(account->session_token, "dummy_token"); // Placeholder
        }

        curl_easy_cleanup(curl);
        free(response.html);
    }
    curl_global_cleanup();
}
