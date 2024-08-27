public class RomanToInteger {
    
    public int romanToInt(String s) {
        
        Map<Character, Integer> m = new HashMap<Character, Integer>();
        m.put('M', 1000);
        m.put('D', 500);
        m.put('C', 100);
        m.put('L', 50);
        m.put('X', 10);
        m.put('V', 5); 
        m.put('I', 1); 
        
        int sum = 0;
        int current;
        for (int i = 0; i < s.length(); i++) {
            current = m.get(s.charAt(i));
            if (i == s.length() - 1) {
                sum += current;
                break;
            }
            int next = m.get(s.charAt(i + 1));
            if (next > current) {
                sum -= current;
            } else {
                sum += current;
            }
        }
        return sum;
    }
}