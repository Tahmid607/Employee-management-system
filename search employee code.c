#include <stdio.h>
#include <string.h>
int main()
{
    char employee_name[100][30];
    int employee_age[100];
    float employee_salary[100];

    int employee_count;
    int i;
    int found = 0;

    char search_name[30];

    printf("===== Search Employee =====\n");

    printf("How Many Employees Do You Want To Add? ");
    scanf("%d", &employee_count);

    for (i = 0; i < employee_count; i++)
    {
        printf("\nEmployee %d\n", i + 1);

        printf("Enter Name: ");
        scanf("%s", employee_name[i]);

        printf("Enter Age: ");
        scanf("%d", &employee_age[i]);

        printf("Enter Salary: ");
        scanf("%f", &employee_salary[i]);
    }

    printf("\nEnter Employee Name To Search: ");
    scanf("%s", search_name);

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
