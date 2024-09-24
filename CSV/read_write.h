#ifndef _READ_WRITE_H_
#define _READ_WRITE_H_

#include "../Patients/patients.h"

// MAX number of characters in a row
#define MAX_CHARS 1000
#define CSV_FILE "CSV/patient.csv"
static char row [MAX_CHARS];
// Read CSV file into Patients (linked list)
void readCSV(void);
// Write a patient into CSV file
void writeCSV(Patient* patient);
// write edits
// This functions will work at the end of the 
// app to add all the edits 
void editCSV();

#endif