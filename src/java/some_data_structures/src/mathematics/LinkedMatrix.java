package mathematics;

public class LinkedMatrix {

  private final Entry topLeft;
  private final int width;
  private final int height;

  public LinkedMatrix(double[][] arr) {
    this.topLeft = new Entry(arr[0][0]);
    this.height = arr.length;
    this.width = arr[0].length;

    Entry e = topLeft;
    for (int i = 1; i < height; i++) {
      e.vNext = new Entry(arr[i][0]);
      e = e.vNext;
    }
    e = topLeft;
    for (int i = 1; i < width; i++) {
      e.hNext = new Entry(arr[0][i]);
      e = e.hNext;
    }

    Entry oldReducedMatrixTopLeft = topLeft;
    int numberOfReductions = Math.min(width, height);
    for (int k = 1; k < numberOfReductions; k++) {
      Entry reducedMatrixTopLeft = new Entry(arr[k][k]);

      Entry currentPred = oldReducedMatrixTopLeft.vNext;
      Entry currentEntry = reducedMatrixTopLeft;
      for (int i = 1; i < height - k; i++) {
        currentPred.hNext = currentEntry;
        currentPred = currentPred.vNext;
        currentEntry.vNext = new Entry(arr[k + i][k]);
        currentEntry = currentEntry.vNext;
      }
      currentPred.hNext = currentEntry;

      currentPred = oldReducedMatrixTopLeft.hNext;
      currentEntry = reducedMatrixTopLeft;
      for (int i = 1; i < width - k; i++) {
        currentPred.vNext = currentEntry;
        currentPred = currentPred.hNext;
        currentEntry.hNext = new Entry(arr[k][k + i]);
        currentEntry = currentEntry.hNext;
      }
      currentPred.vNext = currentEntry;

      oldReducedMatrixTopLeft = reducedMatrixTopLeft;
    }
  }

  private Entry getEntry(int row, int col) {
    Entry entry = topLeft;
    for (int i = 0; i < row; i++) {
      entry = entry.vNext;
    }
    for (int i = 0; i < col; i++) {
      entry = entry.hNext;
    }
    return entry;
  }

  public double get(int row, int column) {
    return getEntry(row, column).getValue();
  }

  public void set(int row, int column, double value) {
    getEntry(row, column).setValue(value);
  }

  public int getNumRows() {
    return height;
  }

  public int getNumColumns() {
    return width;
  }

  @Override
  public String toString() {
    StringBuilder result = new StringBuilder();
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        result.append("| ").append(get(i, j)).append(" ");
      }
      result.append("\n");
    }
    return result.toString();
  }

  private static class Entry {

    private double value;
    private Entry hNext;
    private Entry vNext;

    Entry (double value) {
      this.value = value;
      this.hNext = null;
      this.vNext = null;
    }

    public double getValue() {
      return value;
    }

    public void setValue(double newValue) {
      value = newValue;
    }

  }

  public static void main(String[] args) {
    double[][] test = new double[][]{
            new double[] {1.0D, 2.0D, 3.0D, 4.0D},
            new double[] {5.0D, 6.0D, 7.0D, 8.0D},
            new double[] {9.0D, 1.0D, 1.1D, 1.2D},
            new double[] {1.3D, 1.4D, 1.5D, 1.6D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
            new double[] {1.7D, 1.8D, 1.9D, 2.0D},
    };
    LinkedMatrix testrix = new LinkedMatrix(test);
    System.out.println(testrix);
  }
}

