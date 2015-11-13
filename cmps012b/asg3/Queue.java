//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B
// Queue.java
// Implements a queue using a linked list in java
import java.util.Iterator;
import java.util.NoSuchElementException;

class Queue<Item> implements Iterable<Item> {

    private class Node {

        Item item;
        Node next;
    }
    private Node head = null;
    private Node tail = null;

    public boolean isempty() {
        return (head == null);
    }

    public void insert(Item newitem) {
        Node n = new Node();
        n.item = newitem;
        if (head == null) {
            head = n;
            tail = n;
        } else {
            tail.next = n;
            tail = n;
        }
    }

    public Iterator<Item> iterator() {
        return new Itor();
    }

    class Itor implements Iterator<Item> {

        Node current = head;

        public boolean hasNext() {
            return current != null;
        }

        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            Item result = current.item;
            current = current.next;
            return result;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

}
