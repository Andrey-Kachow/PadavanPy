package enums;


import java.util.function.BiFunction;

public enum Operation {
  ADD("+", 1, Double::sum),
  SUB("-", 1, (a, b) -> a - b),
  MUL("*", 2, (a, b) -> a * b),
  GEOMAVG("?", 69, Operation::mySpecialOperation),
  DIV("/", 2, (a, b) -> a / b);

  private final String sign;
  private final int precedence;
  private final BiFunction<Double, Double, Double> function;

  Operation(String sign, int precedence, BiFunction<Double, Double, Double> function) {
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

  private static double mySpecialOperation(double a, double b) {
    return Math.pow(a, b);
  }

}
