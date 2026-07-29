 #include<stdio.h>
#include<string.h>
#define ATTENDANCE_FILE "attendance.csv"
typedef struct {
    int employee_id;
    char date[15];
    char status[10];
}
Attendance;
void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

}
void read_line(char *text, int size) {
    if (fgets(text, size, stdin) !=NULL) {
        int length = strlen(text);
        if (length > 0 && text[length -1] == '\n') {
            text[length -1] ='\0';
        } else if (length == size -1) {
            clear_input_buffer();

        }
        }
    }

void mark_attendance(void) {
    Attendance attendance;
    printf("Enter Employee ID: ");
    if (scanf("%d", &attendance.employee_id) !=1) {
        printf("INVALID ID.\n");
        clear_input_buffer();
        return;

    }
    clear_input_buffer();
    printf("Enter Date (DD-MM-YYYY): ");
    read_line(attendance.date, sizeof(attendance.date));
    printf("Enter Status (Present/ Absent): ");
    read_line(attendance.status, sizeof(attendance.status));
    FILE *file = fopen(ATTENDANCE_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open attendance file\n");
        return;

    }
fprintf(file, "%d %s %s\n", attendance.employee_id, attendance.date, attendance.status);
fclose(file);
printf("Attendance marked successfully\n");
}
void view_attendance(void) {
    int search_id;
    Attendance attendance;
    int found = 0;
    printf("Enter Employee ID: ");
    if (scanf("%d", &search_id) !=1) {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;

    }
clear_input_buffer();
FILE *file = fopen(ATTENDANCE_FILE, "r");
if (file ==NULL) {
    printf("No attendance records found\n");
    return;
}
printf("\n--- Attendance Records ---\n");
while (fscanf(file, "%d %14s %9s", &attendance.employee_id, attendance.date, attendance.status) ==3) {
    if (attendance.employee_id == search_id) {
        printf("Date: %s | Status: %s\n", attendance.date, attendance.status);
        found = 1;

    }
}
fclose(file);
if (!found) {
    printf("No attendance records found for Employee ID %d\n", search_id);
}
}


void calculate_salary(void) {
    int employee_id;
    char name[60];
    float basic_salary = 0.0f, bonus = 0.0f, tax_percent = 0.0f;
    printf("Enter Employee ID: ");
    if (scanf("%d", &employee_id) != 1) {
        printf("INVALID ID.\n");
        clear_input_buffer();
        return;

    }

clear_input_buffer();
printf("Enter Employee Name: ");
read_line(name, sizeof(name));
printf("Enter Basic Salary: ");
if (scanf("%f", &basic_salary) !=1) {
    printf("INVALID SALARY INPUT.\n");
    clear_input_buffer();
    return;
}
clear_input_buffer();
printf("Enter Bonus amount: ");
if (scanf("%f", &bonus) !=1) {
    bonus = 0.0f;

}
clear_input_buffer();
printf("Enter Tax Percentage: ");
if (scanf("%f", &tax_percent) !=1) {
    tax_percent = 0.0f;
}
clear_input_buffer();
float tax = (basic_salary * tax_percent / 100.0f);
float net_salary = basic_salary + bonus - tax;
printf("\n--- salary slip for %s (ID: %d) ---\n", name, employee_id);
printf("Basic Salary : %.2f\n", basic_salary);
printf("Bonus        : %.2f\n", bonus);
printf("Tax          : %.2f\n", tax);
printf("Net Salary   : %.2f\n", net_salary);
}
void mark_attendance(void);
void view_attendance(void);
void calculate_salary(void);
int main(void) {

    int choice = 0;
    do {
        printf("\n--- Attendance and Payroll Management ---\n");
        printf("1. Mark Attendance\n");
        printf("2. View Attendance\n");
        printf("3. Calculate Salary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1: mark_attendance();
             break;
            case 2: view_attendance();
                break;
            case 3: calculate_salary();
                break;
            case 4: printf("Exiting...\n");
                break;
            default: printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice !=4);
    return 0;

}