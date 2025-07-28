#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item *create_item(const char *name, int quantity, float price) {
    struct Item *item = malloc(sizeof(struct Item));

    if (item == NULL) {
        perror("malloc failed");
        return NULL;
    }

    item->name = malloc(strlen(name) + 1);

    if (item->name == NULL) {
        perror("malloc failed");
        return NULL;
    }

    strncpy(item->name, name, strlen(name) + 1);
    item->quantity = quantity;
    item->price = price;

    return item;
}

struct Inventory *create_inventory() {
    struct Inventory *inventory = malloc(sizeof(struct Inventory));

    if (inventory == NULL) {
        perror("malloc failed");
        return NULL;
    }

    inventory->size = 0;
    inventory->capacity = 4;

    inventory->items = malloc(sizeof(struct Item *) * inventory->capacity);

    if (inventory->items == NULL) {
        perror("malloc failed");
        free(inventory);
        return NULL;
    }

    return inventory;
}

void add_item_to_inventory(struct Inventory *inventory, struct Item *item) {
    if (inventory->size == inventory->capacity) {
        struct Item **temp_items = realloc(inventory->items, sizeof(struct Item *) * inventory->capacity * 2);

        if (temp_items == NULL) {
            perror("realloc failed");
            return;
        }

        inventory->items = temp_items;
        inventory->capacity *= 2;
    }

    inventory->items[inventory->size] = item;
    inventory->size++;
}

void list_inventory(struct Inventory *inventory) {
    printf("--- INVENTORY (%d Items) ---\n", inventory->size);

    if (!inventory->size) {
        printf("You do not yet have an item in your inventory.\n");
        return;
    }

    for (int i = 0; i < inventory->size; i++) {
        struct Item *item = inventory->items[i];
        printf("Name: %s\nQuantity: %d\nPrice: %.2f\n", item->name, item->quantity, item->price);
    }
}

void free_inventory(struct Inventory *inventory) {
    for (int i = 0; i < inventory->size; i++) {
        free(inventory->items[i]->name);
        free(inventory->items[i]);
    }

    free(inventory->items);
    free(inventory);
}