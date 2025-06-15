#ifndef BOTCREATOR_H
#define BOTCREATOR_H

#include <stdlib.h>

#define MAX_ACCOUNTS 5
#define TWITTER_SIGNUP_URL "https://twitter.com/i/flow/signup"
#define TWITTER_THREAD_URL "https://twitter.com/username/status/thread_id"

// Structure to store account credentials
struct Account {
    char username[50];
    char email[50];
    char password[50];
    char session_token[100]; // Placeholder for session/auth token
};

void createAccount(struct Account *account, int index);

#endif
