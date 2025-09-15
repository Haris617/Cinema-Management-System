#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Representation of Seat
struct Seat {
    int seatNumber;
    bool isBooked;
    string customerName;
    int ticketClass; // 1: Standard, 2: Premium, 3: Luxury
};

// Global constants
const int TOTAL_SEATS = 90;
Seat seats[TOTAL_SEATS];

// Pricing Constants
const int STANDARD_PRICE = 500;
const int PREMIUM_PRICE = 750;
const int LUXURY_PRICE = 1000;
const int GLASSES_PRICE = 200;
const int POPCORN_PRICE = 150;
const int SNACKS_PRICE = 250;

void initializeSeats();
void displaySeats();
void bookTicket();
void cancelBooking();
void searchBooking();
void saveBookings();
void displaySummaryReport();
void printTicket(const Seat& seat, bool wantsGlasses, bool wantsPopcorn, bool wantsSnacks, int hallType);
void collectFeedback();
void displayMovies();

string selectedMovie = "";
const string movies[] = { "Inception", "Avengers", "Titanic", "Jurassic Park", "The Dark Knight" };
const int TOTAL_MOVIES = 5;

int main() {
    int choice;
    initializeSeats();

    while (true) {
        cout << "=====================================" << endl;
        cout << "|     Cinema Management System      |" << endl;
        cout << "=====================================" << endl;
        cout << "|       |                           |" << endl;
        cout << "|   1.  |  Select a Movie           |" << endl;
        cout << "|   2.  |  View Available Seats     |" << endl;
        cout << "|   3.  |  Book a Ticket            |" << endl;
        cout << "|   4.  |  Cancel a Booking         |" << endl;
        cout << "|   5.  |  Search for a Booking     |" << endl;
        cout << "|   6.  |  Display Advanced Report  |" << endl;
        cout << "|   7.  |  Leave Feedback           |" << endl;
        cout << "|       |                           |" << endl;
        cout << "=====================================" << endl << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            displayMovies();
            break;
        case 2:
            displaySeats();
            break;
        case 3:
            if (selectedMovie.empty()) {
                cout << "Please select a movie first!\n";
            }
            else {
                bookTicket();
            }
            break;
        case 4:
            cancelBooking();
            break;
        case 5:
            searchBooking();
            break;
        case 6:
            displaySummaryReport();
            break;
        case 7:
            collectFeedback();
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}

void initializeSeats() {
    for (int i = 0; i < TOTAL_SEATS; i++) {
        seats[i].seatNumber = i + 1;
        seats[i].isBooked = false;
        seats[i].customerName = "";
        seats[i].ticketClass = 0;
    }
}

void displayMovies() {
    cout << "Available Movies:\n";
    for (int i = 0; i < TOTAL_MOVIES; i++) {
        cout << i + 1 << ". " << movies[i] << endl;
    }

    int movieChoice;
    cout << "\nSelect a movie by entering its number: ";
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > TOTAL_MOVIES) {
        cout << "Invalid selection. Please try again.\n";
        return;
    }

    selectedMovie = movies[movieChoice - 1];
    cout << "You have selected: " << selectedMovie << endl << endl;
}

void displaySeats() {
    if (selectedMovie.empty()) {
        cout << "Please select a movie first!\n";
        return;
    }

    int hallType;

    // Ask for hall type (3D or Normal)
    cout << "Select Cinema Hall:\n1. 3D\n2. Normal\nEnter your choice: ";
    cin >> hallType;

    if (hallType != 1 && hallType != 2) {
        cout << "Invalid hall type. Please try again." << endl;
        return;
    }

    cout << "========================" << endl;
    cout << "|     Seat Status      |" << endl;
    cout << "========================" << endl << endl;

    // Display seat availability for the selected hall type
    for (int i = 0; i < TOTAL_SEATS; i++) {
        cout << "Seat " << setw(2) << seats[i].seatNumber << "   :    ";
        if (seats[i].isBooked) {
            cout << "Booked" << endl;
        }
        else {
            cout << "Available" << endl;
        }
    }
}

void bookTicket() {
    int numberOfTickets, hallType, seatNumber, ticketClass, totalPrice = 0;
    string name;
    bool wantsGlasses = false, wantsPopcorn = false, wantsSnacks = false;

    // Select Hall Type
    cout << "Select Cinema Hall:\n1. 3D\n2. Normal\nEnter your choice: ";
    cin >> hallType;
    if (hallType != 1 && hallType != 2) {
        cout << "Invalid hall type. Please try again." << endl;
        return;
    }

    // Enter number of tickets
    cout << "Enter the number of tickets to book: ";
    cin >> numberOfTickets;

    for (int i = 0; i < numberOfTickets; i++) {
        cout << "\nBooking Ticket " << i + 1 << " of " << numberOfTickets << ":\n";

        // Select Seat
        cout << "Enter seat number to book (1-" << TOTAL_SEATS << "): ";
        cin >> seatNumber;
        if (seatNumber < 1 || seatNumber > TOTAL_SEATS || seats[seatNumber - 1].isBooked) {
            cout << "Invalid or already booked seat. Please try again." << endl;
            i--;
            continue;
        }

        // Select Ticket Class
        cout << "Select Ticket Class:\n1. Standard (Rs 500)\n2. Premium (Rs 750)\n3. Luxury (Rs 1000)\nEnter your choice: ";
        cin >> ticketClass;

        if (ticketClass == 1) {
            totalPrice += STANDARD_PRICE;
        }
        else if (ticketClass == 2) {
            totalPrice += PREMIUM_PRICE;
        }
        else if (ticketClass == 3) {
            totalPrice += LUXURY_PRICE;
        }
        else {
            cout << "Invalid ticket class. Please try again." << endl;
            i--;
            continue;
        }

        // Add 3D Glasses if applicable
        if (hallType == 1) {
            char glassesChoice;
            cout << "Do you want 3D glasses? (Rs 200) (y/n): ";
            cin >> glassesChoice;
            if (glassesChoice == 'y' || glassesChoice == 'Y') {
                wantsGlasses = true;
                totalPrice += GLASSES_PRICE;
            }
        }

        // Add Popcorn and Snacks
        char popcornChoice, snacksChoice;
        cout << "Do you want popcorn? (Rs 150) (y/n): ";
        cin >> popcornChoice;
        if (popcornChoice == 'y' || popcornChoice == 'Y') {
            wantsPopcorn = true;
            totalPrice += POPCORN_PRICE;
        }

        cout << "Do you want snacks? (Rs 250)(y/n): ";
        cin >> snacksChoice;
        if (snacksChoice == 'y' || snacksChoice == 'Y') {
            wantsSnacks = true;
            totalPrice += SNACKS_PRICE;
        }

        // Enter Customer Name
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        // Book the Seat
        seats[seatNumber - 1].isBooked = true;
        seats[seatNumber - 1].customerName = name;
        seats[seatNumber - 1].ticketClass = ticketClass;

        // Print the Ticket
        printTicket(seats[seatNumber - 1], wantsGlasses, wantsPopcorn, wantsSnacks, hallType);
    }

    // Display Total Price
    cout << "\n=====================================" << endl;
    cout << "|          Booking Summary          |" << endl;
    cout << "=====================================" << endl;
    cout << "| Movie            : " << selectedMovie << endl;
    cout << "| Number of Tickets: " << numberOfTickets << endl;
    cout << "| Hall Type        : ";
    if (hallType == 1) {
        cout << "3D";
    }
    else {
        cout << "Normal";
    }
    cout << endl;
    cout << "| Total Price      : " << totalPrice << endl;
    cout << "=====================================" << endl << endl;
}

void printTicket(const Seat& seat, bool wantsGlasses, bool wantsPopcorn, bool wantsSnacks, int hallType) {
    cout << "\n-------------------------------" << endl;
    cout << "|          TICKET            |" << endl;
    cout << "-------------------------------" << endl;
    cout << "| Movie       : " << selectedMovie << endl;
    cout << "| Seat Number : " << seat.seatNumber << endl;
    cout << "| Customer    : " << seat.customerName << endl;
    cout << "| Class       : ";
    if (seat.ticketClass == 1) {
        cout << "Standard";
    }
    else if (seat.ticketClass == 2) {
        cout << "Premium";
    }
    else if (seat.ticketClass == 3) {
        cout << "Luxury";
    }
    cout << endl;
    cout << "| Hall Type   : ";
    if (hallType == 1) {
        cout << "3D";
    }
    else {
        cout << "Normal";
    }
    cout << endl;
    if (wantsGlasses) {
        cout << "| 3D Glasses  : Yes" << endl;
    }
    if (wantsPopcorn) {
        cout << "| Popcorn     : Yes" << endl;
    }
    if (wantsSnacks) {
        cout << "| Snacks      : Yes" << endl;
    }
    cout << "-------------------------------" << endl;
}

void collectFeedback() {
    cout << "\nPlease provide feedback for the movie " << selectedMovie << endl;
    string feedback;
    cout << "Enter your feedback: ";
    cin.ignore();
    getline(cin, feedback);
    cout << "Thank you for your feedback!" << endl;
}

void cancelBooking() {
    int seatNumber;
    cout << "Enter seat number to cancel booking (1-" << TOTAL_SEATS << "): ";
    cin >> seatNumber;

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS || !seats[seatNumber - 1].isBooked) {
        cout << "Invalid or unbooked seat." << endl;
    }
    else {
        seats[seatNumber - 1].isBooked = false;
        seats[seatNumber - 1].customerName = "";
        seats[seatNumber - 1].ticketClass = 0;
        cout << "Booking for seat " << seatNumber << " has been cancelled." << endl;
    }
}

void searchBooking() {
    string name;
    cout << "Enter customer name to search: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i].customerName == name) {
            cout << "Booking found for " << name << " at seat " << seats[i].seatNumber << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No booking found for " << name << "." << endl;
    }
}

void displaySummaryReport() {
    int totalBookings = 0;
    int totalRevenue = 0;
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i].isBooked) {
            totalBookings++;
            if (seats[i].ticketClass == 1) {
                totalRevenue += STANDARD_PRICE;
            }
            else if (seats[i].ticketClass == 2) {
                totalRevenue += PREMIUM_PRICE;
            }
            else if (seats[i].ticketClass == 3) {
                totalRevenue += LUXURY_PRICE;
            }
        }
    }

    cout << "\nSummary Report:" << endl;
    cout << "Total Bookings: " << totalBookings << endl;
    cout << "Total Revenue: " << totalRevenue << endl;
}
