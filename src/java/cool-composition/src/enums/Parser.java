package enums;

public class Parser {

  public void parse() {
  }

  public static Operation fromToken(char akToken) {
    return switch (akToken) {
      case '+' -> Operation.ADD;
      case '-' -> Operation.SUB;
      case '*' -> Operation.MUL;
      case '/' -> Operation.DIV;
      default -> throw new RuntimeException();
    };
  }
}
