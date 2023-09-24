import mypackage.MyCircle;

public class Main {
  public static void main(String[] args) {


    for (int i = 0; i < 100; i++) {
      MyCircle circle = new MyCircle(i);

      System.out.print(circle.circumference() + " ");
      System.out.println(circle.area());
    }

    System.out.println("Hello world!");
  }
}