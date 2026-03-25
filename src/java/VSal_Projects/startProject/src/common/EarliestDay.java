package common;

public class EarliestDay {
    public static int compareEarlierDates(int[][] dates) {

        int earliestDay = 0;

        for (int i = 1; i < dates.length; i++) {

            int d1 = dates[i][0];
            int m1 = dates[i][1];
            int y1 = dates[i][2];

            int d2 = dates[earliestDay][0];
            int m2 = dates[earliestDay][1];
            int y2 = dates[earliestDay][2];

            if (y1 < y2 || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2)) {

                earliestDay = i;

            }
        }

        return earliestDay;

    }
}

