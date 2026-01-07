#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"
#include <ctype.h>





void initialize(AddressBook *addressBook)
{
	addressBook->contactCount = 0;
	populateAddressBook(addressBook);

	// Load contacts from file during initialization (After files)
	loadContactsFromFile(addressBook);
}
void loadContactsFromFile(AddressBook *addressBook)
{
	FILE*fptr=fopen("contacts.csv","r");
	fscanf(fptr,"#%d\n",&addressBook->contactCount);
	for(int i=0; i<addressBook->contactCount; i++)
	{
		fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

	}
	fclose(fptr);
	printf("Contacts loaded successfully");

}
void listContacts(AddressBook *addressBook, int sortCriteria)
{
	// Sort contacts based on the chosen criteria
	if(sortCriteria==1)
	{
		for(int i=0; i<addressBook->contactCount; i++)
		{
			for(int j=i+1; j<addressBook->contactCount; j++)
			{
				if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0)
				{
					Contact temp = addressBook->contacts[i];
					addressBook->contacts[i]=addressBook->contacts[j];
					addressBook->contacts[j]=temp;
				}
			}
		}
	}
	else if(sortCriteria==2)
	{
		for(int i=0; i<addressBook->contactCount; i++)
		{
			for(int j=i+1; j<addressBook->contactCount; j++)
			{
				if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)>0)
				{
					Contact temp = addressBook->contacts[i];
					addressBook->contacts[i]=addressBook->contacts[j];
					addressBook->contacts[j]=temp;
				}
			}
		}
	}
	else if(sortCriteria==3)
	{
		for(int i=0; i<addressBook->contactCount; i++)
		{
			for(int j=i+1; j<addressBook->contactCount; j++)
			{
				if(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)>0)
				{
					Contact temp = addressBook->contacts[i];
					addressBook->contacts[i]=addressBook->contacts[j];
					addressBook->contacts[j]=temp;
				}
			}
		}
	}
	// Display contacts
	for(int i=0; i<addressBook->contactCount; i++)
	{
		printf("Name: %-10s",addressBook->contacts[i].name);
		printf("\t\tPhone: %-10s\t",addressBook->contacts[i].phone);
		printf("\t\temail: %-10s\t",addressBook->contacts[i].email);
		printf("\n");
	}


}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	char Name[30],phone[15],email[30];
	printf("Enter Name: ");
	scanf("%s",Name);
	// updating into structure member
	strcpy(addressBook -> contacts[addressBook -> contactCount].name,Name);

	int valid =0,found=0;
	int exit_option;
	while(1)
	{
		printf("Enter Phone Number: ");
		scanf("%s",phone);
		// checking if phone length ia 10 or not
		if(strlen(phone) == 10)
		{
			valid=1;
			//check if all are digits

			for(int i=0; i<10; i++)
			{
				if(!isdigit(phone[i]))
				{
					valid=0;
					break;
				}
			}
			if(valid)
			{
				//check if number already exist /not in  contact list
				found=0;
				for(int j=0; j<addressBook->contactCount; j++)
				{
					if(strstr(addressBook -> contacts[j].phone,phone)!=NULL)
					{
						//if present re enter number or exit
						found=1;
						break;
					}

				}
				if(found)
				{
					printf("Phone Number already exist.Please check the number\n");
					printf("For re-enter press 1 or for exit press 0\n");
					scanf("%d",&exit_option);
					if(exit_option==0)
					{
						return;
					}
					continue;
				}
				break;
			}
		}

		else
		{
			//re-enter or exit
			printf("Invalid Phone Number.Number should be 10 digits\n");
			printf("For re-enter press 1 or for exit press 0\n");
			scanf("%d",&exit_option);
			if(exit_option==0)
			{
				return;
			}
			continue;

		}
		if(!valid)
		{
			printf("Invalid Phone Number\n");
			printf("For re-enter press 1 or for exit press 0\n");
			scanf("%d",&exit_option);
			if(exit_option==0)
			{
				return;
			}
			continue;

		}

	}

	strcpy(addressBook->contacts[addressBook->contactCount].phone,phone) ;
	//proceed with reading email

	// checking validity of email
	int emailValid=0;
	while(!emailValid)
	{
		printf("Enter email: ");
		scanf("%s",email);

		if(email[0]!='@')
		{
			if(strstr(email,"@" )&& strstr(email,".com"))
			{
				//check ifthere is some word in between @ and .com only then email is valid
				char *ptr1=strstr(email,"@");
				char *ptr2=strstr(email,".com");

				if(ptr1+1<ptr2)
				{
					//update contact list
					if (*(ptr2 + 4) != '\0') // 4 is the length of ".com"
					{
						printf("Invalid email. Email should not have characters after .com\n");
						printf("For re-enter press 1 or for exit press 0\n");
						scanf("%d", &exit_option);
						getchar(); // Consume the newline character left in the input buffer
						if (exit_option == 0)
						{
							return;
						}
						continue;
					}
					emailValid=1;
					break;
				}
				else
				{
					emailValid=0;
					printf("Invalid email.email should have  word between @ and .com\n");
					printf("For re-enter press 1 or for exit press 0\n");
					scanf("%d",&exit_option);
					if(exit_option==0)
					{
						return;
					}
					continue;

				}
			}
			else
			{
				emailValid=0;
				printf("Invalid email.email should have @ and .com\n");
				printf("For re-enter press 1 or for exit press 0\n");
				scanf("%d",&exit_option);
				if(exit_option==0)
				{
					return;
				}
				continue;
			}
		}
		else
		{
			printf("Invalid email\n");
			continue;
		}

	}



	strcpy(addressBook->contacts[addressBook->contactCount].email,email);
	addressBook->contactCount++;
	printf("Contact added successfully\n");
	saveContactsToFile(addressBook);

}

void searchContact(AddressBook *addressBook)
{
	/* Define the logic for search */
	int option;
	printf("Enter option to search contact:\n");
	printf("1. by name\n");
	printf("2. by mobile\n");
	printf("3. by email\n");
	scanf("%d",&option);
	
	if (!isdigit(option) &&(option < 1 || option > 3)) 
    { // Check if input is not an integer
        printf("Invalid option. Please enter a digit between 1 and 3.\n");
        while (getchar() != '\n');  
		return;
    }
	char input[30];
	int match[30];
	int matchcount=0;

	printf("Enter input to search: ");
	scanf("%s",input);
	for(int i=0; i<addressBook-> contactCount; i++)
	{
		switch(option)
		{
		case 1:
			if(strstr(addressBook -> contacts[i].name,input)!=NULL)
			{

				match[matchcount++]=i;

			}
			break;

		case 2:
			if(strstr(addressBook -> contacts[i].phone,input)!=NULL)
			{
				match[matchcount++]=i;
			}
			break;
		case 3:
			if(strstr(addressBook -> contacts[i].email,input)!=NULL)
			{
				match[matchcount++]=i;
			}
			break;

		}
	}
	if(matchcount==0)
	{
		printf("Contact not found\n");
		return;
	}
	printf("Matching contacts:\n");
	for (int i = 0; i < matchcount; i++)
	{
		int index = match[i];
		printf("%d. Name: %-10s\t, Phone: %-10s\t, email: %-10s\n", i + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
	}




}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int option;
	char input[30];
	int match[30];
	int matchcount=0;
	printf("Enter option to search contact:\n");
	printf("1. by name\n");
	printf("2. by mobile\n");
	printf("3. by email\n");
	scanf("%d",&option);

	if (!isdigit(option) &&(option < 1 || option > 3)) 
    { // Check if input is not an integer
        printf("Invalid option. Please enter a digit between 1 and 3.\n");
        while (getchar() != '\n');  
		return;
    }
	getchar();

	printf("Enter input to search: ");
	scanf("%s",input);
	for(int i=0; i<addressBook-> contactCount; i++)
	{
		switch(option)
		{
		case 1:
			if(strstr(addressBook -> contacts[i].name,input)!=NULL)
			{

				match[matchcount++]=i;

			}
			break;

		case 2:
			if(strstr(addressBook -> contacts[i].phone,input)!=NULL)
			{
				match[matchcount++]=i;
			}
			break;
		case 3:
			if(strstr(addressBook -> contacts[i].email,input)!=NULL)
			{
				match[matchcount++]=i;
			}
			break;

		}
	}
	if(matchcount==0)
	{
		printf("Contact not found\n");
		return;
	}
	printf("Matching contacts:\n");
	for (int i = 0; i < matchcount; i++)
	{
		int index = match[i];
		printf("%d. Name: %-10s\t, Phone: %-10s\t, email: %-10s\n", i + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
	}
	int index;
	printf("Enter the index of the contact you want to edit: ");
	scanf("%d",&index);
	if(index<1 || index>matchcount)
	{
		printf("Invalid index\n");
		return;
	}
	int actualIndex=match[index-1];
	char New[50];
	int editchoice;
	printf("Select the field to edit:\n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. email\n");
	printf("Enter your choice: ");
	scanf("%d", &editchoice);
	getchar();
	switch(editchoice)
	{
	case 1:
	{
		printf("Enter new name: ");
		scanf("%s",New);
		strcpy(addressBook->contacts[actualIndex].name,New);
	}
	break;
	case 2:
	{
		int validPhone = 0;
		while (!validPhone) {
			printf("Enter new phone: ");
			scanf("%s", New);

			if (strlen(New) == 10)
			{
				validPhone = 1;
				// Check if all characters are digits
				for (int i = 0; i < 10; i++)
				{
					if(!isdigit(New[i]))
					{
						printf("Invalid Phone Number\n");
						validPhone=0;
						break;
					}
				}

				if (validPhone) {
					// Check if phone number already exists
					for (int j = 0; j < addressBook->contactCount; j++) {
						if (strstr(addressBook->contacts[j].phone, New) != NULL) {
							printf("Phone number already exists. Please enter a different number.\n");
							validPhone = 0;
							break;
						}
					}
				}
			} else {
				printf("Phone number must be 10 digits long\n");
			}

			if (!validPhone) {
				printf("For re-enter press 1 or for exit press 0\n");
				int exitOption;
				scanf("%d", &exitOption);
				if (exitOption == 0) {
					return;
				}
			}
		}
		strcpy(addressBook->contacts[actualIndex].phone, New);
		break;
	}
	break;
	case 3:
	{

		int emailValid=0,exit_option;
		while(1)
		{

			printf("Enter new email: ");
			scanf("%s",New);
			if(strstr(New,"@" )&& strstr(New,".com"))
			{
				//check ifthere is some word in between @ and .com only then email is valid
				char *ptr1=strstr(New,"@");
				char *ptr2=strstr(New,".com");
				if(ptr1+1<ptr2)
				{
					//update contact list
					if (*(ptr2 + 4) != '\0') // 4 is the length of ".com"
					{
						printf("Invalid email. Email should not have characters after .com\n");
						printf("For re-enter press 1 or for exit press 0\n");
						scanf("%d", &exit_option);
						getchar(); 
						if (exit_option == 0)
						{
							return;
						}
						continue;
					}
					emailValid=1;
					break;
				}
				else
				{
					emailValid=0;
					printf("Invalid email.email should have  word between @ and .com\n");
					printf("For re-enter press 1 or for exit press 0\n");
					scanf("%d",&exit_option);
					if(exit_option==0)
					{
						return;
					}
					continue;

				}

			}
			else
			{
				emailValid=0;
				printf("Invalid email.email should have @ and .com\n");
				printf("For re-enter press 1 or for exit press 0\n");
				scanf("%d",&exit_option);
				if(exit_option==0)
				{
					return;
				}
				continue;
			}

		}
		strcpy(addressBook->contacts[actualIndex].email,New);
	}
	break;
	}
	saveContactsToFile(addressBook);


}


void deleteContact(AddressBook *addressBook)
{
	int choice;
	char search[100];
	int matches[30];
	int matchcount=0;
	printf("Enter the contact details to delete: \n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. email\n");
	scanf("%d", &choice);
	if (!isdigit(choice) &&(choice < 1 || choice > 3)) 
    { // Check if input is not an integer
        printf("Invalid option. Please enter a digit between 1 and 3.\n");
        while (getchar() != '\n');  
		return;
    }
	getchar();

	printf("Enter the search: ");
	scanf("%s",search);
	for (int i = 0; i < addressBook->contactCount; i++)
	{
		switch (choice)
		{
		case 1:
			if(strstr(addressBook -> contacts[i].name,search)!=NULL)
			{
				matches[matchcount++]=i;

			}
			break;

		case 2:
			if(strstr(addressBook -> contacts[i].phone,search)!=NULL)
			{
				matches[matchcount++]=i;

			}
			break;
		case 3:
			if(strstr(addressBook -> contacts[i].email,search)!=NULL)
			{
				matches[matchcount++]=i;

			}
			break;

		default:
			printf("Invalid input");
			break;


		}
	}
	if (matchcount==0)
	{
		printf("Contact not found\n");
		return;
	}

	printf("Matching contacts:\n");
	for (int i = 0; i < matchcount; i++)
	{
		int index = matches[i];
		printf("%d. Name: %-10s\t, Phone: %-10s\t, email: %-10s\n",i + 1, addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
	}

	// Ask the user to select a contact to delete
	int deleteIndex;
	printf("Enter the index of the contact to delete (1-%d): ", matchcount);
	scanf("%d", &deleteIndex);

	if (deleteIndex < 1 || deleteIndex > matchcount)
	{
		printf("Invalid index.\n");
		return;
	}

	// Get the actual index in the address book
	int actualIndex = matches[deleteIndex - 1];

	// Shift contacts to remove the selected contact
	for (int i = actualIndex; i < addressBook->contactCount - 1; i++)
	{
		addressBook->contacts[i] = addressBook->contacts[i + 1];
	}

	addressBook->contactCount--;


	printf("Contact deleted successfully.\n");
	saveContactsToFile(addressBook);
}
void saveContactsToFile(AddressBook *addressBook)
{
	FILE *fptr=fopen("contacts.csv","w");
	fprintf(fptr,"#%d\n",addressBook -> contactCount);

	for(int i=0; i< addressBook->contactCount; i++)
	{
		fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fptr);
	printf("Contacts updated succesfully\n");


}
