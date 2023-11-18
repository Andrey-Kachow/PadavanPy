import java.util.concurrent.Semaphore;

public class SampleSynchronization1 {

  private static final Semaphore sema = new Semaphore(0);

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

      sema.release();

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

      sema.acquire();

      for (int i = 0; i < 10; i++) {
        Thread.sleep(100);
        System.out.println("T2: THIS CAPS LINE SHOULD BE AFTER T1 CAPS LINES");
      }

    } catch (InterruptedException e) {
      throw new RuntimeException(e);
    }
  };

  public static void main(String[] args) throws InterruptedException {
//    Thread t1 = new Thread(r1);
    Thread t2 = new Thread(r2);

    System.out.println("Starting The Demo...");

//    t1.start();
    t2.start();

    Thread.sleep(3000);
    sema.release();

//    t1.join();
    t2.join();

    System.out.println("Ending The Demo...");
  }
}
