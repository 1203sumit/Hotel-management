#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function Declarations
void add();
void list();
void edit();
void delete1();
void search();
void availableRooms();
void setcolor(int);
void login();

// Structure Declaration
struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[35];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
}s;

void setcolor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void login() {
    int attempts = 0;
    char uname[10], pword[10];
    const char user[10] = "sumit";
    const char pass[10] = "1203";
    
    do {
        system("cls");
        printf("\n  **************************  sumit hotel  **************************  ");
        printf("\n  **************************  welcome to login page **************************  ");
        printf("\n                       ENTER USERNAME: ");
        scanf("%9s", uname);
        printf("                       ENTER PASSWORD: ");
        int i = 0;
        while (i < 9) {
            pword[i] = getch();
            if (pword[i] == 13) break;
            else printf("*");
            i++;
        }
        pword[i] = '\0';

        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            printf("\n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL");
            break;
        } else {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCCESSFUL");
            attempts++;
            getch();
        }
    } while (attempts < 3);

    if (attempts >= 3) {
        printf("\nSorry, you have entered the wrong username and password three times!");
        exit(0);
    }
    system("cls");
}

int main() {
    time_t t;
    time(&t);
    char choice;
    
    login();
    system("cls");
    
    while (1) {
        system("cls");
        setcolor(10);
        for (int i = 0; i < 80; i++) printf("-");
        printf("\n   ******************************  |MAIN MENU|  ***************************** \n");
        for (int i = 0; i < 80; i++) printf("-");
        printf("\n\n\t\t *Please enter your choice for menu*:\n\n");
        printf(" \n Enter 1 -> Book a room");
        printf("\n Enter 2 -> View Customer Record");
        printf("\n Enter 3 -> Delete Customer Record");
        printf("\n Enter 4 -> Search Customer Record");
        printf("\n Enter 5 -> Edit Record");
        printf("\n Enter 6 -> View Available Rooms");
        printf("\n Enter 7 -> Exit");
        printf("\n");
        for (int i = 0; i < 80; i++) printf("-");
        printf("\nCurrent date and time : %s", ctime(&t));
        for (int i = 0; i < 80; i++) printf("-");

        choice = getche();
        choice = toupper(choice);
        switch (choice) {
            case '1':
                add();
                break;
            case '2':
                list();
                break;
            case '3':
                delete1();
                break;
            case '4':
                search();
                break;
            case '5':
                edit();
                break;
            case '6':
                availableRooms();
                break;
            case '7':
                system("cls");
                printf("\n\n\t *****THANK YOU*****");
                printf("\n\t FOR TRUSTING OUR SERVICE");
                exit(0);
                break;
            default:
                system("cls");
                printf("Incorrect Input");
                printf("\n Press any key to continue");
                getch();
        }
    }
}

void add() {
    FILE *f;
    char test;
    int validRoomNumbers[] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 
                              111, 112, 113, 114, 115, 116, 117, 118, 119, 120};
    int validRoomCount = sizeof(validRoomNumbers) / sizeof(validRoomNumbers[0]);

    f = fopen("add.txt", "a+");
    if (f == NULL) {
        f = fopen("add.txt", "w+");
        system("cls");
        printf("Please hold on while we set up our database on your computer!!");
        printf("\n Process completed, press any key to continue!! ");
        getch();
    }

    while (1) {
        int roomNumberValid = 0;
        int roomAlreadyBooked = 0;

        system("cls");
        printf("\n Enter Customer Details:");
        printf("\n**************************");

        // Validate room number
        while (!roomNumberValid || roomAlreadyBooked) {
            roomAlreadyBooked = 0;

            printf("\n Enter Room number: ");
            scanf("%9s", s.roomnumber);
            fflush(stdin);

            // Check if room number is valid
            for (int i = 0; i < validRoomCount; i++) {
                if (atoi(s.roomnumber) == validRoomNumbers[i]) {
                    roomNumberValid = 1;
                    break;
                }
            }

            if (!roomNumberValid) {
                printf("\nInvalid Room Number! Please enter a valid room number.\n");
                continue;
            }

            // Check if room is already booked
            FILE *tempFile = fopen("add.txt", "r");
            struct CustomerDetails temp;
            while (fread(&temp, sizeof(temp), 1, tempFile) == 1) {
                if (atoi(temp.roomnumber) == atoi(s.roomnumber)) {
                    roomAlreadyBooked = 1;
                    printf("\nRoom %s is already booked! Please choose another room.\n", s.roomnumber);
                    break;
                }
            }
            fclose(tempFile);
        }

        printf("Enter Name: ");
        scanf("%19s", s.name);
        printf("Enter Address: ");
        scanf("%24s", s.address);
        printf("Enter Phone Number: ");
        scanf("%10s", s.phonenumber);
        printf("Enter Nationality: ");
        scanf("%14s", s.nationality);
        printf("Enter Email: ");
        scanf("%19s", s.email);
        printf("Enter Period (in days): ");
        scanf("%9s", s.period);
        printf("Enter Arrival date (dd/mm/yyyy): ");
        scanf("%9s", s.arrivaldate);
        
        fwrite(&s, sizeof(s), 1, f);
        fflush(stdin);
        printf("\n\n1 Room is successfully booked!!");
        printf("\n Press ESC key to exit, any other key to add another customer detail: ");
        test = getche();
        if (test == 27) break;
    }

    fclose(f);
}

void list() {
    FILE *f;
    int i;
    f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    system("cls");
    printf("ROOM    NAME\t ADDRESS\t PHONENUMBER\t NATIONALITY\t EMAIL\t PERIOD\t ARRIVALDATE\n");

    for (i = 0; i < 118; i++) printf("-");
    while (fread(&s, sizeof(s), 1, f) == 1) {
        printf("\n%s \t%s \t%s \t%s \t%s \t%s \t%s \t%s",
               s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate);
    }
    printf("\n");
    for (i = 0; i < 118; i++) printf("-");
    
    fclose(f);
    getch();
}

void delete1() {
    FILE *f, *t;
    char roomnumber[20];
    int found = 0;

    f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    t = fopen("temp.txt", "w");
    if (t == NULL) {
        printf("Error opening file!");
        fclose(f);
        exit(1);
    }

    system("cls");
    printf("Enter the Room Number of the customer to be deleted from the database: ");
    fflush(stdin);
    scanf("%19s", roomnumber);

    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) != 0) {
            fwrite(&s, sizeof(s), 1, t);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(t);

    remove("add.txt");
    rename("temp.txt", "add.txt");

    if (found) {
        printf("\n\nThe Customer is successfully removed....");
    } else {
        printf("\n\nRecords of Customer with Room number %s not found!!", roomnumber);
    }

    getch();
}

void search() {
    FILE *f;
    char roomnumber[20];
    int found = 0;

    f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    system("cls");
    printf("Enter Room number of the customer to search its details: ");
    fflush(stdin);
    scanf("%19s", roomnumber);

    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 1;
            printf("\n\tRecord Found\n ");
            printf("\nRoom Number: %s", s.roomnumber);
            printf("\nName: %s", s.name);
            printf("\nAddress: %s", s.address);
            printf("\nPhone number: %s", s.phonenumber);
            printf("\nNationality: %s", s.nationality);
            printf("\nEmail: %s", s.email);
            printf("\nPeriod: %s", s.period);
            printf("\nArrival date: %s", s.arrivaldate);
            break;
        }
    }

    if (!found) {
        printf("\n\tRequested Customer could not be found!");
    }

    getch();
    fclose(f);
}

void edit() {
    FILE *f;
    char roomnumber[20];
    long int size = sizeof(s);
    int found = 0;

    f = fopen("add.txt", "r+");
    if (f == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    system("cls");
    printf("Enter Room number of the customer to edit: ");
    fflush(stdin);
    scanf("%19s", roomnumber);

    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 1;
            printf("\nEnter new details for the customer:");
            printf("\nRoom Number: ");
            scanf("%3s", s.roomnumber);
            printf("Name: ");
            scanf("%10s", s.name);
            printf("Address: ");
            scanf("%24s", s.address);
            printf("Phone number: ");
            scanf("%10s", s.phonenumber);
            printf("Nationality: ");
            scanf("%14s", s.nationality);
            printf("Email: ");
            scanf("%19s", s.email);
            printf("Period (in days): ");
            scanf("%9s", s.period);
            printf("Arrival date (dd/mm/yyyy): ");
            scanf("%9s", s.arrivaldate);

            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            break;
        }
    }

    if (found) {
        printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
    } else {
        printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
    }

    fclose(f);
    getch();
}

void availableRooms() {
    FILE *f;
    int validRoomNumbers[] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 
                              111, 112, 113, 114, 115, 116, 117, 118, 119, 120};
    int validRoomCount = sizeof(validRoomNumbers) / sizeof(validRoomNumbers[0]);
    int found;

    f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    system("cls");
    printf("Available Rooms:\n");

    for (int i = 0; i < validRoomCount; i++) {
        found = 0;
        struct CustomerDetails temp;
        while (fread(&temp, sizeof(temp), 1, f) == 1) {
            if (atoi(temp.roomnumber) == validRoomNumbers[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Room %d is available\n", validRoomNumbers[i]);
        }
        rewind(f);
    }

    fclose(f);
    getch();
}
