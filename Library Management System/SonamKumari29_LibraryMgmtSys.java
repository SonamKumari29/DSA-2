import java.util.*;

// Represents a Book with title, author, ISBN, and availability status
class Book {
    String title, author, ISBN;
    boolean isAvailable;

    // Constructor to initialize book details
    public Book(String title, String author, String ISBN) {
        this.title = title;
        this.author = author;
        this.ISBN = ISBN;
        this.isAvailable = true; // Book is available by default
    }

    // Borrow book if available
    public void borrowBook() {
        if (isAvailable) {
            isAvailable = false; // Mark as borrowed
            System.out.println("Borrowed: " + title);
        } else {
            System.out.println(title + " is already borrowed.");
        }
    }

    // Return book if borrowed
    public void returnBook() {
        if (!isAvailable) {
            isAvailable = true; // Mark as available
            System.out.println("Returned: " + title);
        } else {
            System.out.println(title + " was not borrowed.");
        }
    }

    // Display book details
    public String toString() {
        return "Title: " + title + " | Author: " + author + " | ISBN: " + ISBN + " | Available: " + (isAvailable ? "Yes" : "No");
    }
}

// Main Library Management System
public class SonamKumari29_LibraryMgmtSys {
    static HashMap<String, Book> library = new HashMap<>(); // Stores books by ISBN
    static Scanner sc = new Scanner(System.in);

    // Add a new book to the library
    public static void addBook() {
        System.out.print("Enter Title: ");
        String title = sc.nextLine();
        System.out.print("Enter Author: ");
        String author = sc.nextLine();
        System.out.print("Enter ISBN: ");
        String ISBN = sc.nextLine();

        library.put(ISBN, new Book(title, author, ISBN)); // Store book in the library
        System.out.println("Book Added Successfully!");
    }

    // Search for books by title or author
    public static void searchBook() {
        System.out.print("Search by Title/Author: ");
        String query = sc.nextLine().toLowerCase();
        boolean found = false;

        for (Book book : library.values()) {
            if (book.title.toLowerCase().contains(query) || book.author.toLowerCase().contains(query)) {
                System.out.println(book);
                found = true;
            }
        }
        if (!found) System.out.println("No books found.");
    }

    // Borrow a book using its ISBN
    public static void borrowBook() {
        System.out.print("Enter ISBN to borrow: ");
        String ISBN = sc.nextLine();
        Book book = library.get(ISBN);
        
        if (book != null) {
            book.borrowBook();
        } else {
            System.out.println("Book not found.");
        }
    }

    // Return a borrowed book using its ISBN
    public static void returnBook() {
        System.out.print("Enter ISBN to return: ");
        String ISBN = sc.nextLine();
        Book book = library.get(ISBN);

        if (book != null) {
            book.returnBook();
        } else {
            System.out.println("Book not found.");
        }
    }

    // Display all books in the library
    public static void viewBooks() {
        if (library.isEmpty()) {
            System.out.println("No books available.");
        } else {
            for (Book book : library.values()) {
                System.out.println(book);
            }
        }
    }

    // Main menu for user interaction
    public static void main(String[] args) {
        while (true) {
            System.out.println("\n1. Add Book  2. Search Book  3. Borrow  4. Return  5. View All  6. Exit");
            System.out.print("Enter choice: ");
            int choice = sc.nextInt();
            sc.nextLine(); // Consume newline

            switch (choice) {
                case 1 -> addBook();
                case 2 -> searchBook();
                case 3 -> borrowBook();
                case 4 -> returnBook();
                case 5 -> viewBooks();
                case 6 -> {
                    System.out.println("Exiting...");
                    return;
                }
                default -> System.out.println("Invalid choice!");
            }
        }
    }
}
