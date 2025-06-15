#include <stdlib.h>

#include "botCreator.h"

int main() {
    struct Account accounts[MAX_ACCOUNTS];
    int i;

    for (i = 0; i < MAX_ACCOUNTS; i++) {
        createAccount(&accounts[i], i);
    }

    return 0;
}
