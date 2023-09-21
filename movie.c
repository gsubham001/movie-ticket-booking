#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures to represent user and booking data
struct User {
    char username[50];
    char password[50];
};

struct Booking {
    char username[50];
    char movieName[100];
    char showTime[50];
};

// Define structures to represent movie data
struct Movie {
    char name[100];
    char timings[50];
};

// Function prototypes
void registerUser();
int loginUser();
void bookMovieTicket(const char* username);
void showMovies();
void showBookingStatus(const char* username);
void saveUserData();
void loadUserData();
void saveBookingData();
void loadBookingData();

// Global variables
struct User users[100];     // Array to store user data
struct Booking bookings[100]; // Array to store booking data
struct Movie movies[10];     // Array to store movie data
int userCount = 0;           // Number of registered users
int bookingCount = 0;        // Number of bookings
int movieCount = 0;          // Number of movies
char currentUsername[50];    // To track the currently logged-in user

int main() {
    loadUserData();
    loadBookingData();

    int choice;

    // Add some example movies
    strcpy(movies[movieCount].name, "Movie 1");
    strcpy(movies[movieCount].timings, "10:00 AM");
    movieCount++;

    strcpy(movies[movieCount].name, "Movie 2");
    strcpy(movies[movieCount].timings, "2:00 PM");
    movieCount++;

    while (1) {
        printf("Welcome to the Movie Booking System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Book Movie Ticket\n");
        printf("4. Show Movies\n");
        printf("5. Check Booking Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser() == 1) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed. Please try again.\n");
                }
                break;
            case 3:
                if (currentUsername[0] != '\0') {
                    bookMovieTicket(currentUsername);
                } else {
                    printf("Please log in first.\n");
                }
                break;
            case 4:
                showMovies();
                break;
            case 5:
                if (currentUsername[0] != '\0') {
                    showBookingStatus(currentUsername);
                } else {
                    printf("Please log in first.\n");
                }
                break;
            case 6:
                saveUserData();
                saveBookingData();
                printf("Thank you for using the Movie Booking System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void registerUser() {
    printf("Enter a username: ");
    scanf("%s", users[userCount].username);
    printf("Enter a password: ");
    scanf("%s", users[userCount].password);
    userCount++;
    printf("Registration successful!\n");
}

int loginUser() {
    char username[50];
    char password[50];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            strcpy(currentUsername, username);
            return 1; // Login successful
        }
    }

    return 0; // Login failed
}

void bookMovieTicket(const char* username) {
    int choice;
    printf("Available movies:\n");
    showMovies();
    printf("Enter the number of the movie you want to book: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= movieCount) {
        printf("Enter show time: ");
        scanf("%s", bookings[bookingCount].showTime);
        strcpy(bookings[bookingCount].username, username);
        strcpy(bookings[bookingCount].movieName, movies[choice - 1].name);
        bookingCount++;
        printf("Movie ticket booked successfully!\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void showMovies() {
    printf("Available Movies:\n");
    for (int i = 0; i < movieCount; i++) {
        printf("%d. %s (%s)\n", i + 1, movies[i].name, movies[i].timings);
    }
}

void showBookingStatus(const char* username) {
    printf("Booking status for user '%s':\n", username);

    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(username, bookings[i].username) == 0) {
            printf("Booking %d: Movie: %s, Show Time: %s\n", i + 1, bookings[i].movieName, bookings[i].showTime);
        }
    }
}

void saveUserData() {
    FILE* userFile = fopen("user_data.txt", "w");
    if (userFile == NULL) {
        printf("Error opening user data file for writing.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(userFile, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(userFile);
}

void loadUserData() {
    FILE* userFile = fopen("user_data.txt", "r");
    if (userFile == NULL) {
        return; // No user data file exists yet
    }

    while (fscanf(userFile, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }

    fclose(userFile);
}

void saveBookingData() {
    FILE* bookingFile = fopen("booking_data.txt", "w");
    if (bookingFile == NULL) {
        printf("Error opening booking data file for writing.\n");
        return;
    }

    for (int i = 0; i < bookingCount; i++) {
        fprintf(bookingFile, "%s %s %s\n", bookings[i].username, bookings[i].movieName, bookings[i].showTime);
    }

    fclose(bookingFile);
}

void loadBookingData() {
    FILE* bookingFile = fopen("booking_data.txt", "r");
    if (bookingFile == NULL) {
        return; // No booking data file exists yet
    }

    while (fscanf(bookingFile, "%s %s %s", bookings[bookingCount].username, bookings[bookingCount].movieName, bookings[bookingCount].showTime) != EOF) {
        bookingCount++;
    }

    fclose(bookingFile);
}
