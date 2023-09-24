package mypackage;

public class MyCircle {

  final double radius;

  public MyCircle(double radius) {
    this.radius = radius;
  }

  public double circumference() {
    return 2 * Math.PI * radius;
  }

  public double area() {
    return Math.PI * radius * radius;
  }
}
