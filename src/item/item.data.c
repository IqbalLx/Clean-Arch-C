#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "entity.h"

void load_items(FILE *items_table, struct Item *items, int *current_item_row)
{
    char row[255];
    int row_index = 0;
    while (fgets(row, sizeof(row), items_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                items[*current_item_row].id = atoi(value);
                break;

            case 1:
                strncpy(items[*current_item_row].name, value, sizeof(items[*current_item_row].name) - 1);
                items[*current_item_row].name[sizeof(items[*current_item_row].name) - 1] = '\0';
                break;

            case 2:
                items[*current_item_row].price = atoi(value);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        (*current_item_row)++;
        row_index++;
    }
}

void add_item(FILE *items_table, struct Item *items, int *current_item_row, char item_name[255], int item_price)
{
    items[*current_item_row].id = *current_item_row + 1;

    strncpy(items[*current_item_row].name, item_name, sizeof(items[*current_item_row].name) - 1);
    items[*current_item_row].name[sizeof(items[*current_item_row].name) - 1] = '\0';

    items[*current_item_row].price = item_price;

    fprintf(items_table, "\n%d,%s,%d", items[*current_item_row].id, items[*current_item_row].name, items[*current_item_row].price);

    (*current_item_row)++;
}

struct SearchResult search_item_by_price(struct Item *items, int current_item_row, int target_price, int limit)
{
    struct Item *found_items = (struct Item *)malloc(limit * sizeof(struct Item));
    if (found_items == NULL)
    {
        // Handle allocation failure
        struct SearchResult result = {NULL, 0};
        return result;
    }

    int found_index = 0;
    for (int i = 0; i < current_item_row; i++)
    {
        if (found_index > limit - 1)
            break;

        if (items[i].price >= target_price)
        {
            found_items[found_index] = items[i];
            found_index++;
        }
    };

    struct SearchResult result =
        {
            .items = found_items,
            .size = found_index + 1,
        };

    return result;
}

void sort_by_price(struct Item *items, int current_item_row, int is_ascending)
{
    for (int i = 0; i < current_item_row - 1; i++)
    {
        for (int j = 0; j < current_item_row - i - 1; j++)
        {
            if ((items[j].price > items[j + 1].price) && is_ascending)
            {
                struct Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
            else if ((items[j].price < items[j + 1].price) && !is_ascending)
            {
                struct Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}
