#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class MovieBookingSystem {
private:
    struct Movie {
        string name;
        string showtime;
        int totalSeats;
        int availableSeats;
    };

    unordered_map<string, Movie> movies; // Map movie name to details

public:
    void addMovie(const string& name, const string& showtime, int seats) {
        if (movies.find(name) != movies.end()) {
            cout << "Movie already exists. Use a different name." << endl;
            return;
        }
        movies[name] = {name, showtime, seats, seats};
        cout << "Movie '" << name << "' added successfully with " << seats << " seats." << endl;
    }

    void bookTicket(const string& name, int numTickets = 1) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        Movie& movie = movies[name];

        if (movie.availableSeats >= numTickets) {
            movie.availableSeats -= numTickets;
            cout << "Booking confirmed for " << numTickets << " seat(s). Seats left: " << movie.availableSeats << endl;
        } else {
            cout << "Not enough seats available. Only " << movie.availableSeats << " left." << endl;
        }
    }

    void cancelTicket(const string& name, int numTickets = 1) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        Movie& movie = movies[name];

        if (movie.availableSeats + numTickets <= movie.totalSeats) {
            movie.availableSeats += numTickets;
            cout << "Cancellation successful. Seats left: " << movie.availableSeats << endl;
        } else {
            cout << "Cancellation failed. You cannot exceed the total seat limit of " << movie.totalSeats << "." << endl;
        }
    }

    void viewAvailableShows() {
        if (movies.empty()) {
            cout << "No available shows at the moment." << endl;
            return;
        }

        cout << "\nAvailable Movies:\n";
        for (const auto& pair : movies) {
            const Movie& movie = pair.second;
            cout << movie.name << " | Showtime: " << movie.showtime
                 << " | Available Seats: " << movie.availableSeats << "/" << movie.totalSeats << endl;
        }
    }

    void searchMovie(const string& name) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        const Movie& movie = movies[name];
        cout << "Movie Found: " << movie.name << "\nShowtime: " << movie.showtime
             << "\nSeats Available: " << movie.availableSeats << "/" << movie.totalSeats << endl;
    }
};

int main() {
    MovieBookingSystem system;

    system.addMovie("Inception", "7 PM", 50);
    system.addMovie("Interstellar", "9 PM", 40);
    
    system.viewAvailableShows();

    system.bookTicket("Inception", 2);
    system.bookTicket("Interstellar", 5);

    system.viewAvailableShows();

    system.cancelTicket("Inception", 1);
    system.cancelTicket("Interstellar", 3);

    system.viewAvailableShows();

    system.searchMovie("Inception");
    system.searchMovie("The Dark Knight"); // Not available

    return 0;
}
