//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12 B
// dllist.java
// Code for doubly-linked list of strings for Assignment 2

import java.util.NoSuchElementException;

public class dllist {

    public enum position {

        FIRST, PREVIOUS, FOLLOWING, LAST
    };

    private class node {

        String item;
        node prev;
        node next;
    }

    private node first = null;
    private node current = null;
    private node last = null;
    private int currentPosition = 0;

    public void setPosition(position pos) {
        switch (pos) {
            case FIRST:
                current = first;
                currentPosition = 0;
                break;
            case PREVIOUS:
                current = current.prev;
                currentPosition = currentPosition - 1;
                break;
            case FOLLOWING:
                current = current.next;
                currentPosition = currentPosition + 1;
                break;
            case LAST:
                current = last;
                node temp;
                temp = first;
                currentPosition = 0;
                while (temp.next != null) {
                    currentPosition++;
                    temp = temp.next;
                }
                break;
        }
    }

    public boolean isEmpty() {
        return (first == null);
    }

    public String getItem() throws NoSuchElementException {
        if (current == null) {
            throw new NoSuchElementException();
        } else {
            return current.item; 
        }
    }

    public int getPosition() throws NoSuchElementException {
        if (first == null) {
            throw new NoSuchElementException();
        }
	else {
        return currentPosition;
	}
    }

    public void delete() throws NoSuchElementException {
	if (first == null) {
		throw new NoSuchElementException();
	}

	else if (first == last) {
		first = null;
		last = null;
		current = null;
        
	}

	else if (current == first) {
		first = first.next;
		current = first;
		first.prev = null;
	}
	
	else if (current == last) {
		last = last.prev;
		current = last;
		last.next = null;
		currentPosition --;
	}
	
	else {
		current.prev.next = current.next;
		current.next.prev = current.prev;
		current = current.next;
	}
	}

public void insert(String item, position pos) throws IllegalArgumentException {
        node n = new node();
        n.item = item;
        switch (pos) {
            case FIRST:
                if (isEmpty()) {
                    first = n;
                    last = n;
                    current = n;
                    currentPosition = 0;
                } else {
                    n.next = first;
                    first.prev = n;
                    first = n;
                    current = n;
                    currentPosition = 0;
                }
                break;
            case PREVIOUS:
                if (current == first) {
                    throw new IllegalArgumentException();
                } else {
                    n.prev = current.prev;
                    n.next = current;
                    current.prev.next = n;
                    current.prev = n;
                    current = n;
                }
                break;
            case FOLLOWING:
                if (current == last) {
                    throw new IllegalArgumentException();
                } else {
                    n.next = current.next;
                    n.prev = current;
                    current.next.prev = n;
                    current.next = n;
                    current = n;
                    currentPosition = currentPosition + 1;
                }
                break;
            case LAST:
                if (isEmpty()) {
                    first = n;
                    last = n;
                    current = n;
                    currentPosition = 0;
                } else {
                    node temp;
                    temp = first;
                    currentPosition = 0;
                    while (temp.next != null) {
                        currentPosition++;
                        temp = temp.next;
                    }
                    n.prev = last;
                    last.next = n;
                    last = n;
                    current = n;
                    currentPosition++;
                }

                break;
        }

    }

}
