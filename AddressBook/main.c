#include <stdio.h>
#include "contact.h"
#include <ctype.h>

int main() {
    int choice,sortCriteria;
    int match[30];
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Delete contact\n");
        printf("4. Edit contact\n");
        printf("5. Display contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!isdigit(choice) && (choice < 1 || choice > 7)) 
        { // Check if input is not an integer
            printf("Invalid choice. Please enter a digit between 1 and 7.\n");
            while (getchar() != '\n'); 
            continue; 
        }

        
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                deleteContact(&addressBook);
                break;
            case 4:
                editContact(&addressBook);
                break;
            case 5:
                printf("Enter the sorting criteria\n: 1. Name 2. Phone 3. Email\n");
                scanf("%d",&sortCriteria);          
                if (!isdigit(sortCriteria) &&(sortCriteria < 1 || sortCriteria > 3)) 
                { // Check if input is not an integer
                    printf("Invalid Criteria. Please enter a digit between 1 and 3.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }
                listContacts(&addressBook, sortCriteria);
                
                break;
            case 6:
                saveContactsToFile(&addressBook);
                printf("Saving...\n");
                break;
            case 7:
            printf("Exiting...\n");
            break;
            default:
                printf("Invalid choice. Please try again.\n");
                
        }
    } while (choice != 7);
    
       return 0;
}
