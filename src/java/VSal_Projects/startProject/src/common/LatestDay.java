package common;

public class LatestDay {
    public static int compareLateDates(int[][] dates) {

        int lateDay = 0;

        for (int i = 1; i < dates.length; i++) {

            int d1 = dates[i][0];
            int m1 = dates[i][1];
            int y1 = dates[i][2];

            int d2 = dates[lateDay][0];
            int m2 = dates[lateDay][1];
            int y2 = dates[lateDay][2];

            if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) {

                lateDay = i;

            }
        }

        return lateDay;

    }

}
