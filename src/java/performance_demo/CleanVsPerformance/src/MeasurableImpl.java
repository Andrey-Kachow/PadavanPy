import java.util.Random;

public interface MeasurableImpl<T> {
  T[] generateData(int size, Random random);
  double totalArea(T...shapes);
}
