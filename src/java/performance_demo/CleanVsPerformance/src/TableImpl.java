import java.util.Random;

public class TableImpl implements MeasurableImpl<TableImpl.Shape> {

  static final int CIRCLE = 0;
  static final int RECTANGLE = 1;
  static final int TRIANGLE = 2;
  static final double[] areaCoefficients = {Math.PI, 1, 0.5};

  static class Shape implements MeasurableThing {
    final int type;
    final double width;
    final double height;

    private Shape(int type, double width, double height) {
      this.type = type;
      this.width = width;
      this.height = height;
    }

    static Shape triangle(double base, double height) {
      return new Shape(TRIANGLE, base, height);
    }

    static Shape rectangle(double width, double height) {
      return new Shape(RECTANGLE, width, height);
    }

    static Shape circle(double radius) {
      return new Shape(CIRCLE, radius, radius);
    }
  }

  public double totalArea(Shape... shapes) {
    double sum = 0;
    for (Shape shape : shapes) {
      sum += areaCoefficients[shape.type] * shape.width * shape.height;
    }
    return sum;
  }

  public Shape[] generateData(int size, Random random) {
    Shape[] res = new Shape[size];
    for (int i = 0; i < res.length; i++) {
      res[i] = switch (random.nextInt(3) % 3) {
        case 0 -> Shape.triangle(random.nextDouble(), random.nextDouble());
        case 1 -> Shape.rectangle(random.nextDouble(), random.nextDouble());
        case 2 -> Shape.circle(random.nextDouble());
        default -> throw new RuntimeException();
      };
    }
    return res;
  }
}
