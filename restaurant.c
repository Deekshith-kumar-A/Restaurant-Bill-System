#include "restaurant.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Name validation
int is_name_valid(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) // if(isalpha(name[i]) == 0 || name[i] == ' ')

        {
            return 0; // Invalid character found
        }
    }
    return 1; // All characters are valid
}

// valid mobile number

int is_valid_mobile(const char *mobile)
{
    int length = strlen(mobile);
    if (length != 10)
    {
        return 0; // Mobile number must be exactly 10 digits
    }
    for (int i = 0; i < length; i++)
    {
        if (mobile[i] < '0' || mobile[i] > '9') // if (!isdigit((unsigned char)mobile[i])) // from <ctype.h>
            return 0;
    }
    return 1; // Valid mobile number
}

// Function to generate bill header
void generate_bill_header(char name[50], char date[50], char phone[15])
{
    printf("\n\n");
    printf("     \033[1;33m======== FRNDS. RESTAURANT ========\033[0m\n");
    printf("\t      \033[1;33m*****************\033[0m\n");
    printf("\033[1;36mName  :  %-15s\tPhone :  %s\033[0m\n", name, phone);
    printf("\033[1;36mDate  :  %-15s\tTime  :  %s\033[0m\n", __DATE__, __TIME__);
    // printf("\n");
    

        printf("===================================================\n");
    printf("\033[1;33m%-17s %-10s %-10s %-10s\n\033[0m", "Item", "Qty", "Price", "Total");
    printf("===================================================\n");
    // printf("\n\n");
}

// Function to generate bill body
void generate_bill_body(char item[50], float price, int quantity)
{
    printf("\033[1;35m%-17s %-10d %-10.2f %-10.2f\n\033[0m", item, quantity, price, price * quantity);
    // printf("\n");
}

// Function to generate bill footer
void generate_bill_footer(float total)
{
     // Apply automatic discount
    float discount_percent = 0.0;
    if (total > 1000)
        discount_percent = 10.0;
    else if (total > 500)
        discount_percent = 5.0;

    float discount = (discount_percent / 100.0) * total;
    float discounted_total = total - discount;

    // Apply taxes
    float cgst = 0.09 * discounted_total;
    float sgst = 0.09 * discounted_total;
    float grand_total = discounted_total + cgst + sgst;

    //float discount = 0.1 * total; // 10% discount
    //float net_total = total - discount;
    //float cgst = 0.09 * net_total; // 9% CGST
    //float sgst = 0.09 * net_total; // 9% SGST
    //float grand_total = net_total + cgst + sgst;
    printf("---------------------------------------------------\n");
    printf("\033[1;34mTotal:\t\t\t\t\t%.2f\n\033[0m", total);

    if (discount_percent > 0)
        printf("\033[1;32mDiscount @%.0f%%:\t\t\t\t%.2f\n\033[0m", discount_percent, discount);
    else
        printf("\033[1;32mDiscount @0%%:\t\t\t\t0.00\n\033[0m");

    printf("---------------------------------------------------\n");
    printf("\033[1;34mDiscounted Total:\t\t\t%.2f\n\033[0m", discounted_total);
    printf("\033[1;31mCGST (9%%):\t\t\t\t%.2f\n", cgst);
    printf("SGST (9%%):\t\t\t\t%.2f\n\033[0m", sgst);
    printf("===================================================\n");
    printf("\033[1;34mGrand Total:\t\t\t\t%.2f\n\033[0m", grand_total);
    printf("===================================================\n");
    printf("\033[1;32m\nThank you for Visiting Frnds. Restaurant!!!\n\033[0m");
    printf("\n\n");
}


//  Function to generate invoice
int generate_invoice(ORDERS *order)
{

    float total = 0.0;
    // system("clear"); // for Linux/Unix

    // customer details -> name
    while (1)
    {
        printf("\033[1;34m\nEnter the name of Customer: \033[0m");
        scanf("%[^\n]", order->customer_name);
        getchar();
        if (!is_name_valid(order->customer_name))
        {
            printf("\033[1;31m\n***Name must contain only alphabets and spaces.***\033[0m\n\n");
            continue;
        }
        else
        {
            break;
        }
    }

    // customer details -> phone
    while (1)
    {
        printf("\033[1;34mEnter the phone number of Customer: \033[0m");
        scanf("%[^\n]", order->customer_phone);
        getchar();

        if (!is_valid_mobile(order->customer_phone))
        {
            printf("\n\033[1;31m***Mobile number must be exactly 10 digits.***\033[0m\n\n");
            continue;
        }
        else
        {
            break;    
        }
    }

    // date
    strcpy(order->date, __DATE__); // current date

    // time
    strcpy(order->time, __TIME__); // current time

    // menu items
    struct ITEM menu[] = {
    // Main Course
    {"Pizza", 150.0, 0},
    {"Burger", 80.0, 0},
    {"Pasta", 120.0, 0},
    {"Sandwich", 60.0, 0},
    {"Noodles", 110.0, 0},
    {"Fried Rice", 140.0, 0},
    {"Tacos", 130.0, 0},
    
    // Starters
    {"Soup", 60.0, 0},
    {"Garlic Bread", 75.0, 0},
    {"Cheese Balls", 95.0, 0},
    {"Paneer Roll", 85.0, 0},
    {"Fries", 70.0, 0},
    {"Momos", 100.0, 0},

    // Beverages
    {"Tea", 30.0, 0},
    {"Coffee", 50.0, 0},
    {"Juice", 40.0, 0},
    {"Milkshake", 90.0, 0},
    {"Soda", 35.0, 0},

    // Desserts
    {"Ice Cream", 90.0, 0},
    {"Brownie", 120.0, 0}
};


    int menu_size = sizeof(menu) / sizeof(menu[0]);

    // display menu
    printf("\n\033[1;33m*************** MENU ***************\033[0m\n");
    for (int i = 0; i < menu_size; i++)
    {
        printf("\033[1;36m%d.  %-12s    ₹%.2f\033[0m\n", i + 1, menu[i].item, menu[i].price);
    }
    // take order
    printf("\n\033[1;34mEnter number of different items you want to order: \033[0m");
    scanf("%d", &order->number_of_items);

    for (int i = 0; i < order->number_of_items; i++)
    {
        int choice;
        printf("\033[1;35m\nEnter item number (1-%d): \033[0m", menu_size);
        scanf("%d", &choice);

        if (choice < 1 || choice > menu_size)
        {
            printf("\033[1;31mInvalid choice! Try again.\033[0m\n");
            i--;
            continue;
        }
        // quantity
        printf("\033[1;35mEnter quantity for %s: \033[0m", menu[choice - 1].item);
        scanf("%d", &menu[choice - 1].quantity);

        // Copy to order list
        strcpy(order->ordered_items[i].item, menu[choice - 1].item);
        order->ordered_items[i].price = menu[choice - 1].price;
        order->ordered_items[i].quantity = menu[choice - 1].quantity;

        total += order->ordered_items[i].price * order->ordered_items[i].quantity;
    }

    // generate bill header
    generate_bill_header(order->customer_name, order->date, order->customer_phone);

    // generate bill body
    for (int i = 0; i < order->number_of_items; i++)
    {
        generate_bill_body(order->ordered_items[i].item, order->ordered_items[i].price, order->ordered_items[i].quantity);
    }

    // generate bill footer
    generate_bill_footer(total);

    // char save_option;
    char save_option;
    printf("\033[1;36m\nDo you want to save the bill?(y/n): \033[0m");
    scanf(" %c", &save_option);

    if (tolower(save_option) == 'y')
    {
        // Save the order to a file
        FILE *fp = fopen("restaurant_bill.txt", "ab");
        if (fp == NULL)
        {
            printf("\033[1;31mError opening file!\n\033[0m");
            return -1;
        }

        fwrite(order, sizeof(ORDERS), 1, fp);
        // fprintf(fp, "----------------------------------------\n");
        fclose(fp);
        printf("\033[1;32m\n\tBill saved successfully!\n\033[0m");
    }
    else
    {
        printf("\033[1;31m\n\tBill not saved.\n\033[0m");
    }
}

// Function to show all invoices
void show_all_invoices(ORDERS *order)
{

    FILE *fp = fopen("restaurant_bill.txt", "rb");
    if (fp == NULL)
    {
        printf("\033[1;31m\n\tNo previous invoices found.\n\033[0m");
        return;
    }
    ORDERS temp_orders;
    int found = 0;
    printf("\033[1;36m\n************** Welcome Previous Invoices ****************\n\033[0m");

    while (fread(&temp_orders, sizeof(ORDERS), 1, fp))
    {
        float total = 0.0;
        // Display each order
        generate_bill_header(temp_orders.customer_name, temp_orders.date, temp_orders.customer_phone);
        for (int i = 0; i < temp_orders.number_of_items; i++)
        {
            generate_bill_body(temp_orders.ordered_items[i].item, temp_orders.ordered_items[i].price, temp_orders.ordered_items[i].quantity);
            total += temp_orders.ordered_items[i].price * temp_orders.ordered_items[i].quantity;
        }
        generate_bill_footer(total);
        found = 1;

        // printf("\n----------------------------------------\n");
        printf("\n");
    }
    if (!found)
    {
        printf("\033[1;31m\n\tNo previous invoices found.\n\033[0m");
    }

    fclose(fp);
}

// Function to search for an invoice by customer name
int search_invoice(ORDERS *order)
{
    printf("\033[1;36m\n************* Welcome Search Invoices *************\n\033[0m");
    char search_name[50];
    float total = 0.0;
    printf("\033[1;34m\nEnter the customer name to search: \033[0m");
    scanf("%[^\n]", search_name);
    getchar();

    FILE *fp = fopen("restaurant_bill.txt", "rb");
    if (fp == NULL)
    {
        printf("\033[1;31m\n\tNo previous invoices found.\n\033[0m");
        return -1;
    }

    ORDERS temp_orders;
    int found = 0;

    printf("\033[1;35m\n     ============= Invoice of : %s ============== \033[0m", search_name);

    while (fread(&temp_orders, sizeof(ORDERS), 1, fp))
    {
        if (strcmp(temp_orders.customer_name, search_name) == 0)
        {
            // Display the found order
            generate_bill_header(temp_orders.customer_name, temp_orders.date, temp_orders.customer_phone);
            for (int i = 0; i < temp_orders.number_of_items; i++)
            {
                generate_bill_body(temp_orders.ordered_items[i].item, temp_orders.ordered_items[i].price, temp_orders.ordered_items[i].quantity);
                total += temp_orders.ordered_items[i].price * temp_orders.ordered_items[i].quantity;
            }
            generate_bill_footer(total);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\033[1;31m\n\tNo invoice found for customer: %s\n\033[0m", search_name);
    }

    fclose(fp);
}

// Function to delete all invoices
void delete_invoice(ORDERS *order)
{

    printf("\033[1;36m\n************* Welcome Delete Invoices *************\n\033[0m");
    char customer_name[50];
    printf("\033[1;34m\n Enter the Customer name to delete the invoice: \033[0m");
    scanf("%[^\n]", customer_name);
    getchar();

    FILE *fp = fopen("restaurant_bill.txt", "rb");
    if (fp == NULL)
    {
        printf("\033[1;31m\n\tNo previous invoices found.\n\033[0m");
        return;
    }

    ORDERS temp_orders;
    int found = 0;

    // Create a temporary file to store remaining invoices
    FILE *temp_fp = fopen("temp.txt", "wb");
    if (temp_fp == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(fp);
        return;
    }

    // Copy all invoices except the one to be deleted
    while (fread(&temp_orders, sizeof(ORDERS), 1, fp))
    {
        if (strcmp(temp_orders.customer_name, customer_name) != 0)
        {
            fwrite(&temp_orders, sizeof(ORDERS), 1, temp_fp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found)
    {
        remove("restaurant_bill.txt");
        rename("temp.txt", "restaurant_bill.txt");
        printf("\033[1;32m\n\tInvoice deleted successfully!\n\033[0m");
    }
    else
    {
        printf("\033[1;31m\n\tNo invoice found for customer: %s\n\033[0m", customer_name);
        remove("temp.txt");
    }
}

// Function to exit the program
int exit_program(ORDERS *order)
{
    printf("\033[1;33m\n\tThank you for using FRNDS. RESTAURANT BYE BYE!!\n\n\033[0m");
    exit(0);
}
