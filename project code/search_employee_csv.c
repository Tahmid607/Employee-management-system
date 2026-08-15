#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define NAME_SIZE 30

int main()
{
    char employee_name[MAX_EMPLOYEES][NAME_SIZE];
    int employee_age[MAX_EMPLOYEES];
    float employee_salary[MAX_EMPLOYEES];

    int employee_count = 0;
    int i;
    int found = 0;
    char search_name[NAME_SIZE];

    FILE *file;

    printf("===== Search Employee =====\n");

    /* Open CSV file */
    file = fopen("employees.csv", "r");

    if (file == NULL)
    {
        printf("Error: employees.csv file not found.\n");
        return 1;
    }

    /* Skip CSV header */
    fscanf(file, "%*[^\n]\n");

    /* Read employee data from CSV */
    while (employee_count < MAX_EMPLOYEES &&
           fscanf(file, " %29[^,],%d,%f",
                  employee_name[employee_count],
                  &employee_age[employee_count],
                  &employee_salary[employee_count]) == 3)
    {
        employee_count++;
    }

    fclose(file);

    printf("%d employees loaded from employees.csv.\n", employee_count);

    /* Search employee */
    printf("\nEnter Employee Name To Search: ");
    scanf("%29s", search_name);

    for (i = 0; i < employee_count; i++)
    {
        if (strcmp(employee_name[i], search_name) == 0)
        {
            found = 1;

            printf("\n===== Employee Found =====\n");
            printf("Name   : %s\n", employee_name[i]);
            printf("Age    : %d\n", employee_age[i]);
            printf("Salary : %.2f\n", employee_salary[i]);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nEmployee Not Found.\n");
    }

    return 0;
}
