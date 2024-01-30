#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define FLUSH_STDIN while(getc(stdin)!='\n')


#define MAX_NAME 128
#define MAX_DATE 64
#define MAX_EMAIL_ADDRESS 128
#define MAX_RECORDS 50

char totalEntries = 0;

typedef struct __attribute__((packed, aligned(1))) employee_data {
  int employeeId;
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	char middleName[MAX_NAME];
	char emailAddress[MAX_EMAIL_ADDRESS];
	char title[MAX_EMAIL_ADDRESS];
	float annualSalary;
	char dataOfHire[MAX_DATE];
  struct employee_data *pNext;
}EmployeeInformation;

void displaySingleEmployee(EmployeeInformation *employeeRecords);
void editEmployeeSalary(EmployeeInformation *employeeRecords);
void printAllEmployees(EmployeeInformation *employeeRecords);
void removeEmployee(EmployeeInformation *employeeRecords);
void Insert(EmployeeInformation [], EmployeeInformation **);
void sortList(EmployeeInformation *head);
char menu(void);


int main(int argc, char *argv[]){
  FILE *fp;

  EmployeeInformation *head = NULL;
  EmployeeInformation *pNewNode = NULL;
  EmployeeInformation buffer[MAX_RECORDS];
	int i;
	char choice;

	fp = fopen("EmployeeRecords.bin", "rb");
	
	if(fp == NULL){
		printf("Error. Files didn't open properly.\n");
		return 1;
	}
		
	while(fread(&buffer[i++], (sizeof(EmployeeInformation) - sizeof(struct employee_data *)), 1, fp)==1){
		totalEntries++;
	}
	
	for(int i = 0; i < totalEntries; i++){
		pNewNode = (EmployeeInformation *)malloc(sizeof(EmployeeInformation) - sizeof(struct employe_data*));

		strcpy(pNewNode->firstName, buffer[i].firstName);
		strcpy(pNewNode->lastName, buffer[i].lastName);
		strcpy(pNewNode->middleName, buffer[i].middleName);
		strcpy(pNewNode->emailAddress, buffer[i].emailAddress);
		strcpy(pNewNode->dataOfHire, buffer[i].dataOfHire);
		strcpy(pNewNode->title, buffer[i].title);
		pNewNode->annualSalary = buffer[i].annualSalary;
		pNewNode->employeeId = buffer[i].employeeId;

		pNewNode->pNext = NULL;

		if (head == NULL){
				head = pNewNode;
		}
		else{
			pNewNode->pNext = head;
			head = pNewNode;
		}
	}

  fclose(fp);

	sortList(head);

	printf("Loaded %d records into the employee list.\n", totalEntries);

	while ((choice = menu()) != '5'){
		switch (choice)
    {
			case '1' :  displaySingleEmployee(head);
									break;
			case '2' :  editEmployeeSalary(head);
									break;
			case '3' :	removeEmployee(head);
									break;
			case '4' :	printAllEmployees(head);
									break;

			default  :  puts("Switching error");
		}
	}


  return 0;
}

char menu(void){
  int ch;

  puts("\nEmployee Management System Main Menu\n");
  puts("1. Display Employee");
  puts("2. Edit Employee Salary");
	puts("3. Remove Employee");
  puts("4. List All Employees");
  puts("5. Quit");

	printf("Select a menu item: ");

  while ((ch = getchar()) != EOF){
    while (getchar() != '\n')  /* discard rest of line */
      continue;
    if (strchr("12345",ch) == NULL)
      puts("Please enter an 1, 2, 3, 4 or 5:");
    else
        break;
  }
  if (ch == EOF)       /* make EOF cause program to quit */
      ch = 'q';

  return ch;
}

// 1) Display Single Employee function

void displaySingleEmployee(EmployeeInformation *employeeRecords){
  EmployeeInformation *pList;
	int employeeID;
	int i;
	bool flag;

	pList = employeeRecords;

	printf("Enter Employee ID: ");
	scanf("%d", &employeeID);

	printf("\n");

	while(pList != NULL){
		if(pList->employeeId == employeeID){
			flag = true;
			break;
		}
		pList = pList->pNext;
	}

	if(flag == true){
		printf("Employee ID: %d\n", pList->employeeId);
		printf("Employee Name: %s, %s\n", pList->lastName, pList->firstName);
		printf("Tite: %s\n", pList->title);
		printf("Date of Hire: %s\n", pList->dataOfHire);
		printf("Email Address: %s\n", pList->emailAddress);
		printf("Salary: $%.2f\n", pList->annualSalary);
		printf("\n");
	}
	else{
		printf("No record found for employee with ID %d\n\n", employeeID);
	}
	FLUSH_STDIN;
}

// 2) Edit Employee Salary Fucntion
void editEmployeeSalary(EmployeeInformation *employeeRecords){
  EmployeeInformation *pList;
	int employeeID;
	float newSalary = 0.00;
	bool flag;
	int i;

	pList = employeeRecords;

	printf("Enter Employee ID: ");
	scanf("%d", &employeeID);

	while(pList != NULL){
		if(pList->employeeId == employeeID){
			flag = true;
			break;
		}
		pList = pList->pNext;
	}

	if (flag == true){

		printf("Current Salary: %.2f\n", pList->annualSalary);
		printf("Please enter new salary: $");
		scanf("%f", &newSalary);

		pList->annualSalary = newSalary;
	}
	else{
		printf("No record found for employee with ID %d\n\n", employeeID);
	}

	FLUSH_STDIN;
}

// 3) Remove Employee Function
void removeEmployee(EmployeeInformation *employeeRecords){
	int employeeID;

	EmployeeInformation *temp = employeeRecords, *prev;

	printf("Enter Employee ID: ");
	scanf("%d", &employeeID);

	printf("\n");

	// If head node itself holds the key to be deleted
	if (temp != NULL &&  temp->employeeId == employeeID) {
			employeeRecords = temp->pNext; // Changed head
			free(temp); // free old head
			return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->employeeId != employeeID) {
			prev = temp;
			temp = temp->pNext;
	}

	// If key was not present in linked list
	if (temp == NULL)
			return;

	// Unlink the node from linked list
	prev->pNext = temp->pNext;

	free(temp); // Free memory
	FLUSH_STDIN;
}

// 4) List All Employees Function
void printAllEmployees(EmployeeInformation *employeeRecords){

  EmployeeInformation *pList;

  pList = employeeRecords;

	while(pList != NULL){
		printf("Employee ID: %d\n", pList->employeeId);
		printf("Employee Name: %s, %s\n", pList->lastName, pList->firstName);
		printf("Tite: %s\n", pList->title);
		printf("Date of Hire: %s\n", pList->dataOfHire);
		printf("Email Address: %s\n", pList->emailAddress);
		printf("Salary: $%.2f\n", pList->annualSalary);
		printf("-----------------------------------------------------------\n");
    pList = pList->pNext;
	}

}

void sortList(EmployeeInformation *head) {  
	//Node current will point to head  
	EmployeeInformation *current = head;
	EmployeeInformation *index = NULL;

	int temp;  
		
	if(head == NULL) {  
			return;  
	}  
	else {  
		while(current != NULL) {  
			//Node index will point to node next to current  
			index = current;  
				
			while(index != NULL) {  
				//If current node's data is greater than index's node data, swap the data between them  
				if(current->employeeId > index->employeeId) {  
					temp = current->employeeId;  
					current->employeeId = index->employeeId;  
					index->employeeId = temp;  
				}  
				index = index->pNext;  
			}  
			current = current->pNext;  
		}      
	} 
} 