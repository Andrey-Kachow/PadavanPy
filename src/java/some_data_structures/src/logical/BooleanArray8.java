package logical;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

/**
 * The following class represent an array of booleans in a such way
 * that 8 booleans take one byte, not 8 bytes
 */

// TODO: 05.02.2021 TEST THIS DATA TYPE 

// TODO: 05.02.2021 TEST IF IT IS FASTER THAN ARRAYLIST OF BOOLEANS 

public class BooleanArray8 {

  public static final int NUMBER_OF_BITS = 8;

  private byte value;

  public BooleanArray8(int value) {
    this.value = (byte) value;
  }

  public BooleanArray8(boolean b7, boolean b6, boolean b5, boolean b4,
                       boolean b3, boolean b2, boolean b1, boolean b0) {
    this((pow(b7, 7) + pow(b6,  6)
                + pow(b5, 5) + pow(b4, 4) + pow(b3, 3)
                + pow(b2, 2) + pow(b1, 1) + pow(b0, 0)));
  }
  
  public BooleanArray8(int b7, int b6, int b5, int b4,
                       int b3, int b2, int b1, int b0) {
    this(bool(b7), bool(b6), bool(b5), bool(b4),
            bool(b3), bool(b2), bool(b1), bool(b0));
  }

  public BooleanArray8(String binaryString) {
    int val = 0;
    for (int i = 0; i < NUMBER_OF_BITS - 1; i++) {
      int rank = NUMBER_OF_BITS - 1 - i;
      val += pow(binaryString.charAt(i) == '1', rank);
    }
    this.value = (byte) val;
  }

  public boolean get(int index) {
    return toBinaryString().charAt(index) == '1';
  }

  public boolean getBit(int rank) {
    return get( - rank);
  }
  
  public void set(int index, boolean newBit) {
    setBit(NUMBER_OF_BITS - 1 - index, newBit);
  }
  
  public void setBit(int rank, boolean newBit) {
    value -= decimalContribution(rank);
    value += pow(newBit, rank);
  }

  private int decimalContribution(int rank) {
    return pow(getBit(rank), rank);
  }
  
  public String toBinaryString() {
    final int INT_BIT_SIZE = 32;
    return Integer.toBinaryString(value)
            .substring(INT_BIT_SIZE - NUMBER_OF_BITS);
  }

  @Override
  public String toString() {
    List<Boolean> booleanList = new ArrayList<>();
    String code = toBinaryString();
    for (int i = 0; i < code.length(); i++) {
      booleanList.add(code.charAt(i) == '1');
    }
    return booleanList.toString();
  }

  @Override
  public boolean equals(Object other) {
    if (other instanceof BooleanArray8) {
      return this.value == ((BooleanArray8) other).value;
    }
    return false;
  }

  private static byte powOf2(int exponent) {
    byte n = 2;
    for (int i = 0; i < exponent - 1; i++) {
      n *= 2;
    }
    return n;
  }

  public static int pow(boolean bit, int exponent) {
    if (!bit) {
      return 0;
    }
    return powOf2(exponent);
  }

  private static boolean bool(int n) {
    return n != 0;
  }
}
