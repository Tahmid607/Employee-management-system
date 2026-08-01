#include <stdio.h>
#include <string.h>

#define MAX_DEPT 50
#define MAX_EMP  200

struct Department {
    int id;
    char name[50];
};

struct Employee {
    int id;
    char name[50];
    float salary;
    int dept_id;
};

struct Department departments[MAX_DEPT];
int deptCount = 0;

struct Employee employees[MAX_EMP];
int empCount = 0;

void addDepartment();
void addEmployee();
void viewAllDepartments();
void viewAllEmployees();
void viewEmployeesByDepartment();
int findDepartmentIndexById(int dept_id);
void saveDepartmentsToCSV();
void saveEmployeesToCSV();
void showMenu();

int main() {
    int choice;

    printf("=====================================================\n");
    printf("   WELCOME TO EMPLOYEE MANAGEMENT SYSTEM (C Program)\n");
    printf("=====================================================\n");

    while (1) {
        showMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Please enter a valid number!\n\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addDepartment();
                break;
            case 2:
                addEmployee();
                break;
            case 3:
                viewAllDepartments();
                break;
            case 4:
                viewEmployeesByDepartment();
                break;
            case 5:
                viewAllEmployees();
                break;
            case 6:
                printf("\nThank you for using Employee Management System!\n");
                printf("Your data is saved in departments.csv and employees.csv\n");
                return 0;
            default:
                printf("\n[Error] Invalid choice! Please select from menu.\n\n");
        }
    }

    return 0;
}

void showMenu() {
    printf("\n---------------------- MENU -------------------------\n");
    printf("1. Add Department\n");
    printf("2. Add Employee\n");
    printf("3. View All Departments\n");
    printf("4. View Employees by Department\n");
    printf("5. View All Employees\n");
    printf("6. Exit\n");
    printf("-------------------------------------------------------\n");
}

void addDepartment() {
    if (deptCount >= MAX_DEPT) {
        printf("\n[Error] Department list is full! Cannot add more.\n");
        return;
    }

    struct Department newDept;

    newDept.id = deptCount + 1;

    printf("\n--- Add New Department ---\n");
    printf("Enter Department Name: ");
    scanf(" %[^\n]", newDept.name);

    departments[deptCount] = newDept;
    deptCount++;

    printf("\n[Success] Department '%s' added with ID: %d\n", newDept.name, newDept.id);

    saveDepartmentsToCSV();
}

void addEmployee() {
    if (empCount >= MAX_EMP) {
        printf("\n[Error] Employee list is full! Cannot add more.\n");
        return;
    }

    if (deptCount == 0) {
        printf("\n[Error] No department found! Please add a department first.\n");
        return;
    }

    struct Employee newEmp;
    newEmp.id = empCount + 1;

    printf("\n--- Add New Employee ---\n");
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", newEmp.name);

    printf("Enter Employee Salary: ");
    scanf("%f", &newEmp.salary);

    printf("\nAvailable Departments:\n");
    viewAllDepartments();

    int dept_id;
    printf("Enter Department ID for this Employee: ");
    scanf("%d", &dept_id);

    if (findDepartmentIndexById(dept_id) == -1) {
        printf("\n[Error] Invalid Department ID! Employee not added.\n");
        return;
    }

    newEmp.dept_id = dept_id;

    employees[empCount] = newEmp;
    empCount++;

    printf("\n[Success] Employee '%s' added with ID: %d\n", newEmp.name, newEmp.id);

    saveEmployeesToCSV();
}

int findDepartmentIndexById(int dept_id) {
    for (int i = 0; i < deptCount; i++) {
        if (departments[i].id == dept_id) {
            return i;
        }
    }
    return -1;
}

void viewAllDepartments() {
    if (deptCount == 0) {
        printf("\nNo departments added yet.\n");
        return;
    }

    printf("\n%-6s %-20s\n", "ID", "Department Name");
    printf("--------------------------------\n");
    for (int i = 0; i < deptCount; i++) {
        printf("%-6d %-20s\n", departments[i].id, departments[i].name);
    }
}

void viewEmployeesByDepartment() {
    if (deptCount == 0) {
        printf("\nNo departments added yet.\n");
        return;
    }

    viewAllDepartments();

    int dept_id;
    printf("\nEnter Department ID to view its Employees: ");
    scanf("%d", &dept_id);

    int index = findDepartmentIndexById(dept_id);
    if (index == -1) {
        printf("\n[Error] Department ID not found!\n");
        return;
    }

    printf("\nEmployees in Department: %s\n", departments[index].name);
    printf("%-6s %-20s %-10s\n", "ID", "Name", "Salary");
    printf("--------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < empCount; i++) {
        if (employees[i].dept_id == dept_id) {
            printf("%-6d %-20s %-10.2f\n",
                   employees[i].id, employees[i].name, employees[i].salary);
            found = 1;
        }
    }

    if (!found) {
        printf("No employees found in this department.\n");
    }
}

void viewAllEmployees() {
    if (empCount == 0) {
        printf("\nNo employees added yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-10s %-15s\n", "ID", "Name", "Salary", "Department");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < empCount; i++) {
        int dIndex = findDepartmentIndexById(employees[i].dept_id);
        char deptName[50] = "Unknown";
        if (dIndex != -1) {
            strcpy(deptName, departments[dIndex].name);
        }

        printf("%-6d %-20s %-10.2f %-15s\n",
               employees[i].id, employees[i].name,
               employees[i].salary, deptName);
    }
}

void saveDepartmentsToCSV() {
    FILE *fp = fopen("departments.csv", "w");

    if (fp == NULL) {
        printf("[Error] Could not create departments.csv file!\n");
        return;
    }

    fprintf(fp, "ID,DepartmentName\n");

    for (int i = 0; i < deptCount; i++) {
        fprintf(fp, "%d,%s\n", departments[i].id, departments[i].name);
    }

    fclose(fp);
}

void saveEmployeesToCSV() {
    FILE *fp = fopen("employees.csv", "w");

    if (fp == NULL) {
        printf("[Error] Could not create employees.csv file!\n");
        return;
    }

    fprintf(fp, "ID,Name,Salary,DepartmentID,DepartmentName\n");

    for (int i = 0; i < empCount; i++) {
        int dIndex = findDepartmentIndexById(employees[i].dept_id);
        char deptName[50] = "Unknown";
        if (dIndex != -1) {
            strcpy(deptName, departments[dIndex].name);
        }

        fprintf(fp, "%d,%s,%.2f,%d,%s\n",
                employees[i].id, employees[i].name, employees[i].salary,
                employees[i].dept_id, deptName);
    }

    fclose(fp);
}