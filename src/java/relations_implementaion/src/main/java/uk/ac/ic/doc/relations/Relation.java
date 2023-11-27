package uk.ac.ic.doc.relations;

import java.util.*;

class Tuple {
  private final Object[] data;

  Tuple(Object... data) {
    this.data = data;
  }

  public int rowLength(){
    return data.length;
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("| ");
    for (Object datum : data) {
      sb.append(datum.toString());
      sb.append(" | ");
    }
    return sb.toString();
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(data);
  }

  Object get(int index) {
    return data[index];
  }

}

public class Relation {

  private final String[] schema;
  private final List<Tuple> rows = new ArrayList<>(16);



  public Relation(String... schema) {
    this.schema = schema;
  }

  public void addRow(Object... objects) {
    if (objects.length != schema.length) {
      throw new IllegalArgumentException("Schema mismatch");
    }
    this.rows.add(new Tuple(objects));
  }

  public String[] select(String toSelect){

  }

  private int findIndex(String toFind, Tuple tuple){
    Tuple titleTuple = rows.get(0);
    int titleTupleSize = titleTuple.rowLength();

    for (int i = 0; i < titleTupleSize ; i++){
      if (toFind == titleTuple.get(i)){
        return i;
        break;
      }else
    }

    return titleTupleSize;
  }


  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("| ");
    for (Object col : schema) {
      sb.append(col);
      sb.append(" | ");
    }
    sb.append("\n");
    for (Tuple row : rows) {
      sb.append(row.toString()).append("\n");
    }
    return sb.toString();
  }

}


/**
 * Little Hints
 */
interface SelectPredicate {
  boolean invoke(Tuple tuple, String[] schema);
}

class NameEqualsHolgerPredicate implements SelectPredicate {
  @Override
  public boolean invoke(Tuple tuple, String[] schema) {
    // TODO: 23/01/2023 ...
    return false;
  }
}



class BookStore {

  private static Relation createCustomer() {
    Relation customer = new Relation("CustomerID", "Name", "Shipping Address");
    customer.addRow(1, "Holger", "180 Queens Gate");
    customer.addRow(2, "Sam", "32 Vassar Street");
    customer.addRow(3, "Peter", "180 Queens Gate");
    return customer;
  }

  private static Relation createOrder() {
    Relation order = new Relation("OrderID", "CustomerID");
    order.addRow(1, 1);
    order.addRow(2, 2);
    order.addRow(3, 3);
    return order;
  }

  private static Relation createOrderedItem() {
    Relation orderedItem = new Relation("OrderID", "BookID");
    orderedItem.addRow(1, 1);
    orderedItem.addRow(1, 2);
    orderedItem.addRow(2, 1);
    orderedItem.addRow(3, 3);
    return orderedItem;
  }

  private static Relation createBook() {
    Relation book = new Relation("BookID", "Title", "Author", "Price");
    book.addRow(1, "Database Management Systems", "Ramakrishnan & Gehrke", 60);
    book.addRow(2, "A Game of Thrones", "Martin", 15);
    book.addRow(3, "Distributed Systems", "van Steen & Tanenbaum", 40);
    return book;
  }



  public static void main(String[] args) {
    Relation customer = createCustomer();
    Relation order = createOrder();
    Relation orderedItem = createOrderedItem();
    Relation book = createBook();
    System.out.println(customer);
    System.out.println(order);
    System.out.println(orderedItem);
    System.out.println(book);
  }
}
