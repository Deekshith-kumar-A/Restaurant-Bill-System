#include <stdio.h>
#include "restaurant.h"
#include <string.h>
#include <stdlib.h>

int main()
{
    int option;
    ORDERS order;

    char flag = 'y';
    while(flag == 'y')
    {
    //dashboard
    printf("\n\n");
    printf("\033[1;33m\n==============  FRNDS. RESTAURANT  ==============\n");
    printf("\t\t*****************\n\033[0m");
    printf("\033[1;35m\nPlease Select Your Prefered Option :  \n\033[0m");
    printf("\033[1;36m\n1. Generate Invoice");
    printf("\n2. Show all Invoices");
    printf("\n3. Search Invoice");
    printf("\n4. Delete Invoice");
    printf("\n5. Exit\033[0m");

    printf("\033[1;35m\n\nEnter your choice: \033[0m");
    scanf("%d", &option);
    getchar(); // to consume the newline character left by scanf

    //printf("\nYou have selected option %d", option);

    switch(option)
    {
        case 1:
            generate_invoice(&order);
            break;
        case 2:
            show_all_invoices(&order);
            break;
        case 3:
            search_invoice(&order);
            break;
        case 4:
            delete_invoice(&order);
            break;
        case 5:
            exit_program(&order);
            break;
        default:
            printf("\n\tSorry Invalid Option. Please Try Again!!");
            break;
    }

    printf("\033[1;36m\nDo you want to perform another operation? (y/n): \033[0m");
    scanf(" %c", &flag);
}


    printf("\n\n");
    return 0;
}