#include <stdio.h>

void saveToCSV(char exit_choice, const char *message)
{
    FILE *file = fopen("exit_confirmation.csv", "a");

    if (file == NULL)
    {
        printf("Error: Could not open CSV file.\n");
        return;
    }

    fprintf(file, "%c,%s\n", exit_choice, message);
    fclose(file);
}

int main()
{
    char exit_choice;
    FILE *file = fopen("exit_confirmation.csv", "r");

    if (file == NULL)
    {
        file = fopen("exit_confirmation.csv", "w");
        if (file != NULL)
        {
            fprintf(file, "Exit_Choice,Message\\n");
            fclose(file);
        }
    }
    else
    {
        fclose(file);
    }

    printf("===== Exit Confirmation =====\n");

    while (1)
    {
        printf("Do You Want To Exit? (Y/N): ");
        scanf(" %c", &exit_choice);

        if (exit_choice == 'Y' || exit_choice == 'y')
        {
            printf("\nThank You For Using Employee Management System.\n");
            printf("Good Bye!\n");
            saveToCSV(exit_choice, "Thank You For Using Employee Management System");
            break;
        }
        else if (exit_choice == 'N' || exit_choice == 'n')
        {
            printf("\nReturning To Main Menu...\n");
            saveToCSV(exit_choice, "Returning To Main Menu");
            break;
        }
        else
        {
            printf("\nInvalid Input!\n");
            printf("Please Enter Y or N.\n");
        }
    }

    return 0;
}
