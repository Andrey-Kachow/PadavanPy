import logical.BooleanArray8;
import org.junit.Test;
import org.junit.Assert;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;


public class BooleanArray8Tester {

  // own assert methods to reference Junit assert methods

  private static void assertTrue(boolean booleanTestCase) {
    Assert.assertTrue(booleanTestCase);
  }

  private static void assertFalse(boolean booleanTestCase) {
    Assert.assertFalse(booleanTestCase);
  }

  private static void assertEquals(Object expected, Object actual) {
    Assert.assertEquals(expected, actual);
  }

  private final BooleanArray8 arr1 = new BooleanArray8(1, 0, 1, 0, 1, 0, 1, 0);
  private final BooleanArray8 arr2 = new BooleanArray8(true, false, true, false, true, false, true, false);
  private final String biString = "10101010";
  private final BooleanArray8 arr3 = new BooleanArray8(biString);
  private final List<Boolean> bools = new ArrayList<>(List.of(true, false, true, false, true, false, true, false));

  @Test
  public void constructorEquivalences() {
    assertEquals(arr1, arr2);
    assertEquals(arr2, arr3);
    assertTrue(arr1.equals(arr2));
    assertTrue(arr2.equals(arr3));
  }

  @Test
  public void stringTests() {
    assertEquals(arr1.toString(), bools.toString());
    assertTrue(arr1.toString().equals(bools.toString()));

    assertEquals(arr1.toBinaryString(), biString);
    assertTrue(arr1.toBinaryString().equals(biString));

    assertEquals(arr2.toBinaryString(), biString);
    assertTrue(arr2.toBinaryString().equals(biString));
  }


}