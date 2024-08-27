bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }
    int copy = x;
    int x_rev = 0;
    while (copy != 0) {
        if (INT_MAX / 10 < x_rev) {
            return false;
        }
        x_rev = x_rev * 10 + copy % 10;
        copy /= 10;
    }
    return x == x_rev;
}