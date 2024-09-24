#ifndef _PATIENTS_H_
#define _PATIENTS_H_

enum Gender {MALE, FEMALE};

typedef struct Patient {
    int id;
    int age;
    int gender;
    char* reservation;
    char* name;
    struct Patient* next;
} Patient;

extern Patient* node;


static char* copyChars(char* string, int startIndex, int numberOfChars);
void addPatient(Patient* new);
void createNewPatient(int ID, char* name, int age, int gender, char* reservation);
void parse_row_CSV(char* row);
Patient* searchPatient(int ID, int* index);

// Editing Patient
void editAge(Patient* patient, int age);
void editGender(Patient* patient, int gender);
void editName(Patient* patient, char* name);
void editReservation(Patient* patient, char* reservation);

#endif