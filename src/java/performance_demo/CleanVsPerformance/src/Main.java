import java.util.*;

public class Main {

  static final int NUM_ITERATIONS = 1000;
  static final int SAMPLE_SIZE = 1000;

  static class Timer {
    long elapsedNanoTime = 0;

    private long currentNanoTime = 0;

    void start() {
      currentNanoTime = System.nanoTime();
    }

    void pause() {
      elapsedNanoTime += System.nanoTime() - currentNanoTime;
      currentNanoTime = 0;
    }

    @Override
    public String toString() {
      return "Elapsed real time " + elapsedNanoTime;
    }
  }

  static class Tester {
    private final MeasurableImpl<MeasurableThing> measurable;
    private final Timer timer = new Timer();
    private final Random random;

    Tester(MeasurableImpl<MeasurableThing> measurable, long seed) {
      this.measurable = measurable;
      this.random = new Random(seed);
    }

    void test() {
      Timer realTimer = new Timer();
      realTimer.start();
      for (int i = 0; i < NUM_ITERATIONS; i++) {
        var shapes = measurable.generateData(SAMPLE_SIZE, random);
        timer.start();
        measurable.totalArea(shapes);
        timer.pause();
        Runtime.getRuntime().gc();
      }
      realTimer.pause();
      System.out.println(measurable);
      System.out.println(timer);
      System.out.println("Out of which total time " + realTimer.elapsedNanoTime);
      System.out.println();
    }
  }

  public static void main(String[] args) {
    List<MeasurableImpl<? extends MeasurableThing>> measurables = List.of(
      new CleanImpl()
      ,
      new SwitchImpl()
      ,
      new TableImpl()
    );
    for (var measurable : measurables) {
      new Tester((MeasurableImpl<MeasurableThing>) measurable, 42069).test();
    }
  }
}