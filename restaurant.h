#ifndef RESTAURANT_H
#define RESTAURANT_H



typedef struct ITEM
{
    char item[50];
    float price;
    int quantity;
} ITEM;

typedef struct orders
{
    char customer_name[50];
    char customer_phone[15];
    char date[50];
    char time[50];
    int number_of_items;
    ITEM ordered_items[10];
    float total;
}ORDERS;


int generate_invoice(ORDERS *);
void show_all_invoices(ORDERS *);
int search_invoice(ORDERS *);
void delete_invoice(ORDERS *);
int exit_program(ORDERS *);

#endif // RESTAURANT_H