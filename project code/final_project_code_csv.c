
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPLOYEE_FILE  "employees.csv"
#define  ATTENDANCE_FILE "attendance.csv"
#define LOGIN_FILE  "login.csv"
#define ENC_KEY 'K' // change the naming pattern into something meaningfull
#define MAX_DEPARTMENTS 20

typedef struct {
    int id;
  char name[50]; // check all the indentation and spacing in the code
   char gender[10];
    int age;
    char phone[15];
    char department[30];
    char designation[30];
    char joiningDate[15];
    float basicSalary; // why different kind of casing pattern? use only one for entire project
} Employee;

typedef struct {
    int empId;
    char date[15];
    char status[10];
} Attendance;

char departments[MAX_DEPARTMENTS][30];
int deptCount = 0;
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void readLine(char *str, int size) {
    if (fgets(str, size, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        } else if (len == (size_t)(size - 1)) {
            clearInputBuffer();
        }
    }
}
void xorEncryptDecrypt(char *str, char key) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != key) {
            str[i] = str[i] ^ key;
        }
    }
}

int confirmAction(const char *message) {
    char choice;
    printf("%s (y/n): ", message);
    if (scanf(" %c", &choice) != 1) {
        choice = 'n';
    }
    clearInputBuffer();
    return (choice == 'y' || choice == 'Y');
}

void registerAdmin(void) {
    FILE *file = fopen(LOGIN_FILE, "r");
    if (file != NULL) {
        fclose(file);
        printf("An admin account already exists. Please login instead.\n");
        return;
    }

    char username[30], password[30], confirmPass[30];
    printf("\nEnter new username: ");
    readLine(username, sizeof(username));

    printf("Enter new password: ");
    readLine(password, sizeof(password));

    printf("Enter password again: ");
    readLine(confirmPass, sizeof(confirmPass));

    if (strcmp(password, confirmPass) != 0) {
        printf("Passwords do not match. Try again!\n");
        return;
    }

    xorEncryptDecrypt(password, ENC_KEY);
    file = fopen(LOGIN_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
        printf("Registration successful. You can now log in.\n");
    } else {
        printf("Error: Unable to open login file\n");
    }
}

int adminLogin(void) {
    char username[30], password[30];
    char storedUser[30], storedPass[30];

    FILE *file = fopen(LOGIN_FILE, "r");
    if (file == NULL) {
        printf("No admin account found. Please register first.\n");
        return 0;
    }

    printf("\nEnter username: ");
    readLine(username, sizeof(username));

    printf("Enter password: ");
    readLine(password, sizeof(password));

    if (fscanf(file, "%29s %29s", storedUser, storedPass) != 2) {
        fclose(file);
        printf("Error: Login file corrupt.\n");
        return 0;
    }
    fclose(file);

    xorEncryptDecrypt(storedPass, ENC_KEY);

    if (strcmp(username, storedUser) == 0 && strcmp(password, storedPass) == 0) {
        printf("Login successful\n");
        return 1;
    }

    printf("Login failed: incorrect username or password\n");
    return 0;
}

void changePassword(void) {
    char storedUser[30], storedPass[30];
    char currPass[30], newPass[30], confirmPass[30];

    FILE *file = fopen(LOGIN_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open login file\n");
        return;
    }

    if (fscanf(file, "%29s %29s", storedUser, storedPass) != 2) {
        fclose(file);
        printf("Error: Login file data unreadable\n");
        return;
    }
    fclose(file);

    xorEncryptDecrypt(storedPass, ENC_KEY);

    printf("Enter current password: ");
    readLine(currPass, sizeof(currPass));

    if (strcmp(currPass, storedPass) != 0) {
        printf("Incorrect current password.\n");
        return;
    }

    printf("Enter new password: ");
    readLine(newPass, sizeof(newPass));

    printf("Enter new password again: ");
    readLine(confirmPass, sizeof(confirmPass));

    if (strcmp(newPass, confirmPass) != 0) {
        printf("Passwords do not match. Try again!\n");
        return;
    }

    xorEncryptDecrypt(newPass, ENC_KEY);
    file = fopen(LOGIN_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%s %s\n", storedUser, newPass);
        fclose(file);
        printf("Password changed successfully\n");
    } else {
        printf("Error: Unable to open login file\n");
    }
}

void forgotPassword(void) {
    char recoveryKey[30];
    char storedUser[30], storedPass[30];

    printf("Enter recovery key: ");
    readLine(recoveryKey, sizeof(recoveryKey));

    if (strcmp(recoveryKey, "RECOVER123") != 0) {
        printf("Incorrect recovery key\n");
        return;
    }

    FILE *file = fopen(LOGIN_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open login file\n");
        return;
    }

    if (fscanf(file, "%29s %29s", storedUser, storedPass) == 2) {
        xorEncryptDecrypt(storedPass, ENC_KEY);
        printf("Username: %s\n", storedUser);
        printf("Password: %s\n", storedPass);
    } else {
        printf("Error reading recovery details.\n");
    }
    fclose(file);
}

void addEmployee(void) {
    Employee e;
    printf("\nEnter Employee ID: ");
    if (scanf("%d", &e.id) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Name: ");
    readLine(e.name, sizeof(e.name));

    printf("Enter Gender: ");
    readLine(e.gender, sizeof(e.gender));

    printf("Enter Age: ");
    if (scanf("%d", &e.age) != 1) {
        printf("Invalid Age.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Phone: ");
    readLine(e.phone, sizeof(e.phone));

    printf("Enter Department: ");
    readLine(e.department, sizeof(e.department));

    printf("Enter Designation: ");
    readLine(e.designation, sizeof(e.designation));

    printf("Enter Joining Date (DD-MM-YYYY): ");
    readLine(e.joiningDate, sizeof(e.joiningDate));

    printf("Enter Basic Salary: ");
    if (scanf("%f", &e.basicSalary) != 1) {
        printf("Invalid Salary.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file = fopen(EMPLOYEE_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open employee file\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%d;%s;%s;%s;%s;%.2f\n",
            e.id, e.name, e.gender, e.age, e.phone,
            e.department, e.designation, e.joiningDate, e.basicSalary);
    fclose(file);
    printf("Employee added successfully\n");
}

void printEmployee(Employee e) {
    printf("ID: %d | Name: %s | Gender: %s | Age: %d | Phone: %s | "
           "Dept: %s | Designation: %s | Joined: %s | Basic Salary: %.2f\n",
           e.id, e.name, e.gender, e.age, e.phone,
           e.department, e.designation, e.joiningDate, e.basicSalary);
}

void viewAllEmployees(void) {
    Employee e;
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("No employee records found\n");
        return;
    }

    printf("\n--- All Employees ---\n");
    int count = 0;
    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        printEmployee(e);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No employee records found\n");
    }
}

void searchEmployeeById(void) {
    int searchId;
    Employee e;
    int found = 0;

    printf("Enter Employee ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("No employee records found\n");
        return;
    }

    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (e.id == searchId) {
            printEmployee(e);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No employee found with ID %d\n", searchId);
    }
}

void searchEmployeeByName(void) {
    char searchName[50];
    Employee e;
    int found = 0;

    printf("Enter Name to search: ");
    readLine(searchName, sizeof(searchName));

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("No employee records found\n");
        return;
    }

    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (strstr(e.name, searchName) != NULL) {
            printEmployee(e);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No employee found matching name: %s\n", searchName);
    }
}

void updateEmployee(void) {
    int updateId;
    Employee e;
    int found = 0;

    printf("Enter Employee ID to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file == NULL || temp == NULL) {
        printf("Error: Unable to open employee file\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (e.id == updateId) {
            found = 1;
            printf("Enter new Name: ");
            readLine(e.name, sizeof(e.name));

            printf("Enter new Gender: ");
            readLine(e.gender, sizeof(e.gender));

            printf("Enter new Age: ");
            scanf("%d", &e.age);
            clearInputBuffer();

            printf("Enter new Phone: ");
            readLine(e.phone, sizeof(e.phone));

            printf("Enter new Department: ");
            readLine(e.department, sizeof(e.department));

            printf("Enter new Designation: ");
            readLine(e.designation, sizeof(e.designation));

            printf("Enter new Joining Date: ");
            readLine(e.joiningDate, sizeof(e.joiningDate));

            printf("Enter new Basic Salary: ");
            scanf("%f", &e.basicSalary);
            clearInputBuffer();
        }
        fprintf(temp, "%d;%s;%s;%d;%s;%s;%s;%s;%.2f\n",
                e.id, e.name, e.gender, e.age, e.phone,
                e.department, e.designation, e.joiningDate, e.basicSalary);
    }
    fclose(file);
    fclose(temp);

    remove(EMPLOYEE_FILE);
    rename("temp.csv", EMPLOYEE_FILE);

    if (found) {
        printf("Employee updated successfully\n");
    } else {
        printf("No employee found with ID %d\n", updateId);
    }
}

void deleteEmployee(void) {
    int deleteId;
    Employee e;
    int found = 0;

    printf("Enter Employee ID to delete: ");
    if (scanf("%d", &deleteId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (!confirmAction("Are you sure you want to delete this employee?")) {
        printf("Delete cancelled\n");
        return;
    }

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file == NULL || temp == NULL) {
        printf("Error: Unable to open employee file\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (e.id == deleteId) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d;%s;%s;%d;%s;%s;%s;%s;%.2f\n",
                e.id, e.name, e.gender, e.age, e.phone,
                e.department, e.designation, e.joiningDate, e.basicSalary);
    }
    fclose(file);
    fclose(temp);

    remove(EMPLOYEE_FILE);
    rename("temp.csv", EMPLOYEE_FILE);

    if (found) {
        printf("Employee deleted successfully\n");
    } else {
        printf("No employee found with ID %d\n", deleteId);
    }
}

void markAttendance(void) {
    Attendance a;
    printf("Enter Employee ID: ");
    if (scanf("%d", &a.empId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Date (DD-MM-YYYY): ");
    readLine(a.date, sizeof(a.date));

    printf("Enter Status (Present/Absent): ");
    readLine(a.status, sizeof(a.status));

    FILE *file = fopen(ATTENDANCE_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open attendance file\n");
        return;
    }

    fprintf(file, "%d %s %s\n", a.empId, a.date, a.status);
    fclose(file);
    printf("Attendance marked successfully\n");
}

void viewAttendance(void) {
    int searchId;
    Attendance a;
    int found = 0;

    printf("Enter Employee ID: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file = fopen(ATTENDANCE_FILE, "r");
    if (file == NULL) {
        printf("No attendance records found\n");
        return;
    }

    printf("\n--- Attendance Records ---\n");
    while (fscanf(file, "%d %14s %9s", &a.empId, a.date, a.status) == 3) {
        if (a.empId == searchId) {
            printf("Date: %s | Status: %s\n", a.date, a.status);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No attendance records found for Employee ID %d\n", searchId);
    }
}

void calculateSalary(void) {
    int searchId;
    Employee e;
    int found = 0;

    printf("Enter Employee ID: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("No employee records found\n");
        return;
    }

    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (e.id == searchId) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No employee found with ID %d\n", searchId);
        return;
    }

    float bonus = 0.0f, taxPercent = 0.0f;
    printf("Enter Bonus amount: ");
    if (scanf("%f", &bonus) != 1) bonus = 0.0f;
    clearInputBuffer();

    printf("Enter Tax percentage (e.g. 5 for 5%%): ");
    if (scanf("%f", &taxPercent) != 1) taxPercent = 0.0f;
    clearInputBuffer();

    float tax = (e.basicSalary * taxPercent) / 100.0f;
    float netSalary = e.basicSalary + bonus - tax;

    printf("\n--- Salary Slip for %s (ID: %d) ---\n", e.name, e.id);
    printf("Basic Salary : %.2f\n", e.basicSalary);
    printf("Bonus        : %.2f\n", bonus);
    printf("Tax          : %.2f\n", tax);
    printf("Net Salary   : %.2f\n", netSalary);
}

void addDepartment(void) {
    if (deptCount >= MAX_DEPARTMENTS) {
        printf("Department list is full\n");
        return;
    }

    printf("Enter Department name: ");
    readLine(departments[deptCount], sizeof(departments[deptCount]));
    deptCount++;
    printf("Department added successfully\n");
}

void viewEmployeesByDepartment(void) {
    char searchDept[30];
    Employee e;
    int found = 0;

    printf("Enter Department name: ");
    readLine(searchDept, sizeof(searchDept));

    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("No employee records found\n");
        return;
    }

    printf("\n--- Employees in %s ---\n", searchDept);
    while (fscanf(file, "%d;%49[^;];%9[^;];%d;%14[^;];%29[^;];%29[^;];%14[^;];%f\n",
                  &e.id, e.name, e.gender, &e.age, e.phone,
                  e.department, e.designation, e.joiningDate, &e.basicSalary) == 9) {
        if (strcasecmp(e.department, searchDept) == 0) {
            printEmployee(e);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No employees found in department %s\n", searchDept);
    }
}

void searchModule(void) {
    int choice = 0;
    printf("\n--- Search Module ---\n");
    printf("1. Search by Employee ID\n");
    printf("2. Search by Department\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        printf("Invalid choice\n");
        return;
    }
    clearInputBuffer();

    if (choice == 1) {
        searchEmployeeById();
    } else if (choice == 2) {
        viewEmployeesByDepartment();
    } else {
        printf("Invalid choice\n");
    }
}

void dashboardMenu(void) {
    int choice = 0;
    do {
        printf("\n===== Dashboard Menu =====\n");
        printf("1. Employee Management\n");
        printf("2. Attendance Management\n");
        printf("3. Payroll Management\n");
        printf("4. Department Management\n");
        printf("5. Search Module\n");
        printf("6. Change Password\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: {
                int empChoice = 0;
                printf("\n--- Employee Management ---\n");
                printf("1. Add Employee\n2. View All Employees\n");
                printf("3. Search by ID\n4. Search by Name\n");
                printf("5. Update Employee\n6. Delete Employee\n");
                printf("Enter your choice: ");
                if (scanf("%d", &empChoice) != 1) {
                    clearInputBuffer();
                    printf("Invalid input\n");
                    break;
                }
                clearInputBuffer();

                switch (empChoice) {
                    case 1: addEmployee(); break;
                    case 2: viewAllEmployees(); break;
                    case 3: searchEmployeeById(); break;
                    case 4: searchEmployeeByName(); break;
                    case 5: updateEmployee(); break;
                    case 6: deleteEmployee(); break;
                    default: printf("Invalid choice\n");
                }
                break;
            }
            case 2: {
                int attChoice = 0;
                printf("\n--- Attendance Management ---\n");
                printf("1. Mark Attendance\n2. View Attendance\n");
                printf("Enter your choice: ");
                if (scanf("%d", &attChoice) != 1) {
                    clearInputBuffer();
                    printf("Invalid input\n");
                    break;
                }
                clearInputBuffer();

                if (attChoice == 1) markAttendance();
                else if (attChoice == 2) viewAttendance();
                else printf("Invalid choice\n");
                break;
            }
            case 3:
                calculateSalary();
                break;
            case 4: {
                int deptChoice = 0;
                printf("\n--- Department Management ---\n");
                printf("1. Add Department\n2. View Employees by Department\n");
                printf("Enter your choice: ");
                if (scanf("%d", &deptChoice) != 1) {
                    clearInputBuffer();
                    printf("Invalid input\n");
                    break;
                }
                clearInputBuffer();

                if (deptChoice == 1) addDepartment();
                else if (deptChoice == 2) viewEmployeesByDepartment();
                else printf("Invalid choice\n");
                break;
            }
            case 5:
                searchModule();
                break;
            case 6:
                changePassword();
                break;
            case 7:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);
}

int main(void) {
    strncpy(departments[0], "HR", sizeof(departments[0]));
    strncpy(departments[1], "IT", sizeof(departments[1]));
    strncpy(departments[2], "Finance", sizeof(departments[2]));
    deptCount = 3;

    int choice = 0;
    printf("Welcome to the Employee Management System\n");

    do {
        printf("\n===== Main Menu =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Forgot Password\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                registerAdmin();
                break;
            case 2:
                if (adminLogin()) {
                    dashboardMenu();
                }
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                if (confirmAction("Are you sure you want to exit?")) {
                    printf("Exiting...\n");
                } else {
                    choice = 0;
                }
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}