#ifndef ITEM_HEADER
#define ITEM_HEADER

struct SearchResult
{
    struct Item *items;
    int size;
};

// data
void load_items(FILE *items_table, struct Item *items, int *current_item_row);
void add_item(FILE *items_table, struct Item *items, int *current_item_row, char item_name[255], int item_price);
struct SearchResult search_item_by_price(struct Item *items, int current_item_row, int target_price, int limit);
void sort_by_price(struct Item *items, int current_item_row, int is_ascending);

// service
void do_display_item(int current_item_row, struct Item *items);
void do_add_item(FILE *items_table, struct Item *items, int *current_item_row);
void do_search_item_by_price(struct Item *items, int current_item_row);
void do_sort(struct Item *items, int current_item_row);

#endif