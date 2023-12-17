#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "auth.h"
#include "item.h"
#include "helper.h"

void display_header(char title[255])
{
    printf("\n");
    printf("====================================================\n");
    printf("%s\n", title);
    printf("====================================================\n");
}

void display_login()
{
    display_header("Selamat Datang Koperasi ITTS");

    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Keluar\n");

    printf("Masukkan pilihan: ");
}

void display_menu(char user_name[255])
{
    char title[255] = "Selamat Datang ";
    strcat(title, user_name);
    strcat(title, " di Koperasi ITTS");

    display_header(title);

    printf("1. Input data koperasi\n");
    printf("2. Data koperasi\n");
    printf("3. Search data koperasi\n");
    printf("4. Sort data koperasi\n");
    printf("5. Keluar\n");

    printf("Masukkan pilihan: ");
}

int main()
{

    // Start of Init Items Table
    FILE *items_table;
    open_database_table("items", &items_table);

    struct Item items[MAX_ITEMS];
    int current_item_row = 0;

    load_items(items_table, items, &current_item_row);
    // End of Init Items Table

    // Start of Init Items Table
    FILE *users_table;
    open_database_table("users", &users_table);

    struct User users[MAX_USERS];
    int current_user_row = 0;

    load_users(users_table, users, &current_user_row);
    // End of Init Items Table

    struct User current_logged_in_user;

    int answer;
    while (1)
    {
        display_login();
        scanf("%i", &answer);

        int is_login_success, is_register_success;
        switch (answer)
        {
        case 1:
            is_register_success = do_user_register(users_table, users, &current_user_row);
            if (is_register_success)
            {
                display_header("Selamat registrasi berhasil");
                break;
            }
            break;

        case 2:
            is_login_success = do_user_login(users, &current_user_row, &current_logged_in_user);
            if (is_login_success)
            {
                display_header("Selamat login berhasil");
                break;
            }
            break;

        case 3:
            fclose(users_table);
            // fclose(items_table);
            return 0;

        default:
            printf("Input tidak valid\n");
            break;
        }

        if (is_login_success)
            break;
    }

    while (1)
    {
        display_menu(current_logged_in_user.name);
        scanf("%i", &answer);

        switch (answer)
        {
        case 1:
            do_add_item(items_table, items, &current_item_row);
            break;

        case 2:
            display_header("Data Koperasi ITTS");
            do_display_item(current_item_row, items);
            break;

        case 3:
            display_header("Search Data Koperasi ITTS");
            do_search_item_by_price(items, current_item_row);
            break;

        case 4:
            do_sort(items, current_item_row);
            break;

        case 5:
            fclose(users_table);
            fclose(items_table);
            return 0;

        default:
            printf("Input tidak valid\n");
            break;
        }
    }

    fclose(users_table);
    fclose(items_table);

    return 0;
}