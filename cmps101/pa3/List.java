//Alix Feinsod
//afeinsod
//CMPS 101, PA3
//List.java: Doubly Linked List ADT, edited for PA3

class List {

	private class Node{
      		// Fields
	        Object data;
		Node previous;
      		Node next;
      		// Constructor
      		Node(Object data) { 
			this.data = data; 
			next = null; 
		}
      		// toString:  Overides Object's toString method.
      		public String toString() { 
		    return (data.toString()); 
		}
   	}

	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int cursorIndex;
	private int length;

	// Constructor

	//Creates a new empty list.
	List() { 
		front = back = cursor = null;
		cursorIndex = -1;
		length = 0;
	}

	//Access functions

	// Returns number of elements in this list.
	int length() { 
		return length;
	}

	// Returns the index of the cursor element in this list, or
	//returns -1 if the cursor element is undefined.
	int getIndex() { 
		return cursorIndex;
	}

	// Returns front element in this list. Pre: length()>0
	Object front() { 
		if (length == 0) {
			throw new RuntimeException("List Error: front() called on empty List");
		}
		else {
			return front.data;
		}
	}

	// Returns back element in this List. Pre: length()>0
	Object back() { 
		if (length == 0) {
			throw new RuntimeException("List Error: back() called on empty List");
		}
		else {
			return back.data;
		}
	}

	// Returns cursor elementin this list.
	// Pre: length()>0,getIndex()>=0
	Object getElement() { 
		if (length == 0) {
			throw new RuntimeException("List Error: getElement() called on empty List");
		}
		else if (getIndex() < 0) {
			throw new RuntimeException("List Error: getElement() called with null index");
		}
		else {
			return cursor.data;
		}
	}

	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object X) {
      		if (!(X instanceof List)) {
			return false;
		}
		else {
		List L = (List) X;
		boolean flag  = true;
      		Node N = this.front;
      		Node M = L.front;

      		if(this.length==L.length){
         		while( flag && N!=null){
            			flag = (N.data==M.data);
            			N = N.next;
            			M = M.next;
         		}
         		return flag;
      		}
		else {
         		return false;
      		}
		}
   	}

	// Manipulation procedures

	// Re-sets this List to the empty state.
	void clear() {
		this.front = this.back = this.cursor = null;
		this.cursorIndex = -1;
		this.length = 0;
	}

	// If 0<=i<=length()-1, moves the cursor to the element
	// at index i, otherwise the cursor becomes undefined.
	void moveTo(int i) {
		if ((0<=i) && (i<=(length-1))) {
			cursorIndex = i;
			cursor = front;
			if (i != 0) {
				for (int j = 0; j<i; j++) {
					cursor = cursor.next;
				}
			}
		}
		else {
			cursorIndex = -1;
			cursor = null;
		}
	}

	// If 0<getIndex()<=length()-1, moves the cursor one step toward the
	// front of the list. If getIndex()==0, cursor becomes undefined.
	// If getIndex()==-1, cursor remains undefined.This operation is
	// equivalent to moveTo(getIndex()-1).
	void movePrev() {
		if ((0<cursorIndex) && (cursorIndex <= (length-1))) {
			cursor = cursor.previous;
			cursorIndex --;
		}
		else if (cursorIndex == 0) {
			cursor = null;
			cursorIndex = -1;
		}
		else {}
	}

	// If 0<=getIndex()<length()-1, moves the cursor one step toward the
	// back of thelist. If getIndex()==length()-1, cursor becomes
	// undefined. If getIndex()==-1, cursor remains undefined. This
	// operation is equivalent to moveTo(getIndex()+1).
	void moveNext() {
		if ((0<=cursorIndex) && (cursorIndex < (length-1))) {
			cursor = cursor.next;
			cursorIndex ++;
		}
		else if (cursorIndex == (length-1)) {
			cursor = null;
			cursorIndex = -1;
		}
		else {}
	}

	// Inserts new element before front element in this List.
	void prepend(Object data) {
		Node n = new Node(data);
		if (this.length == 0) {
			front=back=n;
                        length++;
		}
		else {
			front.previous = n;
			n.next = front;
			front = n;
			length ++;
		}
	}

	// Inserts new element after back element in this List.
	void append(Object data) {
		Node n = new Node(data);
		if (this.length == 0) {
			front=back=n;
                        length++;
		}
		else {
			back.next = n;
			n.previous = back;
			back = n;
			length ++;
		}
	}

	// Inserts new element before cursor element in this
	// List.Pre: length()>0, getIndex()>=0
	void insertBefore(Object data) {
		if (this.length <= 0) {
			throw new RuntimeException("List Error: called insertBefore() on empty list.");
		}
		else if (getIndex() <0) {
			throw new RuntimeException("List Error: called insertBefore() with null index.");
		}
		else {
			Node n = new Node(data);
			if (cursor == front) {
			    front = n;
			    n.next = cursor;
			    cursor.previous = n;
			    length ++;
			    cursorIndex ++;
			}
			else {
			    cursor.previous.next = n;
			    n.previous = cursor.previous;
			    n.next = cursor;
			    cursor.previous = n;
			    length ++;
			    cursorIndex ++;
			}
		}
	}

	// Inserts new element after cursor element in this
	// List. Pre: length()>0, getIndex()>=0
	void insertAfter(Object data) {
		if (length <= 0) {
			throw new RuntimeException("List Error: called insertAfter() on empty list.");
		}
		else if (getIndex() <0) {
			throw new RuntimeException("List Error: called insertAfter() with null index.");
		}
		else {
			Node n = new Node(data);
			if (cursor == back) {
			    back = n;
			    n.previous = cursor;
			    cursor.next = n;
			    length ++;
			}
			else {
			    cursor.next.previous = n;
			    n.next = cursor.next;
			    n.previous = cursor;
			    cursor.next = n;
			    length ++;
			}
		}
	}

	// Deletes the front element in this List. Pre: length()>0
	void deleteFront() {
		if (length == 0) {
			throw new RuntimeException("List error: called deleteFront on empty list.");
		}
		else {
			front = front.next;
			if (cursorIndex == 0) {
				cursorIndex = -1;
				cursor = null;
			}
			length --;
		}
	}

	// Deletes the back element in this List.Pre: length()>0
	void deleteBack() {
		if (length == 0) {
			throw new RuntimeException("List error: called deleteBack on empty list.");
		}
		else {
			
			if (cursor == back) {
				cursorIndex = -1;
				cursor = null;
			}
			back = back.previous;
			back.next = null;
			length --;
		}
	}

	// Deletes cursor element in this List. Cursor is undefined after this
	// operation. Pre: length()>0, getIndex()>=0
	void delete() {
		if (length <= 0) {
			throw new RuntimeException("List Error: called delete() on empty list.");
		}
		else if (getIndex() <0) {
			throw new RuntimeException("List Error: called delete() with null index.");
		}
		else {
                    if (getIndex() ==0) {
                        front = front.next;
                        cursorIndex = -1;
			cursor = null;
			length --;
                    }
                    else if (getIndex() == length) {
                        back = back.previous;
                        cursorIndex = -1;
			cursor = null;
			length --;
                    }
                    else {
			cursor.previous.next = cursor.next;
			cursor.next.previous = cursor.previous;
			cursorIndex = -1;
			cursor = null;
			length --;
                    }
		}
	}

	// Other methods

	// Overides Object's toString method. Creates a string
	// consisting of a space separated sequence of integers
	// with front on the left and back on the right. The
	// cursor is ignored.
	public String toString() {
		String txt = "";
		Node n = front;
		while (n != null) {
			txt=txt+n.toString()+ " ";
			n=n.next;
		}
		return txt;
	}
}
