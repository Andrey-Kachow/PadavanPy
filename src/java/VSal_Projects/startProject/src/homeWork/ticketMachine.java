package homeWork;
import java.util.InputMismatchException;
import java.util.Scanner;

// TICKET MACHINE

public class ticketMachine {
    public static void main(String[] args) {

        double fullPrice = 16.80;  //from 26 full price
        double discount20 = 13.44; //from 18 to incl. 25 -20%
        double discount50 = 8.40; //less than 18 -50%
        char currency = '€';
        boolean isRunning = true;

        Scanner scanner = new Scanner(System.in);

        System.out.println("WELCOME TO APPLE CINEMA!");
        System.out.println("\nToday's program:");
        System.out.println("1. Rear Window at 6pm (PG)");
        System.out.println("2. Vertigo at 8:30pm (PG)");
        System.out.println("3. La Pescine at 11pm (18+)");
        System.out.println("4. Exit");

        //users choice
        System.out.print("\nEnter your choice (1-4): ");

        try {
            int choice = scanner.nextInt();

            switch (choice) {
                case 1 -> {
                    System.out.println("Rear Window at 6pm (PG)");
                    System.out.print("\nEnter your age: ");
                    int age = scanner.nextInt();

                    if (age < 18) {
                        System.out.println("The price of your ticket is " + discount50 + currency);
                    } else if (age <= 25) {
                        System.out.println("The price of your ticket is " + discount20 + currency);
                    } else {
                        System.out.println("The price of your ticket is " + fullPrice + currency);
                    }

                    System.out.println("\nThank you for your purchase!");
                }

                case 2 -> {
                    System.out.println("Vertigo at 8:30pm (PG)");
                    System.out.print("\nEnter your age: ");
                    int age = scanner.nextInt();

                    if (age < 18) {
                        System.out.println("The price of your ticket is " + discount50 + currency);
                    } else if (age <= 25) {
                        System.out.println("The price of your ticket is " + discount20 + currency);
                    } else {
                        System.out.println("The price of your ticket is " + fullPrice + currency);
                    }

                    System.out.println("\nThank you for your purchase!");
                }

                case 3 -> {
                    System.out.println("La Piscine at 11pm (18+)");
                    System.out.print("\nEnter your age: ");
                    int age = scanner.nextInt();

                    if (age < 18) {
                        System.out.println("You aren't old enough to watch this movie :(");
                    } else if (age >= 18 && age < 26) {
                        System.out.println("The price of your ticket is " + discount20 + currency);
                        System.out.println("\nThank you for your purchase!");
                    } else {
                        System.out.println("The price of your ticket is "  + fullPrice + currency);
                        System.out.println("\nThank you for your purchase!");
                    }

                }
                case 4 -> {
                    System.out.println("Sorry, we couldn't help you today!");
                    isRunning = false;
                }
                default -> System.out.println("Invalid choice!");
            }
        } catch (InputMismatchException e) {
            System.out.println("You should enter a number.");
        }
        scanner.close();
    }
}


// System.out.print("How many customer are here today?: ");
// iMax = scanner.nextInt();
// scanner.nextLine();
//
// for(int i = 0; i < iMax; i++) {
//     System.out.print("How old are you?: ");
//     age = scanner.nextInt();
//     scanner.nextLine();
//
//     System.out.print("How many tickets do you need?: ");
//     quantity = scanner.nextInt();
//     scanner.nextLine();
//
//     if (age < 18) {
//         total = discount50 * quantity;
//     } else if (age <= 25) {
//         total = discount20 * quantity;
//     } else {
//         total = fullPrice * quantity;
//     }
//
//     String formattedMoney = String.format("%.2f. I bought %d tickets", total, quantity);
//
//     String englishSpellingOfTickets = "ticket";
//     if (quantity > 1) {
//         englishSpellingOfTickets += "s";
//     }
//
//     System.out.println("Your total for " + quantity + " ticket/s is " + currency + formattedMoney + ".");
//     if(i < 2) {
//         System.out.println("\nNext person, please!\n");
//     }
// }
//
// System.out.println("\nSorry, we are closed for today!");