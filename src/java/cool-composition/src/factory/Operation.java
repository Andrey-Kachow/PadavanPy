package factory;

import java.util.function.BiFunction;

public class Operation {

  private final String sign;
  private final int precedence;
  private final BiFunction<Double, Double, Double> function;

  private Operation(String sign, int precedence, BiFunction<Double, Double, Double> function) {
    this.sign = sign;
    this.precedence = precedence;
    this.function = function;
  }

  public double eval(double left, double right) {
    return function.apply(left, right);
  }

  public String getSign() {
    return sign;
  }

  public int getPrecedence() {
    return precedence;
  }

  public static Operation addition() {
    return new Operation("+", 1, Double::sum);
  }

  public static Operation subtraction() {
    return new Operation("-", 1, (a, b) -> a - b);
  }

  public static Operation multiplication() {
    return new Operation("*", 2, (a, b) -> a * b);
  }

  public static Operation division() {
    return new Operation("/", 2, (a, b) -> a / b);
  }
}
