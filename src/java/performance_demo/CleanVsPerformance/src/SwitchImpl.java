import java.util.Random;

public class SwitchImpl implements MeasurableImpl<SwitchImpl.Shape> {

  enum ShapeType {
    RECTANGLE, TRIANGLE, CIRCLE;
  }

  static class Shape implements MeasurableThing {
    final ShapeType type;
    final double width;
    final double height;

    private Shape(ShapeType type, double width, double height) {
      this.type = type;
      this.width = width;
      this.height = height;
    }

    static Shape triangle(double base, double height) {
      return new Shape(ShapeType.TRIANGLE, base, height);
    }

    static Shape rectangle(double width, double height) {
      return new Shape(ShapeType.RECTANGLE, width, height);
    }

    static Shape circle(double radius) {
      return new Shape(ShapeType.CIRCLE, radius, radius);
    }
  }

  public double totalArea(Shape... shapes) {
    double sum = 0;
    for (Shape shape : shapes) {
      sum += switch (shape.type) {
        case CIRCLE -> Math.PI * shape.width * shape.height;
        case TRIANGLE -> 0.5 * shape.width * shape.height;
        case RECTANGLE -> shape.width * shape.height;
      };
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

