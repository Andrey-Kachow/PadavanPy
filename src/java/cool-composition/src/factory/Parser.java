package factory;


public class Parser {

  public void parse() {
  }

  public static Operation fromToken(char akToken) {
    return switch (akToken) {
      case '+' -> Operation.addition();
      case '-' -> Operation.subtraction();
      case '*' -> Operation.multiplication();
      case '/' -> Operation.division();
      default -> throw new RuntimeException();
    };
  }
}
