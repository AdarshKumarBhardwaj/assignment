#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"

// Function prototypes
void createFileIfNotExists();
void addUser();
void displayUsers();
void updateUser();
void deleteUser();

int main()
{
    int choice;

    do
    {
        printf("\n=== CRUD Operations Menu ===\n");
        printf("1. Create File (if not exists)\n");
        printf("2. Add User\n");
        printf("3. Display Users\n");
        printf("4. Update User\n");
        printf("5. Delete User\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createFileIfNotExists();
            break;
        case 2:
            addUser();
            break;
        case 3:
            displayUsers();
            break;
        case 4:
            updateUser();
            break;
        case 5:
            deleteUser();
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to create a file if it doesn't exist
void createFileIfNotExists()
{
    FILE *file = fopen(FILENAME, "a");
    if (!file)
    {
        perror("Error creating file");
        return;
    }
    fclose(file);
    printf("File '%s' is ready for use.\n", FILENAME);
}

// Function to add a new user
void addUser()
{
    FILE *file = fopen(FILENAME, "a");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    int id, age;
    char name[50];

    printf("Enter ID: ");
    scanf("%d", &id);
    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Age: ");
    scanf("%d", &age);

    fprintf(file, "%d %s %d\n", id, name, age);

    fclose(file);
    printf("User added successfully.\n");
}

// Function to display all users
void displayUsers()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    int id, age;
    char name[50];
    printf("\n--- User Records ---\n");

    while (fscanf(file, "%d %s %d", &id, name, &age) != EOF)
    {
        printf("ID: %d, Name: %s, Age: %d\n", id, name, age);
    }

    fclose(file);
}

// Function to update a specific user
void updateUser()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    int id, age, targetId, found = 0;
    char name[50], tempName[50];
    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        perror("Error creating temp file");
        fclose(file);
        return;
    }

    printf("Enter the ID of the user to update: ");
    scanf("%d", &targetId);

    while (fscanf(file, "%d %s %d", &id, name, &age) != EOF)
    {
        if (id == targetId)
        {
            printf("Enter new Name: ");
            scanf("%s", tempName);
            printf("Enter new Age: ");
            scanf("%d", &age);
            fprintf(temp, "%d %s %d\n", id, tempName, age);
            found = 1;
        }
        else
        {
            fprintf(temp, "%d %s %d\n", id, name, age);
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User updated successfully.\n");
    }
    else
    {
        remove("temp.txt");
        printf("User with ID %d not found.\n", targetId);
    }
}

// Function to delete a specific user
void deleteUser()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    int id, age, targetId, found = 0;
    char name[50];
    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        perror("Error creating temp file");
        fclose(file);
        return;
    }

    printf("Enter the ID of the user to delete: ");
    scanf("%d", &targetId);

    while (fscanf(file, "%d %s %d", &id, name, &age) != EOF)
    {
        if (id == targetId)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d %s %d\n", id, name, age);
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User deleted successfully.\n");
    }
    else
    {
        remove("temp.txt");
        printf("User with ID %d not found.\n", targetId);
    }
}
