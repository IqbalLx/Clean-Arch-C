#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "item.h"

void do_display_item(int current_item_row, struct Item *items)
{
    printf("ID\t\tNama\t\tHarga\n");
    for (int i = 0; i < current_item_row; i++)
    {
        printf("%d\t\t%s\t\t%d\n", items[i].id, items[i].name, items[i].price);
    };
}

void do_add_item(FILE *items_table, struct Item *items, int *current_item_row)
{
    if (*current_item_row == (MAX_ITEMS - 1))
    {
        printf("Tidak bisa menambah item lagi\n");
        return;
    }

    char item_name[255];
    int item_price;

    printf("Masukkan Nama Produk: ");
    scanf("%s", &item_name);

    printf("Masukkan Harga Produk: ");
    scanf("%i", &item_price);

    add_item(items_table, items, current_item_row, item_name, item_price);
}

void do_search_item_by_price(struct Item *items, int current_item_row)
{
    int target_price, limit;

    printf("Masukkan Harga Produk: ");
    scanf("%d", &target_price);

    printf("Masukkan Batas Data: ");
    scanf("%d", &limit);

    struct SearchResult found_items = search_item_by_price(items, current_item_row, target_price, limit);

    printf("ID\t\tNama\t\tHarga\n");
    for (int i = 0; i < found_items.size && i < limit; i++)
    {
        printf("%d\t\t%s\t\t%d\n", found_items.items->id, found_items.items->name, found_items.items->price);
        found_items.items++;
    };
}

void do_sort(struct Item *items, int current_item_row)
{
    sort_by_price(items, current_item_row, 1);

    return do_display_item(current_item_row, items);
};