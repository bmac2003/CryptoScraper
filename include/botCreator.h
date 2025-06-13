#ifndef SCRAPER_H
#define SCRAPER_H

#include <stdlib.h>

// Structure to store account credentials
struct Account {
    char username[50];
    char email[50];
    char password[50];
    char session_token[100]; // Placeholder for session/auth token
};

#endif
