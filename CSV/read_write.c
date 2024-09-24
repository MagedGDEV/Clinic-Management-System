#include "read_write.h"
#include <stdio.h>
#include <string.h>


void readCSV(void) {

    FILE *csv;
    csv = fopen (CSV_FILE, "r");
    if (csv == NULL) {
        perror("Error opening file");
        return;
    }
    int rows = 0;
    while (fgets(row, sizeof(row), csv) != NULL){
        if (rows == 0){
            rows++;
            continue; // Skip first row
        } 
        parse_row_CSV(row);
    }
    fclose(csv);
}

void writeCSV(Patient* patient){

    FILE *csv;
    // "r+" is a read/write mode using this to write on the empty row
    csv = fopen(CSV_FILE, "r+");
    if (csv == NULL) {
        perror("Error opening file");
        return;
    }

    // Read until you find an empty row
    while(fgets(row, sizeof(row), csv) != NULL);
    if (patient->reservation != NULL)
        fprintf (csv,"%d,%s,%d,%s,%s \n", patient->id, patient->name, patient->age,
        (patient->gender == 0 ? "Male" : "Female"), patient->reservation);
    else 
        fprintf (csv,"%d,%s,%d,%s, \n", patient->id, patient->name, patient->age,
        (patient->gender == 0 ? "Male" : "Female"));

    fclose(csv);
}

void editCSV(){
    
    if (remove(CSV_FILE) == 0)
        printf("file deleted successfully.\n");
    else 
        perror("Error deleting the file\n");

    FILE *csv = fopen(CSV_FILE, "w");
    fprintf (csv, "ID,Name,Age,Gender,Reservation\n");
    Patient* patient = node;
    while (patient != NULL) {
        fprintf (csv,"%d,%s,%d,%s,%s\n", patient->id, patient->name, patient->age,
        (patient->gender == 0 ? "Male" : "Female"), patient->reservation);
        patient = patient->next;
    }

    fclose(csv);
}