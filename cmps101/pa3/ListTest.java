//Alix Feinsod
//afeinsod
//CMPS 101, PA3
//ListTest.java: Class to test the Doubly Linked List ADT

class ListTest{

	public static void main(String args[]) {
		List A = new List();
		for (int i = 1; i<16; i++) {
			A.append(i);
		}
		System.out.println(A.toString());
		System.out.println(A.length());
		List B = new List();
		for(A.moveTo(0); A.getIndex() >-1; A.moveNext()) {
			B.prepend(A.getElement());
		}
		System.out.println(B.toString());
		System.out.println(B.length());
		System.out.println((int) A.front() + (int) B.front());
		System.out.println(A.back() == B.back());
		System.out.println(A.equals(B));
		System.out.println(A.equals(A));
		A.clear();
		System.out.println(A.length());
		A.append(3);
		A.prepend(1);
		A.prepend(1);
		A.append(7);
		A.moveTo(3);
		A.insertAfter(8);
		A.insertBefore(5);
		A.moveNext();
		A.insertAfter(13);
		A.movePrev();
		A.delete();
		System.out.println(A.toString());
		A.deleteFront();
		A.deleteBack();
		System.out.println(A.toString());


//Should output:
//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
//15
//15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
//15
//16
//false
//false
//true
//0
//1 1 3 5 8 13
//1 3 5 8
}
		
}