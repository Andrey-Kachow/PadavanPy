public class IntegerToRoman {
    public String intToRoman(int num) {
        StringBuilder sb = new StringBuilder();
        while (true) {
            if (num >= 1000) {
                sb.append('M');
                num -= 1000;
            } else if (num >= 900) {
                sb.append('C');
                sb.append('M');
                num -= 900;
            } else if (num >= 500) {
                sb.append('D');
                num -= 500;
            } else if (num >= 400) {
                sb.append('C');
                sb.append('D');
                num -= 400;
            } else if (num >= 100) {
                sb.append('C');
                num -= 100;
            } else if (num >= 90) {
                sb.append('X');
                sb.append('C');
                num -= 90;
            } else if (num >= 50) {
                sb.append('L');
                num -= 50;
            } else if (num >= 40) {
                sb.append('X');
                sb.append('L');
                num -= 40;
            } else if (num >= 10) {
                sb.append('X');
                num -= 10;
            } else if (num >= 9) {
                sb.append('I');
                sb.append('X');
                num -= 9;
            } else if (num >= 5) {
                sb.append('V');
                num -= 5;
            } else if (num >= 4) {
                sb.append('I');
                sb.append('V');
                num -= 4;
            } else if (num >= 1) {
                sb.append('I');
                num -= 1;
            } else {
                break;
            }
        }
        return sb.toString();
    }
}