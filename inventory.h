#ifndef INVENTORY_H
#define INVENTORY_H

struct Item {
    char *name;
    int quantity;
    float price;
};

struct Inventory {
    struct Item **items;
    int size;
    int capacity;
};

struct Item *create_item(const char *name, int quantity, float price);
struct Inventory *create_inventory();
void add_item_to_inventory(struct Inventory *inventory, struct Item *item);
void list_inventory(struct Inventory *inventory);
void free_inventory(struct Inventory *inventory);

#endif