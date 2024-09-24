#include "patients.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CSV/read_write.h"

Patient* node = NULL;
static Patient* last = NULL;

static char* copyChars(char* string, int startIndex, int numberOfChars){
    char* stringCopied = (char* ) malloc((numberOfChars + 1) * sizeof(char));
    strncpy(stringCopied, string + startIndex, numberOfChars);
    stringCopied[numberOfChars] = '\0';
    return stringCopied;
}

void addPatient(Patient* new){
    new->next = NULL;
    if (node == NULL){
        node = new;
        last = node;
    }
    else {
        last->next = new;
        last = last->next;
    }
}

void createNewPatient(int ID, char* name, int age, int gender, char* reservation){
    Patient* new = (Patient *)malloc(sizeof(Patient));
    new->id = ID;
    new->name = name;
    new->age = age;
    new->gender = gender;
    new->reservation = reservation;
    addPatient(new);
    writeCSV(new);
    free(new);
}

void parse_row_CSV(char* row){

    Patient* new = (Patient *)malloc(sizeof(Patient));
    int i = 0 , column = 0, start = 0;
    while (row[i] != '\0'){
        if (row[i] == ','){
            char* string = copyChars(row, start, i - start);
            switch (column){
                case 0: 
                    new->id = atoi(string);
                    free(string); // empty unused string
                    break;
                case 1:
                    new->name = string;
                    string = NULL; // let one pointer points to the name
                    break;
                case 2:
                    new->age = atoi(string);
                    free(string); // empty unused string
                    break;
                case 3:
                    new->gender = string[0] == 'M' ? MALE : FEMALE;
                    free(string); // empty unused string
                    break;
                default: 
                    printf("Column number unavailable");
                    break;
            }
            start = i + 1;
            column++;
        }
        i++;
    }
    new->reservation = copyChars(row, start, i - start - 1);
    if (new->name != NULL)
        addPatient(new);
}

Patient* searchPatient(int ID, int* index){
    Patient* search = node;
    if (index != NULL)
        *index = 0;
    while (search != NULL){
        if (search->id == ID){
            index = NULL;
            return search;
        }
        search = search->next;
        if (index != NULL)
            *index++;
    }
    if (index != NULL)
        *index = -1;
    index = NULL;
    return NULL;
}

// Editing Patient -----------------------------------------------
void editAge(Patient* patient, int age){
    patient->age = age;
    patient = NULL;
}

void editGender(Patient* patient, int gender){
    patient->gender = gender;
    patient = NULL;
}

void editName(Patient* patient, char* name){
    patient->name = name;
    patient = NULL;
}

void editReservation(Patient* patient, char* reservation){
    patient->reservation = reservation;
    patient = NULL; 
}
