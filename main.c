#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"

int main() {
    struct Inventory *inventory = create_inventory();

    if (inventory == NULL) {
        perror("create_inventory failed");
        return 1;
    }

    while (1) {
        char user_input[100];
        fgets(user_input, 100, stdin);
        user_input[strcspn(user_input, "\n")] = 0;

        char *command = strtok(user_input, " ");

        if (command == NULL) {
            printf("Invalid input.\n");
            continue;
        }

        if (!strcmp(command, "exit")) {
            break;

        } else if (!strcmp(command, "list")) {
            list_inventory(inventory);

        } else if (!strcmp(command, "add")) {
            char *name = strtok(NULL, " ");
            char *quantity_str = strtok(NULL, " ");
            char *price_str = strtok(NULL, " ");

            if (name == NULL || quantity_str == NULL || price_str == NULL) {
                printf("Invalid input.\n");
                continue;
            }

            int quantity = atoi(quantity_str);
            float price = atof(price_str);

            struct Item *item = create_item(name, quantity, price);
            add_item_to_inventory(inventory, item);

        } else {
            printf("Invalid input.\n");
        }
    }

    free_inventory(inventory);

    return 0;
}
