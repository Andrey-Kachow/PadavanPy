package basicsLoops;

//IMPORT
import common.DateUtils;
import java.util.Scanner;

// WHILE LOOPS 2.4

public class DatesStatistics {

    public static void main(String[] args){

        Scanner scanner = new Scanner(System.in);

        System.out.print("How many dates you want to process? ");
        int size = scanner.nextInt();
        scanner.nextLine();
        
        //(in)valid dates counter
        int invalidDates = 0;
        
        //format counter
        int countEURO = 0;
        int countUK = 0;
        int countUSA = 0;
        int countISO = 0;
        int countNotExistFormat = 0;
        
        //counter for year 2007
        int count2007 = 0;

        //Format dates

        for (int i = 0; i < size; i++) {

            System.out.println("\n/////////////////");
            System.out.println("DATE FORMATTER");
            System.out.println("Here are the available formats:");
            System.out.println("0: European");
            System.out.println("1: British");
            System.out.println("2: American");
            System.out.println("3: ISO");

            System.out.print("\nChoose your format: ");
            int format = scanner.nextInt();
            scanner.nextLine();

            //check format
            if (format < 0 || format > 3) {
                countNotExistFormat++;
            }

            //count formats
            switch (format){
                case 0 -> countEURO++;
                case 1 -> countUK++;
                case 2 -> countUSA++;
                case 3 -> countISO++;
            }

            System.out.print("Enter the day: ");
            int day = scanner.nextInt();
            scanner.nextLine();

            System.out.print("Enter the month: ");
            int month = scanner.nextInt();
            scanner.nextLine();

            System.out.print("Enter the year: ");
            int year = scanner.nextInt();
            scanner.nextLine();
            
            if (year == 2007) {
                count2007++;
            }

            //check date
            boolean valid = DateUtils.isDateValid(day, month, year);

            //output if NOT valid
            if (!valid) {
                invalidDates++;
                System.out.println("This date does NOT exist");;
                continue;
            }

            //output
            String output = switch (format) {
                case 0 -> day + "." + month + "." + year; // European
                case 1 -> day + "/" + month + "/" + year; // British
                case 2 -> month + "/" + day + "/" + year; // American
                case 3 -> year + "-" + month + "-" + day; // ISO
                default -> "Unknown format!";
            };

            System.out.println("Formatted date: " + output);
            System.out.println();

        }

        //Statistic of formated dates
        System.out.println("\nSTATISTICS:");
        System.out.println("Altogether " + size + " date(s) was/were processed.");
        System.out.println("Of which " + invalidDates + " was/were incorrect.");
        System.out.println(" ");
        System.out.println("Following formats were used:");
        System.out.println("European format: " + countEURO);
        System.out.println("British format: " + countUK);
        System.out.println("American format: " + countUSA);
        System.out.println("ISO format: " + countISO);
        System.out.println("Unidentified format(s): " + countNotExistFormat);
        System.out.println(" ");
        System.out.println("The year 2007 appeared " + count2007 + " time(s).");

        scanner.close();
    }
}
