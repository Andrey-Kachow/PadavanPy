import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SampleLocks0 {

  static class ImportantResource {

    Lock lock = new ReentrantLock();

    void doSomethingImportant() throws InterruptedException {

      lock.lock();

      Thread.sleep(200);
      System.out.print("H");
      Thread.sleep(200);
      System.out.print("e");
      Thread.sleep(200);
      System.out.print("l");
      Thread.sleep(200);
      System.out.print("l");
      Thread.sleep(200);
      System.out.print("o");
      Thread.sleep(200);
      System.out.print(" ");
      Thread.sleep(200);
      System.out.print("W");
      Thread.sleep(200);
      System.out.print("o");
      Thread.sleep(200);
      System.out.print("r");
      Thread.sleep(200);
      System.out.print("l");
      Thread.sleep(200);
      System.out.print("d");
      Thread.sleep(200);
      System.out.println();

      lock.unlock();
    }

    static class SomethingToDoWithImportant implements Runnable {

      ImportantResource importantResource;

      SomethingToDoWithImportant(ImportantResource important) {
        this.importantResource = important;
      }

      @Override
      public void run() {
        try {
          importantResource.doSomethingImportant();
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
      }
    }

    public static void main(String[] args) throws InterruptedException {

      ImportantResource important = new ImportantResource();

      Thread t1 = new Thread(new SomethingToDoWithImportant(important));
      Thread t2 = new Thread(new SomethingToDoWithImportant(important));

      System.out.println("Starting The Demo...");

      t1.start();
      t2.start();

//      t1.join();
//      t2.join();

      System.out.println("Ending The Demo...");
    }

  }

}
