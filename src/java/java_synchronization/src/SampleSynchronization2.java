import java.util.concurrent.Semaphore;

public class SampleSynchronization2 {

  private static final Semaphore sema1 = new Semaphore(0);
  private static final Semaphore sema2 = new Semaphore(0);

  private static final Runnable r1 = () -> {
    try {

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T1: This line should be printed in arbitrary order (" + i + ")");
      }

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T1: THIS CAPS LINE SHOULD BE BEFORE T2 CAPS LINES");
      }

      sema1.release();
      sema2.acquire();

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T1: This line should be printed in arbitrary order (" + i + ")");
      }

    } catch (InterruptedException e) {
      throw new RuntimeException(e);
    }
  };

  private static final Runnable r2 = () -> {
    try {

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T2: This line should be printed in arbitrary order (" + i + ")");
      }

      sema1.acquire();

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T2: THIS CAPS LINE SHOULD BE AFTER T1 CAPS LINES");
      }

      sema2.release();

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T2: This line should be printed in arbitrary order (" + i + ")");
      }

    } catch (InterruptedException e) {
      throw new RuntimeException(e);
    }
  };

  public static void main(String[] args) throws InterruptedException {
    Thread t1 = new Thread(r1);
    Thread t2 = new Thread(r2);

    System.out.println("Starting The Demo...");

    t1.start();
    t2.start();

    t1.join();
    t2.join();

    System.out.println("Ending The Demo...");
  }
}
