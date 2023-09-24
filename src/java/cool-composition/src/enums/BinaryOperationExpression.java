package enums;

import common.Expression;

public class BinaryOperationExpression implements Expression {

  private final Operation operation;
  private final Expression left;
  private final Expression right;

  public BinaryOperationExpression(Operation operation, Expression left, Expression right) {
    this.operation = operation;
    this.left = left;
    this.right = right;
  }

  @Override
  public double eval() {
    return operation.eval(left.eval(), right.eval());
  }
}
