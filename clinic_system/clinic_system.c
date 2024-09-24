#include "clinic_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Patients/patients.h"
#include "../CSV/read_write.h"


#define DIVIDOR_1 "*****************************************\n"
#define DIVIDOR_2 "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
#define HOME "Home Page\n"
#define ADMIN "Admin Page\n"
#define EXIT "Exit\n"
#define UPPER_ID_BOUND 2000
#define LOWER_ID_BOUND 1

bool isStarting = true;
static void printUserData(Patient user);
static void editPatientName(Patient user);

bool home(void){
    
    readingSavedData();
    if (!isStarting){
        // Clear the input buffer before entering any mode
        while(getchar() != '\n');
    }
    chooseMode();
    if (mode == 1){
        adminMode();
        return false;
    }
    else if (mode == 2){
        userMode();
        return false;
    }
    exitApp();
}

static void readingSavedData(void){
    if (!isCsvLoaded){
        printf(DIVIDOR_0);
        printf(DIVIDOR_0);
        printf("Reading saved data from the saving file\n");
        readCSV();
        printf("Reading data finished successfully\n");
        printf(DIVIDOR_0);
        isCsvLoaded = true;
    }
}

static char welcomeMessage(void){
    printf("Welcome to our clinic system --- Please choose from the following:\n");
    printf("    a) Admin Mode\n");
    printf("    b) User Mode\n");
    printf("    c) %s", EXIT);
    char choice;
    printf("Enter your preferred mode: ");
    scanf(" %c", &choice);
    return choice;
}

static void chooseMode(void){
    printf(DIVIDOR_0);
    char choice = welcomeMessage();
    // Loop until user enters A | a | B | b | C | c
    while (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B' && choice != 'c' && choice != 'C'){
        printf("Please enter either \'a\', \'A\', \'b\', \'B\', \'c\', \'C\': ");
        // Clear the input buffer to get only the first character at each input
        // and Ignore new lines
        while (getchar() != '\n');  
        scanf(" %c", &choice);      // The space before %c to consume any leading whitespace
    }

    if (choice == 'a' || choice == 'A')
        mode = 1;
    else if (choice == 'b' || choice == 'B') 
        mode = 2;
    else 
        mode = 3;
    printf(DIVIDOR_0);
}

static void exitApp(void){
    printf(DIVIDOR_0);
    if (edited == true){
        printf("Writing edited data into the saving file\n");
        editCSV();     
        printf("Editing data finished successfully\n");
    }
    printf("Closing the program\n");
    printf(DIVIDOR_0);
    printf(DIVIDOR_0);
    exit(0);
}

static void printUserData(Patient user){
    printf(DIVIDOR_1);
    printf("Patient %d: %s\n", user.id, user.name);
    printf("Age: %d\n", user.age);
    printf("Gender: %s\n", (user.gender == 0 ? "Male" : "Female"));
    printf("Reservation: %s\n", user.reservation);
    printf(DIVIDOR_1);
}
// User mode  -------------------------
static void userMode(void){
    printf(DIVIDOR_0);
    printf("Welcome! Enter your ID to continue and view your profile: ");
    
    int ID; char string[10]; 
    Patient* user = NULL;
    scanf(" %s", string);
    ID = atoi(string);
    if (ID != 0)
        user = searchPatient(ID, NULL);
    
    while (user == NULL){
        printf("Please enter a valid existing ID or choose from the following:\n");
        printf("    a) %s", HOME);
        printf("    b) %s", EXIT);
        printf("Enter your choice: ");
        scanf(" %s", string);
        if (strcmp(string, "a") == 0 || strcmp(string, "A") == 0){
            // This indicates to return the home page
            // without staying in the userMode function
            // To avoid stack overflow in the long run   
            return; 
        }
        else if (strcmp(string, "b") == 0 || strcmp(string, "B") == 0){
            printf(DIVIDOR_0);
            exitApp();
        }
        else {
            ID = atoi(string);
            if (ID != 0)
                user = searchPatient(ID, NULL);
        }
    }
    // Empty the buffer
    while (getchar() != '\n');
    // print user data, Choose to close or go to home page
    printUserData(*user);
    // Empty the heap
    free(user);
    user = NULL;
    printf("What would you like to do next?\n");
    printf("    a) %s", HOME);
    printf("    b) %s", EXIT);
    printf("Enter your selection: ");
    char choice;
    scanf(" %c", &choice);
    while (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B'){
        printf("Please enter either \'a\', \'A\', \'b\', \'B\': ");
        // Clear the input buffer to get only the first character at each input
        // and Ignore new lines
        while (getchar() != '\n');  
        scanf(" %c", &choice);      // The space before %c to consume any leading whitespace
    }
    if (choice == 'b' || choice == 'B')
        exitApp();
    // Reaching this point indicates to return the home page
    // without staying in the userMode function
    // To avoid stack overflow in the long run      
}
// Admin mode -------------------------
static void adminMode(void){
    printf(DIVIDOR_0);
    while (getchar() != '\n');  
    if (!isCorrectPass()){
        printf(DIVIDOR_0);
        exitApp();
    }
    printf(DIVIDOR_2);
    printf("Please choose from the following options to manage patient records and reservations\n");
    printf("    1) View all patient records\n");
    printf("    2) Add a new patient record\n");
    printf("    3) Edit an existing patient record\n");
    printf("    4) Reserve a slot with a doctor\n");
    printf("    5) Cancel a reservation\n");
    printf("    6) %s", HOME);
    printf("    7) %s", EXIT);
    printf("Enter your selection: ");
    while (getchar() != '\n');  
    char choice;
    scanf(" %c", &choice);
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5'
    && choice != '6' && choice != '7'){
        printf("Please enter either 1, 2, 3, 4, 5, 6, 7: ");
        while (getchar() != '\n');  
        scanf(" %c", &choice);
    }
    int selection = choice - '0';
    switch(selection){
        case 1: 
            viewAllPatients();
            break;
        case 2:
            addNewPatient();
            break;
        case 3:
            editPatient();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            exitApp();
            break;
    } 
}

static bool isCorrectPass(void){
    char enteredPass[20];
    printf("Enter the password: ");
    scanf(" %s", enteredPass);
    if (strcmp(enteredPass, password) != 0){
        for (int i = 0; i < 2; i++){
            enteredPass[0] = '\0';
            printf("You got %d trial%s left, Enter the correct password: ", 2-i, (i == 1 ? "" : "s"));
            scanf("%s", enteredPass);
            if (strcmp(enteredPass, password) == 0) 
                return true;
        }
    }
    else 
        return true;
    printf("You have passed the number of trials to enter the password\n");
    return false;
}
// Admin Mode -------- Viewing --------
static void viewAllPatients(void){
    printf(DIVIDOR_2);
    Patient* patient = node;
    while (patient != NULL){
        printUserData(*patient);
        patient = patient->next;
    }
    printf(DIVIDOR_2);
}
// Admin Mode -------- Adding ---------
static int generateRandomNumber(void){
    srand(time(NULL));
    return rand() % (UPPER_ID_BOUND - LOWER_ID_BOUND) + 1;
}

static void addNewPatient(void){
    printf(DIVIDOR_2);
    printf("Adding New Patient\n");
    int ID = generateRandomNumber();
    printf("The ID is automatically generated\n");
    printf("Enter the name of the patient: ");
    while (getchar() != '\n'); // empty the input buffer
    char name[100];
    // read the whole string including spaces
    fgets(name, sizeof(name), stdin);
    size_t length = strlen(name);
    // remove the new line character
    if (length > 0 && name[length - 1] == '\n')
        name[length - 1] = '\0';
    char input[10];
    printf("Enter the age of the patient: ");
    scanf(" %s", input);
    int age = atoi(input);
    while (age == 0){
        printf("Please enter a numerical value for the age of the patient: ");
        scanf(" %s", input);
        age = atoi(input);
        while (getchar() != '\n'); // empty the input buffer
    }
    printf("Please choose from the following to define the gender of the patient:\n");
    printf("    1) Male\n");
    printf("    2) Female\n");
    printf("Enter your choice: ");
    input[0] = '\0';
    scanf(" %s", input);
    while (strcmp(input , "1") != 0 && strcmp(input, "2") != 0){
        printf("Please enter either 1, 2: ");
        while (getchar() != '\n');  
        scanf(" %s", &input);
    }
    
    createNewPatient(ID, name, age, (input[0] == '1' ? MALE : FEMALE), NULL);
    printf(DIVIDOR_2);
}
// Admin Mode -------- Editing --------
static void editPatient(void){
    printf(DIVIDOR_2);
    printf("Editing patient\n");
    printf("Enter the ID of the patient: ");
    int ID; char string[10]; 
    Patient* user = NULL;
    scanf(" %s", string);
    ID = atoi(string);
    if (ID != 0)
        user = searchPatient(ID, NULL);
    while (user == NULL){
        printf("Please enter a valid existing ID or choose from the following:\n");
        printf("    a) %s", ADMIN);
        printf("    b) %s", HOME);
        printf("    c) %s", EXIT);
        printf("Enter your choice: ");
        scanf(" %s", string);
        if (strcmp(string, "a") == 0 || strcmp(string, "A") == 0){
            // This indicates to return the Admin page
            // without staying in the userMode function
            // To avoid stack overflow in the long run  
            return; 
        }
        else if (strcmp(string, "b") == 0 || strcmp(string, "B") == 0){
            // This indicates to return the home page
            // without staying in the userMode function
            // To avoid stack overflow in the long run  
        }
        else if (strcmp(string, "c") == 0 || strcmp(string, "C") == 0){
            printf(DIVIDOR_0);
            exitApp();
        }
        else {
            ID = atoi(string);
            if (ID != 0)
                user = searchPatient(ID, NULL);
        }
    }
    printf("Pick an item from the following to edit:\n");
    printf("    1) Name\n");
    printf("    2) Age\n");
    printf("    3) Gender\n");
    printf("Enter your choice: ");
    char choice; 
    while(getchar() != '\n');
    scanf(" %c", &choice);
    while (choice != '1' && choice != '2' && choice != '3'){
        printf("Please enter either 1, 2, 3: ");
        while(getchar() != '\n');
        scanf(" %c", &choice);
    }

    int selection = choice - '0';
    switch (selection){
        case 1:
            editPatientName(*user);
            break;
        case 2: 
            // edit age
            break;
        case 3: 
            // edit gender
            break;
        
    }

    edited = true;
}

static void editPatientName(Patient user){
    printf("Change patient %d name from %s to: ", user.id, user.name);
    char name[100];
    // read the whole string including spaces
    fgets(name, sizeof(name), stdin);
    size_t length = strlen(name);
    // remove the new line character
    if (length > 0 && name[length - 1] == '\n')
        name[length - 1] = '\0';
    user.name = name;
    printf("user: %s to %s", user.name, name);
    
}

