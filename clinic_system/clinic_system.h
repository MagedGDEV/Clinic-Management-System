#ifndef _CLINIC_SYSTEM_H_
#define  _CLINIC_SYSTEM_H_

#include <stdbool.h>

#define DIVIDOR_0 "----------------------------------------------------------\n"

static int mode = 0;
static const char password[] = "asd123qwe";
static bool edited = false;
static bool isCsvLoaded = false;

extern bool isStarting;

bool home(void);

static void readingSavedData(void);
static char welcomeMessage(void);
static void chooseMode(void);
static void exitApp(void);
// User mode  -------------------------
static void userMode(void);
// Admin mode -------------------------
static void adminMode(void);
static bool isCorrectPass(void);
// Admin Mode -------- Viewing --------
static void viewAllPatients(void);
// Admin Mode -------- Adding ---------
static int generateRandomNumber(void);
static void addNewPatient(void);
// Admin Mode -------- Editing --------
static void editPatient(void);
#endif