//Alix Feinsod
//afeinsod
//CMPS 101 PA3
//MatrixTest.java - tester for Matrix ADT
public class MatrixTest {
    public static void main(String[] args) {
        Matrix A = new Matrix(2);
        A.changeEntry(1,1,1);
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        A.changeEntry(1,2,2);
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        A.changeEntry(2, 1, 3);
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        A.changeEntry(2,2,4);
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        System.out.println(A.toString());
        A.changeEntry(2,1,0);
        A.changeEntry(2,2,0);
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        System.out.println(A.toString());
        
        Matrix B = new Matrix(3);
        B.changeEntry(1,1,1);
        B.changeEntry(2,2,1);
        B.changeEntry(3,3,1);
        System.out.println(B.toString());
        Matrix C = B.scalarMult(2);
        System.out.println(C.toString());
        
        Matrix D = new Matrix(2);
        D.changeEntry(1,1,1);
        D.changeEntry(1,2,2);
        D.changeEntry(2,1,3);
        D.changeEntry(2,2,4);
        System.out.println(D.toString());
        Matrix E = D.transpose();
        System.out.println(E.toString());
        Matrix F = A.mult(E);
        System.out.println(F.toString());
        Matrix dplusd = D.add(D);
        System.out.println(dplusd.toString());

	A.makeZero();
        System.out.println("Size: " + A.size + ", numNNZ: " + A.numNNZ);
        
    }
    
}

/*
Expected output:

Size: 2, numNNZ: 1
Size: 2, numNNZ: 2
Size: 2, numNNZ: 3
Size: 2, numNNZ: 4
1: ( 1, 1.0) ( 2, 2.0)
2: ( 1, 3.0) ( 2, 4.0)

Size: 2, numNNZ: 2
1: ( 1, 1.0) ( 2, 2.0)

1: ( 1, 1.0)
2: ( 2, 1.0)
3: ( 3, 1.0)

1: ( 1, 2.0)
2: ( 2, 2.0)
3: ( 3, 2.0)

1: ( 1, 1.0) ( 2, 2.0)
2: ( 1, 3.0) ( 2, 4.0)

1: ( 1, 1.0) ( 2, 3.0)
2: ( 1, 2.0) ( 2, 4.0)

1: ( 1, 5.0) ( 2, 11.0)

1: ( 1, 2.0) ( 2, 4.0)
2: ( 1, 6.0) ( 2, 8.0)

Size: 0, numNNZ: 0
*/