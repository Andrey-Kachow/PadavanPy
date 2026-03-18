package common;

import java.util.Scanner;

public class ArrayScanner {

    public static int[] scanIntegerArray() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Please, insert the array size: ");
        int size = scanner.nextInt();

        int[] array = new int[size];

        for (int i = 0; i < array.length; i++) {
            System.out.print("Enter integer #" + (i + 1) + ": ");
            array[i] = scanner.nextInt();
        }

        return array;
    }

}
