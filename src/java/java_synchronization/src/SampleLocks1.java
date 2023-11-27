import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SampleLocks1 {

  static class Tree {

    private final int val;
    private Tree left;
    private Tree right;

    Lock leftLock = new ReentrantLock();
    Lock rightLock = new ReentrantLock();

    static Tree leaf(int val) {
      return new Tree(val, null, null);
    }

    Tree(int val, Tree left, Tree right) {
      this.val = val;
      this.left = left;
      this.right = right;
    }

    void insert(int i) {
      if (i < val) {
        if (left == null) {
          left = leaf(i);
        } else {
          left.insert(i);
        }
      } else {
        if (right == null) {
          right = leaf(i);
        } else {
          right.insert(i);
        }
      }
    }

    void concurrentInsert(int i, Lock parentLock) {
      if (i < val) {
        leftLock.lock();
        if (parentLock != null) {
          parentLock.unlock();
        }
        if (left == null) {
          left = leaf(i);
          leftLock.unlock();
        } else {
          left.concurrentInsert(i, leftLock);
        }
      } else {
        rightLock.lock();
        if (parentLock != null) {
          parentLock.unlock();
        }
        if (right == null) {
          right = leaf(i);
          rightLock.unlock();
        } else {
          right.concurrentInsert(i, rightLock);
        }
      }
    }

    void traverse(String msgPrefix) {
      if (left != null) {
        left.traverse(msgPrefix);
      }
      System.out.println(msgPrefix + "Visited " + val);
      if (right != null) {
        right.traverse(msgPrefix);
      }
    }

    int size() {
      int count = 1;
      if (left != null) {
        count += left.size();
      }
      if (right != null) {
        count += right.size();
      }
      return count;
    }

  }

  static Random random = new Random();

  static class Inserter implements Runnable {
    private final Tree tree;

    Inserter(Tree tree) {
      this.tree = tree;
    }

    @Override
    public void run() {
      for (int i = 0; i < 100; i++) {
        tree.concurrentInsert(random.nextInt(-20, 20), null);
//        tree.insert(random.nextInt(-20, 20));
      }
    }
  }

  public static void main(String[] args) throws InterruptedException {
    Tree tree = Tree.leaf(0);
    List<Thread> threads = new ArrayList<>(100);
    for (int i = 0; i < 100; i++) {
      threads.add(new Thread(new Inserter(tree)));
    }

    System.out.println("Starting The Demo...");

    for (Thread t : threads) {
      t.start();
    }

    for (Thread t : threads) {
      t.join();
    }

//    tree.traverse("CHECKING ORDER ");
    if (tree.size() != 10000 + 1) {
      throw new IllegalStateException("Actual size: " + tree.size());
    }

    System.out.println("Ending The Demo...");
  }

}
