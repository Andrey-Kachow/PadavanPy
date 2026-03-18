package homeWork;
import java.util.Scanner;

/*
 LEAP YEAR PROBLEM
 A leap year is evenly divisible by 4, 100 and 400
*/

public class leapYear {
    public static void main(String[] args){

        int year;

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a year you want to check: ");
        year = scanner.nextInt();
        scanner.nextLine();

        // (||) > means "or" the next statement applies
        // Since, year is an integer, I check with remainder-division

        if((year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0)){
            System.out.println("YES");
        } else{
            System.out.println("NO");
        }

        scanner.close();
    }
}
