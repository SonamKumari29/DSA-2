class MovieBookingSystem:
    def __init__(self):
        self.movies = {}  # Dictionary to store movie details

    def add_movie(self, name, showtime, seats):
        if name in self.movies:
            print("Movie already exists.")
        else:
            self.movies[name] = {"showtime": showtime, "seats": seats}
            print("Movie added successfully.")

    def book_ticket(self, name):
        if name in self.movies:
            if self.movies[name]["seats"] > 0:
                self.movies[name]["seats"] -= 1
                print(f"Booking confirmed. Seats Left: {self.movies[name]['seats']}")
            else:
                print("Booking failed. No seats available.")
        else:
            print("Movie not found.")

    def cancel_ticket(self, name):
        if name in self.movies:
            self.movies[name]["seats"] += 1
            print(f"Ticket canceled. Seats Left: {self.movies[name]['seats']}")
        else:
            print("Cancellation failed. Movie not found.")

    def view_available_shows(self):
        if not self.movies:
            print("No movies available.")
        else:
            for name, details in self.movies.items():
                print(f'"{name}" - Showtime: {details["showtime"]} - Seats Left: {details["seats"]}')

    def search_movie(self, name):
        if name in self.movies:
            details = self.movies[name]
            print(f'Movie Found:\n"{name}" - Showtime: {details["showtime"]} - Seats Left: {details["seats"]}')
        else:
            print("Movie not found.")

# Example Usage
system = MovieBookingSystem()
system.add_movie("Inception", "7 PM", 50)
system.book_ticket("Inception")
system.cancel_ticket("Inception")
system.view_available_shows()
system.search_movie("Inception")
