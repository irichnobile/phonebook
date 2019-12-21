//******************************************************************************
//  CECS130NobileIanLab_8.c     Author: Ian Nobile
//  
//  Program_description: this program uses an array of structures to hold the 
//  contact information of as many friends as a user wants. Functions to add or 
//  delete entries in the phone book and to print valid phone book entries have 
//  been created; phone book entries that are invalid or NULL (0) do not 
//  display; and memory is allocated and freed as necessary. It is now also 
//  possible for users to alphabetically sort the list of entries by name 
//  (first or last), find a phone number for a given name, randomly select a 
//  friend from the phonebook for you to call,  delete everyone from the 
//  phonebook at the same time and store all phonebook entries into and 
//  retrieve entries from a location/file-name specified by the user.
//  
//  Lab section: 01
//  Due Date: 2 November 2018
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include<windows.h>


//Creates Phonebook structure:
typedef struct Phonebook {
    char cFirstName[255];
    char cLastName[255];
    char cPhoneNumber[255];
} pb;

/*Some of these function create pointers to new blocks of memory and thus must 
return those (potentially) new pointers:*/
pb* AddFriend(pb*, int*);
pb* DeleteFriend(pb*, int*);
void DisplayPhonebook(pb*, int*);
pb* SortAlphabetically(pb*, int*);
void FindbyName(pb*, int*);
void RandomFriend(pb*, int*);
pb* ClearAll(pb*, int*);
void BackupPhonebook(pb*, int*);
pb* UploadBackup(pb*, int*);


int main() {

    //Sets up the "default" phonebook:
    int iNumContacts = 4;
    pb* contacts = malloc(iNumContacts * sizeof(pb));
    strcpy(contacts[0].cFirstName, "Bob");
    strcpy(contacts[0].cLastName, "Smith");
    strcpy(contacts[0].cPhoneNumber, "123-4567");
    strcpy(contacts[1].cFirstName, "John");
    strcpy(contacts[1].cLastName, "Doe");
    strcpy(contacts[1].cPhoneNumber, "893-4567");
    strcpy(contacts[2].cFirstName, "Dr. Roman");
    strcpy(contacts[2].cLastName, "Yampolskiy");
    strcpy(contacts[2].cPhoneNumber, "CECS-130-1,2");
    strcpy(contacts[3].cFirstName, "Jenny");
    strcpy(contacts[3].cLastName, "Keller");
    strcpy(contacts[3].cPhoneNumber, "1(628)867-5309");

    srand((unsigned int)time(NULL));
    int iUserSelection = -1;

    //--------------------------------------------------------------------------
    //  The Main Menu
    //--------------------------------------------------------------------------
    while (iUserSelection != 0) {
        printf("The Phonebook App\n");
        printf("1)\tAdd Friend\n");
        printf("2)\tDelete Friend\n");
        printf("3)\tDisplay Phonebook\n");
        printf("4)\tSort Alphabetically\n");
        printf("5)\tFind by Name\n");
        printf("6)\tRandom Friend\n");
        printf("7)\tClear All\n");
        printf("8)\tBackup Your Phonebook\n");
        printf("9)\tUpload Your Backup\n");
        printf("0)\tExit\n\n");
        printf("What would you like to do? ");
        scanf("%d", &iUserSelection);

        switch (iUserSelection) {
            //------------------------------------------------------------------
            //  Add contact to phonebook
            //------------------------------------------------------------------
            case 1:
                printf("You selected \"Add Friend.\"\n");
                contacts = AddFriend(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Delete contact from phonebook
            //------------------------------------------------------------------
            case 2:
                printf("You selected \"Delete Friend.\"\n");
                contacts = DeleteFriend(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Diplay all contacts
            //------------------------------------------------------------------
            case 3:
                printf("You selected \"Display Phonebook.\"\n");
                DisplayPhonebook(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Sort contacts in phonebook
            //------------------------------------------------------------------
            case 4:
                printf("You selected \"Sort Alphabetically.\"\n");
                contacts = SortAlphabetically(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Find contact by first or last name
            //------------------------------------------------------------------
            case 5:
                printf("You selected \"Find by Name.\"\n");
                FindbyName(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Receive the info of a contact selected at random
            //------------------------------------------------------------------
            case 6:
                printf("You selected \"Random Friend.\"\n");
                RandomFriend(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Delete all contacts from phonebook
            //------------------------------------------------------------------
            case 7:
                printf("You selected \"Clear All.\"\n");
                contacts = ClearAll(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Download .txt version of phonebook
            //------------------------------------------------------------------
            case 8:
                printf("You selected \"Backup Your Phonebook.\"\n");
                BackupPhonebook(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;

            //------------------------------------------------------------------
            //  Upload .txt version of phonebook
            //------------------------------------------------------------------
            case 9:
                printf("You selected \"Upload Your Backup.\"\n");
                contacts = UploadBackup(contacts, &iNumContacts);
                system("pause");
                system("cls");
                break;


            //the exit case
            case 0:
                break;

            //to catch any bad input
            default:
                printf("Sorry, but that's not a valid option.\n\n");
                system("pause");
                system("cls");
                break;
        }//end switch

    }//end while

    //deallocates phonebook memory before exiting:
    free(contacts);
    system("cls");
    
    //bids the user farewell:
    printf("Thank you for using the Phonebook app.\nGoodbye!\n\n");
    system("pause");

}//end main



pb* AddFriend(pb* contacts, int* iNumContacts) {
    char cAddFirst[255];
    char cAddLast[255];
    char cAddNum[255];

    //allocates memory for new contact:
    *iNumContacts += 1;
    contacts = realloc(contacts, *iNumContacts * sizeof(pb));

    //takes user input
    printf("\nPlease enter your friend's first name. ");
    scanf("%s", cAddFirst);
    printf("Please enter your friend's last name. ");
    scanf("%s", cAddLast);
    printf("Now, please enter your friend's phone number. ");
    scanf("%s", cAddNum);
    
    //adds new contact to newly allocated space in phonebook:
    strcpy(contacts[*iNumContacts - 1].cFirstName, cAddFirst);
    strcpy(contacts[*iNumContacts - 1].cLastName, cAddLast);
    strcpy(contacts[*iNumContacts - 1].cPhoneNumber, cAddNum);
    printf("\nYour friend %s %s has been added!\n\n", cAddFirst, cAddLast);

    //send revised phonebook back to the main function:
    return contacts; 

}//end AddFriend


pb* DeleteFriend(pb* contacts, int* iNumContacts) {
    int i;
    char cDel[255];
    int iDelLoc = -1;

    printf("\nPlease enter your ex-friend's first name, last name or phone "
        "number. ");
    scanf("%s", cDel);

    //finds cell index of target contact:
    for (i = 0;i < *iNumContacts;i++) {
        if (strcmp(contacts[i].cFirstName, cDel) == 0 || //or,
            strcmp(contacts[i].cLastName, cDel) == 0 || //or,
            strcmp(contacts[i].cPhoneNumber, cDel) == 0) {
            iDelLoc = i;
            break;
        }//end if
    }//end for
    
    //if the contact was not found:
    if (cDel == -1) {
        printf("\nSorry, but I couldn't find a contact associated with "
            "\"%s.\"\n\n", cDel);
        return contacts;
    }//end notfound if

    else {
        //copies each proceeding friend up one cell, over the deleted contact:
        for (i = iDelLoc;i < (*iNumContacts - 1);i++) {
            contacts[i] = contacts[i + 1];
            /*
            strcpy(contacts[i].cFirstName, contacts[i + 1].cFirstName);
            strcpy(contacts[i].cLastName, contacts[i + 1].cLastName);
            strcpy(contacts[i].cPhoneNumber, contacts[i + 1].cPhoneNumber);
            */

        }//end for

        //deletes the final (now duplicate) cell and shrinks phonebook size:
        *iNumContacts -= 1;
        contacts = realloc(contacts, *iNumContacts * sizeof(pb));
        printf("\nYour ex-friend \"%s\" has been erased.\n\n", cDel);
        return contacts;
    }//end found else

}//end DeleteFriend


void DisplayPhonebook(pb* contacts, int* iNumContacts) {
    int i;
    printf("\n\tCONTACTS\n");
    for (i = 0;i < *iNumContacts;i++) {
        printf("%s ", contacts[i].cFirstName);
        printf("%s\t", contacts[i].cLastName);
        printf("%s\n", contacts[i].cPhoneNumber);
    }
    printf("\n");

}//end DisplayPhonebook


pb* SortAlphabetically(pb* contacts, int* iNumContacts) {
    int iUserSelection = 0;
    printf("Would you like to sort by first name (1) or last name (2)? ");
    scanf("%d", &iUserSelection);

    //to catch any bad input:
    while (iUserSelection != 1 && iUserSelection != 2) {
        printf("\nSorry, I didn't understand that response!\n\n");
        printf("Would you like to sort by first name (1) or last name (2)? ");
        scanf("%d", &iUserSelection);
    }//end while

    if (iUserSelection == 1) {//by first name
        if (*iNumContacts <= 50) {
            //insertionsort for small phonebooks:
            int i, j;
            
            //allocates memory for temp object:
            pb* temp = malloc(1 * sizeof(pb));

            //for each contact in your phonebook:
            for (i = 0; i < *iNumContacts; i++) {
                
                //sets temp equal to the contact in question:
                temp[0] = contacts[i];
                j = i - 1;
                
                /*until you reach the beginning of the list or
                the contact's first name is in the right alphabetical position:*/
                while (j >= 0 && ((strcmp(contacts[j].cFirstName,
                    temp[0].cFirstName)) > 0)) {
                    
                    //shift all previous contacts down one cell:
                    contacts[j + 1] = contacts[j];
                    j = j - 1;
                }//end while

                //then place the contact down over the (now duplicate) cell
                contacts[j + 1] = temp[0];
            }//end for

             //deallocates temp memory:
            free(temp);

        }//end insertsort if

        else {
            //quicksort for large phonebooks:
            int iLow = 0;
            int iHigh = *iNumContacts - 1;
            int iMed;
            //creates an array of int:
            int* stack = malloc((iHigh - iLow + 1) * sizeof(int));
            int top = -1;
            //stack[0] = low index, stack[1] = high index:
            stack[++top] = iLow;
            stack[++top] = iHigh;
            //temp contact spaces:
            pb* temp = malloc(1 * sizeof(pb));
            pb* pivot = malloc(1 * sizeof(pb));
            //while the stack is not empty...
            while (top >= 0) {
                iHigh = stack[top--];
                iLow = stack[top--];
                //pivot = end contact(NOT ideal; should be median of three)
                pivot[0] = contacts[iHigh];
                /*
                for later, median:
                ((a - b) * (b - c) > -1 ? b : ((a - b) * (a - c) < 1 ? a : c));
                contacts[iLow].cFirstName vs. 
                contacts[(iHigh + iLow) / 2].cFirstName vs.
                contacts[iHigh].cFirstName;
                */

                //i looks for values greater than pivot
                int i = (iLow - 1);
                //j looks for values less than pivot
                for (int j = iLow; j <= iHigh - 1; j++) {
                    //ascending: >= 0, descending: <= 0:
                    if (strcmp(pivot[0].cFirstName, 
                        contacts[j].cFirstName) >= 0) {
                        i++;
                        //swaps greater and lesser
                        temp[0] = contacts[i];
                        contacts[i] = contacts[j];
                        contacts[j] = temp[0];

                    }//end if

                }//end for

                //switches pivot with end contact:
                temp[0] = contacts[i + 1];
                contacts[i + 1] = contacts[iHigh];
                contacts[iHigh] = temp[0];
                
                //sets Low and High indexes for next iteration
                if (i > iLow) {
                    stack[++top] = iLow;
                    stack[++top] = i;
                }
                if (i + 2 < iHigh) {
                    stack[++top] = i + 2;
                    stack[++top] = iHigh;
                }
            }//end while

            free(pivot);
            free(temp);

        }//end quicksort else

        printf("\nYour phonebook has been sorted by first name.\n\n");
        return contacts; //returns the new phonebook

    }//end firstname if

    else {//by surname
        if (*iNumContacts <= 50) {
            //insertionsort for small phonebooks:
            int i, j;
            pb* temp = malloc(1 * sizeof(pb));
            for (i = 0; i < *iNumContacts; i++) {
                temp[0] = contacts[i];
                j = i - 1;
                while (j >= 0 && ((strcmp(contacts[j].cLastName,
                    temp[0].cLastName)) > 0)) {
                    contacts[j + 1] = contacts[j];
                    j = j - 1;
                }//end while
                contacts[j + 1] = temp[0];
            }//end for
            free(temp);
        }//end insertsort if
        else {
            //quicksort for large phonebooks:
            int iLow = 0;
            int iHigh = *iNumContacts - 1;
            int* stack = malloc((iHigh - iLow + 1) * sizeof(int));
            int top = -1;
            stack[++top] = iLow;
            stack[++top] = iHigh;
            pb* temp = malloc(1 * sizeof(pb));
            pb* x = malloc(1 * sizeof(pb));
            while (top >= 0) {
                iHigh = stack[top--];
                iLow = stack[top--];
                x[0] = contacts[iHigh];
                int i = (iLow - 1);
                for (int j = iLow; j <= iHigh - 1; j++) {
                    if(strcmp(x[0].cLastName, contacts[j].cLastName) >= 0) {
                        i++;
                        temp[0] = contacts[i];
                        contacts[i] = contacts[j];
                        contacts[j] = temp[0];
                    }//end if
                }//end for
                temp[0] = contacts[i + 1];
                contacts[i + 1] = contacts[iHigh];
                contacts[iHigh] = temp[0];
                if (i > iLow) {
                    stack[++top] = iLow;
                    stack[++top] = i;
                }
                if (i + 2 < iHigh) {
                    stack[++top] = i + 2;
                    stack[++top] = iHigh;
                }//end high if
            }//end while
            free(x);
            free(temp);
        }//end quicksort else
        printf("\nYour phonebook has been sorted by last name.\n\n");
        return contacts;
    }//end lastname else

}//end SortAlphabetically


void FindbyName(pb* contacts, int* iNumContacts) {
    char sByName[30];
    int iByName = -1;
    
    printf("Please enter your friend's first or last name: ");
    scanf("%s", sByName);
    
    //finds cell index of target contact:
    for (int i = 0;i < *iNumContacts;i++) { 
        if (strcmp(contacts[i].cFirstName, sByName) == 0 || //or,
            strcmp(contacts[i].cLastName, sByName) == 0 || //and just in case:
            strcmp(contacts[i].cPhoneNumber, sByName) == 0) {
            iByName = i;
            break;
        }//end if
    }//end for

    if (iByName == -1) {//if not found:
        printf("\nSorry, but I couldn't find a contact associated with ");
        printf("\"%s.\"\n\n", sByName);
    }
    else {
        printf("\n%s %s\'s phone number is: %s.\n\n", 
            contacts[iByName].cFirstName, 
            contacts[iByName].cLastName, 
            contacts[iByName].cPhoneNumber);
    }//end else

}//end FindbyName


void RandomFriend(pb* contacts, int* iNumContacts) {
    printf("\nSelecting a random contact for you...\n");
    Sleep(1 * 1000);
    int iRandomNum = (rand() % (*iNumContacts));
    printf("It's %s %s! Their number is: %s.\n", 
        contacts[iRandomNum].cFirstName, 
        contacts[iRandomNum].cLastName, 
        contacts[iRandomNum].cPhoneNumber);

}//end RandomFriend


pb* ClearAll(pb* contacts, int* iNumContacts) {
    //shinks phonebook size:
    *iNumContacts = 0;
    contacts = realloc(contacts, 1 * sizeof(pb));
    
    //blanks all fields:
    strcpy(contacts[0].cFirstName, "");
    strcpy(contacts[0].cLastName, "");
    strcpy(contacts[0].cPhoneNumber, "");
    printf("\nYour friends have all been erased.\n\n");
    return contacts;

}//end ClearAll


void BackupPhonebook(pb* contacts, int* iNumContacts) {
    int iUserSelection = 0;
    FILE* ptrDownload;

    printf("To specify a filename and location, press 1. To use the default "
        "filename, press 2. ");
    scanf("%d", &iUserSelection);
    
    //to catch any bad input:
    while (iUserSelection != 1 && iUserSelection != 2) {
        printf("\nSorry, I didn't understand that response!\n\n");
        printf("Would you like to sort by first name (1) or last name (2)? ");
        scanf("%d", &iUserSelection);
    }//end while

    if (iUserSelection == 1) {//user-defined filename
        char cUserFilename[255];
        char cDat[] = ".dat";
        printf("Please enter the desired /path/name of your file: ");
        scanf("%s", cUserFilename);
        
        //add a ".dat" to the end of user inputted name/path
        ptrDownload = fopen(strcat(cUserFilename, cDat), "w");
    }//end if
    else {//default filename: "pb.dat"
        ptrDownload = fopen("pb.dat", "w");
    }//end else

    if (ptrDownload == NULL) { //Checks that file was created
        printf("File could not be created.");
    }
    else {
        //adds number of contacts and newline to beginning of .dat file
        fprintf(ptrDownload, "%d\n", *iNumContacts);
        printf("Download started.\n\n");
        for (int i = 0;i < *iNumContacts;i++) { //writes contacts to file
            fprintf(ptrDownload, "%s %s\t%s\n", 
                contacts[i].cFirstName, 
                contacts[i].cLastName, 
                contacts[i].cPhoneNumber);
        }//end for
        Sleep(1 * 1000);
        printf("Download complete.\n");
    }//end else

    fclose(ptrDownload); //Closes the file
    return;

}//end BackupPhonebook


pb* UploadBackup(pb* contacts, int* iNumContacts) {
    int iUserSelection = -1;
    FILE* ptrUpload;

    printf("To specify a filename, press 1. To just use \"pb.dat\", press 2. ");
    scanf("%d", &iUserSelection);
    
    //to catch any bad input:
    while (iUserSelection != 1 && iUserSelection != 2) {
        printf("\nSorry, I didn't understand that response!\n\n");
        printf("Would you like to sort by first name (1) or last name (2)? ");
        scanf("%d", &iUserSelection);
    }//end while

    if (iUserSelection == 1) {
        char cUserFilename[255];
        char cDat[] = ".dat";
        printf("Please enter the name/path of your backup. ");
        scanf("%s", cUserFilename);

        //read only open:
        ptrUpload = fopen(strcat(cUserFilename, cDat), "r");
    }
    else {
        ptrUpload = fopen("pb.dat", "r");
    }

    if (ptrUpload == NULL) { //checks that file is present:
        printf("File not found.\n");
    }
    else {
        char cUpFirst[255];
        char cUpLast[255];
        char cUpNum[255];
        
        //Reads number of contacts from file:
        fscanf(ptrUpload, "%d", iNumContacts); 

        //Resizes dynamic array to fit backed-up contacts:
        contacts = realloc(contacts, *iNumContacts * sizeof(pb));
        
        printf("Upload started.\n\n");
        for (int i = 0;i < *iNumContacts;i++) {
            //reads names/numbers from file and stores them in char arrays:
            fscanf(ptrUpload, "%s%s%s[^\n]", cUpFirst, cUpLast, cUpNum);
            //copies each name/number from char array to phonebook:
            strcpy(contacts[i].cFirstName, cUpFirst);
            strcpy(contacts[i].cLastName, cUpLast);
            strcpy(contacts[i].cPhoneNumber, cUpNum);
        }//end for
        Sleep(1 * 1000);//for effect
        printf("Upload complete.\n");
        fclose(ptrUpload); //closes file
    }//end else

    return contacts; //returns location of (new) pointer

}//end UploadBackup

