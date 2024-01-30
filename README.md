# Employee Management System

This C program implements a simple Employee Management System that allows users to manage employee records. The program supports operations such as displaying employee details, editing employee salaries, removing employees, and listing all employees. Employee records are stored in a linked list, and the program includes a Makefile for easy compilation.

## Features

1. **Display Single Employee**: Allows users to display details of a specific employee based on their Employee ID.

2. **Edit Employee Salary**: Enables users to edit the salary of a specific employee.

3. **Remove Employee**: Allows users to remove an employee from the records based on their Employee ID.

4. **List All Employees**: Displays details of all employees in the system.

## Usage

1. Compile the program using the provided Makefile.

```bash```
make

This will generate the executable named EmployeeManagementSystem.

1. Run the compiled executable.
   ./EmployeeManagementSystem
   
Follow the menu prompts to perform various operations on employee records.
File Handling
The program reads employee records from a binary file named EmployeeRecords.bin. If the file is not present, the program will display an error message.

Compilation
The Makefile provided includes the necessary flags for compilation, including debugging information.

Linked List Sorting
The program uses a simple linked list to store employee records. The sortList function is implemented to sort the linked list based on Employee ID.

Menu Interface
The program provides a menu-driven interface for users to easily navigate and perform operations on employee records.

Feel free to use, modify, and share this code as needed!
