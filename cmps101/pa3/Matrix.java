//Alix Feinsod
//afeinsod
//CMPS 101 Programming Assignment 3
//Matrix.java - Matrix ADT for PA3
class Matrix {

    private class Entry {

        int column;
        double value;

        //Constructor
        Entry(int c, double v) {
            this.column = c;
            this.value = v;
        }

        public boolean equals(Object X) {
            if (!(X instanceof Entry)) {
                return false;
            } else {
                Entry E = (Entry) X;
                if ((this.column == E.column) && (this.value == E.value)) {
                    return true;
                } else {
                    return false;
                }
            }
        }

        public String toString() {
            String s = "";
            s = "( " + this.column + ", " + this.value + ")";
            return s;
        }
    }

    int size;
    int numNNZ;
    List[] row;

    //private functions
    private static double dot(List P, List Q) {
        double product = 0;
        //check if either is a zero row
        if ((P.length() == 0) || (Q.length() == 0)) {
            return product;
        } //walk through both lists until over the edge
        else {
            P.moveTo(0);
            Q.moveTo(0);
            while ((P.getIndex() > -1) && (Q.getIndex() > -1)) {
                //if the columns match up
                if (((Entry) P.getElement()).column == ((Entry) Q.getElement()).column) {
                    //add their value to the end result and move on from both
                    product = product + (((Entry) P.getElement()).value * ((Entry) Q.getElement()).value);
                    P.moveNext();
                    Q.moveNext();
                } else if (((Entry) P.getElement()).column < ((Entry) Q.getElement()).column) {
                    //if the P list is behind the Q list, increment P
                    P.moveNext();
                } else {
                    Q.moveNext();
                }
            }
            return product;
        }
    }

    
    private List add(List P, List Q) {
        List sum = new List();
        //check if either is a zero row
        if (P.length() == 0) {
		return Q;
	    }
	 else if (Q.length() == 0) {
		return P;
	    }
	 else if (P.equals(Q)) {
	     P.moveTo(0);
	     while (P.getIndex() >-1) {
		 Entry e;
		 e = new Entry(((Entry) P.getElement()).column, 2*(((Entry) P.getElement()).value));
		 sum.append(e);
		 P.moveNext();
	     }
	     return sum;
	 }
        //walk through both lists until over the edge
        else {
            P.moveTo(0);
            Q.moveTo(0);
	    while ((P.getIndex() > -1) && (Q.getIndex() > -1)) {
                //if the columns match up
                if (((Entry) P.getElement()).column == ((Entry) Q.getElement()).column) {
                    //add their value to the end result and move on from both
                    if ((((Entry) P.getElement()).value + ((Entry) Q.getElement()).value) != 0) {
			Entry e;
			e = new Entry(((Entry) P.getElement()).column, (((Entry) P.getElement()).value + ((Entry) Q.getElement()).value));
			sum.append(e);
		    }
                    P.moveNext();
		    Q.moveNext();
                } else if (((Entry) P.getElement()).column < ((Entry) Q.getElement()).column) {
                    //if the P list is behind the Q list, increment P
		    Entry e;
                    e = new Entry(((Entry) P.getElement()).column, ((Entry) P.getElement()).value);
		    if (e.value !=0) {
			sum.append(e);}
                    P.moveNext();
                } else {
		     Entry e;
                    e = new Entry(((Entry) Q.getElement()).column, ((Entry) Q.getElement()).value);
		    if (e.value !=0) {
			sum.append(e);}
                    Q.moveNext();
                }
	    }
		//finish lists if not same length
	        while (P.getIndex() >-1) {
		    Entry e;
		    e = new Entry(((Entry) P.getElement()).column, ((Entry) P.getElement()).value);
                    if (e.value !=0) {
                        sum.append(e);
		    }
		   P.moveNext();
            }
		while (Q.getIndex() >-1) {
		    Entry e;
		    e = new Entry(((Entry) Q.getElement()).column, ((Entry) Q.getElement()).value);
		    if (e.value !=0) {
			sum.append(e);
		    }   
		   Q.moveNext();
	       }
            return sum;
        }
    }
    
    private List sub(List P, List Q) {
        List sub = new List();
	//check if rows are equal
	if (P.equals(Q)) {
	    return sub;
	}
        //check if either is a zero row
	else if (P.length() == 0) {
	   Q.moveTo(0);
	   while(Q.getIndex() > -1) {
	         Entry e;
	         e = new Entry(((Entry) Q.getElement()).column, -((Entry) Q.getElement()).value);
		 sub.append(e);
		 Q.moveNext();
	    }
	   return sub;
       }
	 else if (Q.length() == 0) {
		return P;
	 }
        //walk through both lists until over the edge
        else {
            P.moveTo(0);
            Q.moveTo(0);
            while ((P.getIndex() > -1) && (Q.getIndex() > -1)) {
                //if the columns match up
                if (((Entry) P.getElement()).column == ((Entry) Q.getElement()).column) {
                    //add their value to the end result and move on from both
		    if ((((Entry) P.getElement()).value - ((Entry) Q.getElement()).value) != 0) {
			Entry e;
			e = new Entry(((Entry) P.getElement()).column, (((Entry) P.getElement()).value - ((Entry) Q.getElement()).value));
			sub.append(e);
		    }
                    P.moveNext();
                    Q.moveNext();
                } else if (((Entry) P.getElement()).column < ((Entry) Q.getElement()).column) {
                    //if the P list is behind the Q list, increment P
			Entry e;
			e = new Entry(((Entry) P.getElement()).column, ((Entry) P.getElement()).value);
			sub.append(e);
                    	P.moveNext();
                } else {
			Entry e;
			e = new Entry(((Entry) Q.getElement()).column, -((Entry) Q.getElement()).value);
			sub.append(e);
                    	Q.moveNext();
                }
            }
		//finish both lists if not same length
	    while (P.getIndex() >-1) {
		    Entry e;
		    e = new Entry(((Entry) P.getElement()).column, ((Entry) P.getElement()).value);
		    sub.append(e);
		    P.moveNext();
            }
	    while (Q.getIndex() >-1) {
		    Entry e;
		    e = new Entry(((Entry) Q.getElement()).column, -((Entry) Q.getElement()).value);
		    sub.append(e);
		    Q.moveNext();
	    }
            return sub;
        }
    }
    // Constructor
    Matrix(int n) {// Makes a new n x n zero Matrix.
        //pre: n>=1
        if (n < 1) {
            throw new RuntimeException("Called Matrix constructor on integer less than 1");
        } else {
            numNNZ = 0;
            size = n;
            this.row = new List[n + 1];
            for (int i = 0; i < n + 1; i++) {
                row[i] = new List();
            }
        }
    }

// Access functions
    int getSize() {// Returns n, the number of rows and columns of this Matrix
        return this.size;
    }

    int getNNZ() {// Returns the number of non-zero entries in this Matrix
        return this.numNNZ;
    }

    public boolean equals(Object X) {// overrides Object's equals()method
        if (!(X instanceof Matrix)) {
            return false;
        } else {
            if ((this.size != ((Matrix) X).size) || ((this.numNNZ != ((Matrix) X).numNNZ))) {
                return false;
            } else {
                for (int i = 0; i <= this.size; i++) {
                    if (!(this.row[i].equals(((Matrix) X).row[i]))) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    // Manipulation procedures
    void makeZero() {//sets this Matrix to the zero state
        for (int i = 0; i <= size; i++) {
            this.row[i].clear();
        }
        size = 0;
        numNNZ = 0;
    }

    Matrix copy(){ // returns a new Matrix having the same entries as this Matrix
	Matrix M = new Matrix(this.size);
	for (int i =1; i <=this.size; i++) {
	    M.row[i]=this.row[i];
	}
	return M;
    }

 void changeEntry(int i, int j, double x) {// changes ith row, jth column of this Matrix to x
        // pre: 1<=i<=getSize(), 1<=j<=getSize()
        //check for prereqs
        if (!(1 <= i) && (i <= getSize()) && (1 <= j) && (j <= getSize())) {
            throw new RuntimeException("Matrix Error: called changeEntry() on invalid row or column value");
        } else {
            //if prereqs are ok, checks if there isn't a list in the ith row, and if 
            //x is nonzero, add x to this empty list
            if ((this.row[i].length() == 0) && (x != 0)) {
                Entry e = new Entry(j, x);
                this.row[i].append(e);
                numNNZ++;
            } else {
                //move to beginning of correct row's list
                this.row[i].moveTo(0);
                //moves to correct stop in the list
                while (this.row[i].getIndex() > -1 && (((Entry) this.row[i].getElement()).column < j)) {
                    this.row[i].moveNext();
                }

                //checks if we have gone off the end of the list:
                if (this.row[i].getIndex() == -1) {
                    if (x != 0) {
                        Entry e = new Entry(j, x);
                        this.row[i].append(e);
                        numNNZ++;
                    }
                } else {
                    //checks if there is an element in the jth column
                    if (((Entry) this.row[i].getElement()).column == j) {
                        //if we are inerting a zero, delete the element there
                        if (x == 0) {
                            this.row[i].delete();
                            numNNZ--;
                        } else {
                            //otherwise, replace existing entry with x
                            Entry e = new Entry(j, x);
                            this.row[i].insertBefore(e);
                            this.row[i].delete();
                        }
                    } else {
                        //if there is not already an entry in the jth column,
                        //and if x isn't zero, we insert x.
                        //if x is zero, we do nothing
                        if (x != 0) {
                            Entry e = new Entry(j, x);
                            this.row[i].insertBefore(e);
                            numNNZ++;
                        }
                    }
                }
            }
        }
    }

// returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x) {
        Matrix M = new Matrix(this.size);
        if (x == 0) {
            //return empty matrix if multiplying by zero
            return M;
        } else {
            //go through all the rows
            for (int i = 1; i <= this.size; i++) {
                //if the row is not empty, go through the row 
                if (this.row[i].length() != 0) {
                    this.row[i].moveTo(0);
                    while (this.row[i].getIndex() > -1) {
                        //for each entry, creates a new entry with same column value
                        //and scaled value
                        Entry e;
                        e = new Entry(((Entry) this.row[i].getElement()).column, ((Entry) this.row[i].getElement()).value * x);
                        M.row[i].append(e);
                        this.row[i].moveNext();
                    }
                }
            }
            return M;
        }
    }
    
// returns a new Matrix that is the sum of this Matrix with M
// pre: getSize()==M.getSize()
 Matrix add(Matrix M) {
     if (this.getSize() != M.getSize()) {
        throw new RuntimeException("Matrix Error: add called on incompatible matrices");
    }
    else {
       Matrix added = new Matrix(this.size);
        for (int i = 0; i <= this.size; i ++) {
	   if ((this.row[i].length() !=0) || (M.row[i].length() != 0)) {
           	added.row[i]= add(this.row[i], M.row[i]);
	   }
        }
        return added;
     }
}

// returns a new Matrix that is the difference of this Matrix with M
// pre: getSize()==M.getSize()
 Matrix sub(Matrix M) {
     if (this.getSize() != M.getSize()) {
        throw new RuntimeException("Matrix Error: sub called on incompatible matrices");
    }
    else {
       Matrix subbed = new Matrix(this.size);
        for (int i = 0; i <= this.size; i ++) {
	   if ((this.row[i].length() !=0) || (M.row[i].length() != 0)) {
           	subbed.row[i]= sub(this.row[i], M.row[i]);
	    }
        }
        return subbed;
        }
 }
    
// returns a new Matrix that is the transpose of this Matrix
    Matrix transpose() {
   Matrix M = new Matrix(this.size);
   for (int i = 1; i <=this.size; i ++) {
       if (this.row[i].length() != 0) {
           this.row[i].moveTo(0);
           while (this.row[i].getIndex() > -1) {
               Entry e;
               e = new Entry(i, ((Entry) this.row[i].getElement()).value);
               M.row[((Entry) this.row[i].getElement()).column].append(e);
               this.row[i].moveNext();
           }
       }
   }
   return M;
}
    
// returns a new Matrix that is the product of this Matrix with M
// pre: getSize()==M.getSize()
Matrix mult(Matrix M) {
    if (this.getSize() != M.getSize()) {
        throw new RuntimeException("Matrix Error: mult called on incompatible matrices");
    }
    else {
       Matrix multiplied = new Matrix(this.size);
        Matrix T = M.transpose();
        for (int i = 0; i <= this.size; i ++) {
	    if (this.row[i].length() != 0) {
            	for (int j = 0; j <= this.size; j++) {
			if (T.row[i].length() != 0) {
                		if ((dot(this.row[i], T.row[j])) != 0) {
                			Entry e;
                			e = new Entry(j, dot(this.row[i], T.row[j]));
                			multiplied.row[i].append(e);
            			}
			}
		
	    }
        }
    }
        
    return multiplied;
}
}

    
    
// Other functions

    public String toString() {//overrides Object's toString() method
        String s = "";
        for (int i = 0; i < row.length; i++) {
            if (row[i].length() != 0) {
                s = s + i + ": ";
                row[i].moveTo(0);
                while (row[i].getIndex() > -1) {
                    s = s + row[i].getElement().toString() + " ";
                    row[i].moveNext();
                }
                s = s + "\n";
            }
        }
        return s;
    }
}
