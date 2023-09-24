package common;

public class NumericExpression implements Expression {

  private final double value;

  public NumericExpression(double value) {
    this.value = value;
  }

  @Override
  public double eval() {
    return value;
  }
}
