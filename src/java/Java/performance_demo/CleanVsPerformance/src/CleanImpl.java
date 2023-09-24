import java.util.Random;

public class CleanImpl implements MeasurableImpl<CleanImpl.Shape> {

  interface Shape extends MeasurableThing {
    double area();
  }

  static class Circle implements Shape {

    private final double radius;

    Circle(double radius) {
      this.radius = radius;
    }

    @Override
    public double area() {
      return Math.PI * radius * radius;
    }
  }

  static class Rectangle implements Shape {

    private final double width;
    private final double height;

    Rectangle(double width, double height) {
      this.width = width;
      this.height = height;
    }

    @Override
    public double area() {
      return width * height;
    }
  }

  static class Triangle implements Shape {

    private final double base;
    private final double height;

    Triangle(double base, double height) {
      this.base = base;
      this.height = height;
    }

    @Override
    public double area() {
      return 0.5 * base * height;
    }
  }

  public double totalArea(Shape... shapes) {
    double sum = 0;
    for (Shape shape : shapes) {
      sum += shape.area();
    }
    return sum;
  }






  public Shape[] generateData(int size, Random random) {
    Shape[] res = new Shape[size];
    for (int i = 0; i < res.length; i++) {
      res[i] = switch (random.nextInt(3) % 3) {
        case 0 -> new Triangle(random.nextDouble(), random.nextDouble());
        case 1 -> new Rectangle(random.nextDouble(), random.nextDouble());
        case 2 -> new Circle(random.nextDouble());
        default -> throw new RuntimeException();
      };
    }
    return res;
  }
}
