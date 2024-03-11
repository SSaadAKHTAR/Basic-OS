#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void createFolder() {
    // Declare a character array to store folder name
    char folderName[50];
    printf("Enter Folder name: ");
    scanf("%s", folderName);

    // 0777 sets the permissions
    if (mkdir(folderName, 0777) == 0) {
        // If the folder creation is successful, print a message
        printf("Folder '%s' created.\n", folderName);
    } else {
        // If there's an error creating the folder, print an error message
        printf("Error creating folder.\n");
    }
}

void createFile() {
    char fileName[50];
    printf("Enter File Name: ");
    scanf("%s", fileName);
// Create an empty file using the touch command
    char command[100];
    sprintf(command, "touch %s", fileName);

    if (system(command) == 0) {
        printf("File '%s' created.\n", fileName);
    } else {
        printf("Error creating file.\n");
    }
}

void changeFileRights() {
    char fileName[50];
//Declares an integer variable named permissions to store the new file permissions.
    int permissions;

    printf("Enter File Name: ");
    scanf("%s", fileName);

    printf("Enter new permissions (in octal): ");
    scanf("%o", &permissions);

//Uses the chmod system call to change the permissions of the file
    if (chmod(fileName, permissions) == 0) {
// If the operation is successful (returns 0), 
        printf("Permissions for file '%s' changed to %o.\n", fileName, permissions);
    } else {
// if else then it prints an error message indicating that there was an error changing file permissions.
        printf("Error changing file permissions.\n");
    }
}

void searchFile() {
//Declares a character array name to store the name of the file.
    char fileName[50];
    printf("Enter File Name to search: ");
    scanf("%s", fileName);

//This structure will be used to store information about the file when using the stat system call.
    struct stat fileInfo;
//Uses the stat system call to retrieve information about the file 
    if (stat(fileName, &fileInfo) == 0) {
        printf("File '%s' found.\n", fileName);
    } else {
//
        printf("File '%s' not found.\n", fileName);
    }
}


void createUser() {
    char username[50];
    printf("Enter Username: ");
    scanf("%s", username);

    // Useing useradd command
    char command[100];
    sprintf(command, "sudo useradd %s", username);

    if (system(command) == 0) {
        printf("User '%s' created.\n", username);
    } else {
        printf("Error creating user.\n");
    }
}

void deleteUser() {
    char username[50];
    printf("Enter Username to delete: ");
    scanf("%s", username);

    // Useing userdel command 
    char command[100];
    sprintf(command, "sudo userdel %s", username);

    if (system(command) == 0) {
        printf("User '%s' deleted.\n", username);
    } else {
        printf("Error deleting user.\n");
    }
}

void updateUser() {
    char username[50];
    printf("Enter Username to update: ");
    scanf("%s", username);

    // Using usermod command
    char command[200];
    sprintf(command, "sudo usermod -l %s %s", username, username);

    if (system(command) == 0) {
        printf("User '%s' updated.\n", username);
    } else {
        printf("Error updating user.\n");
    }
}

void switchUser() {
    char username[50];
    printf("Enter Username to switch: ");
    scanf("%s", username);

    // Using su command
    char command[100];
    sprintf(command, "su %s", username);

    if (system(command) == 0) {
        printf("Switched to user '%s'.\n", username);
    } else {
        printf("Error switching user.\n");
    }
}
void killProcess() {
    pid_t pid;
    printf("Enter the PID of the process to kill: ");
    scanf("%d", &pid);

    if (kill(pid, SIGKILL) == 0) {
        printf("Process with PID %d killed.\n", pid);
    } else {
        perror("Error killing process");
    }
}

void createProcess() {
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0) {
        // Code inside this block will be executed by the child process
        printf("Child process is running (PID: %d).\n", getpid());
        // Add your specific child process logic here

        // Exit the child process
        exit(0);
    } else if (child_pid > 0) {
        // Code inside this block will be executed by the parent process
        printf("Parent process created a child with PID %d.\n", child_pid);
    } else {
        perror("Error creating process");
    }
}

void listProcesses() {
    printf("List of currently running processes:\n");

    // Use system command to execute "ps" command and list processes
    system("ps aux");
}

int main() {
    int mainChoice, subChoice;

    do {
        printf("\nMain Menu:\n");
        printf("1. User Management\n");
        printf("2. File Management\n");
        printf("3. Process Management\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                // User Management
                do {
                    printf("\nUser Management Menu:\n");
                    printf("1. Create User\n");
                    printf("2. Delete User\n");
                    printf("3. Update User\n");
                    printf("4. Switch User\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);

                    switch (subChoice) {
                        case 1:
                            createUser();
                            break;
                        case 2:
                            deleteUser();
                            break;
                        case 3:
                            updateUser();
                            break;
                        case 4:
                            switchUser();
                            break;
                        case 0:
                            printf("Returning to Main Menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (subChoice != 0);
                break;

            case 2:
            // File Management
                do {
                    printf("\nFile Management Menu:\n");
                    printf("1. Create Folder\n");
                    printf("2. Create File\n");
                    printf("3. Change file rights\n");
                    printf("4. Search file\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);

                    switch (subChoice) {
                        case 1:
                            createFolder();
                            break;
                        case 2:
                            createFile();
                            break;
                        case 3:
                            changeFileRights();
                            break;
                        case 4:
                            searchFile();
                            break;
                        case 0:
                            printf("Returning to Main Menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (subChoice != 0);
                break;

            case 3:
                // Process Management
                do {
                    printf("\nProcess Management Menu:\n");
                    printf("1. Kill Process\n");
                    printf("2. Create Process\n");
                    printf("3. List Processes\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);

                    switch (subChoice) {
                        case 1:
                            killProcess();
                            break;
                        case 2:
                            createProcess();
                            break;
                        case 3:
                            listProcesses();
                            break;
                        case 0:
                            printf("Returning to Main Menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (subChoice != 0);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (mainChoice != 0);

    return 0;
}
