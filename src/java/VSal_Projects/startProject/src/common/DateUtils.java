package common;

public class DateUtils {
    static void main() {
        assertThat(isDateValid(12,1,2025));
        System.out.println("DateUtils.isDateValid works correctly!");
    }


    public static void assertThat(boolean isValid){

        if(!isValid){
            throw new RuntimeException("The date is NOT valid.");
        }
    }

    public static boolean isDateValid(int day, int month, int year) {

        //check month
        if(month < 1 || month > 12){
            return false; //should be false; or return = false;
        }

        int maxDay;

        //check days in month
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
                month == 8 || month == 10 || month == 12) {
            maxDay = 31;
        } else if (month == 4 || month == 6 || month == 9 || month == 11){
            maxDay = 30;
        } else if (month == 2 && (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0) ){
            maxDay = 29;
        } else {
            maxDay = 28;
        }

        //check day
        if (day < 1 || day > maxDay) {
            return false;
        }

        return true;
    }

    public static String formatDate(int format, int day, int month, int year) {
        String output = switch (format) {
            case 0 -> day + "." + month + "." + year; // European
            case 1 -> day + "/" + month + "/" + year; // British
            case 2 -> month + "/" + day + "/" + year; // American
            case 3 -> year + "-" + month + "-" + day; // ISO
            default -> "Unknown format number!";
        };
        return output;
    }


}
