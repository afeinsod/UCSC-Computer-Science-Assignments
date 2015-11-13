//Alix Feinsod
//afeinsod
//CMPS 101 PA3
//Sparse.java - Takes in a file and performs matrix operations on the 
//	matrixes from the file using Matrix.java, and outputs 
//	the results into a new file.
import java.io.*;
import java.util.Scanner;

public class Sparse {
    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            System.err.println("Usage: Sparse infile outfile");
            System.exit(1);
        } else {
             String line;
             String[] lineInfo;
            Scanner in = null;
            in = new Scanner(new File(args[0]));
            //grabs the first line of the infile, splits it up
             String firstline = in.nextLine();
             String[] values = firstline.split(" ");
             //creates new matrices with size n
             Matrix A = new Matrix(Integer.parseInt(values[0]));
             Matrix B = new Matrix(Integer.parseInt(values[0]));
             //stores info for number of entries in A and B
             int numEntriesA = Integer.parseInt(values[1]);
             int numEntriesB = Integer.parseInt(values[2]);
             
             //skips blank line
             line=in.nextLine();
             //fills the values of A
             for (int i =0; i<numEntriesA; i++) {
                line = in.nextLine();
                lineInfo= line.split(" ");
                A.changeEntry(Integer.parseInt(lineInfo[0]),Integer.parseInt(lineInfo[1]), Double.parseDouble(lineInfo[2]));
            }
             
             
             //skips a line
             line=in.nextLine();
             //fills the values of B
             for (int i =0; i<numEntriesB; i++) {
                line = in.nextLine();
                lineInfo= line.split(" ");
                B.changeEntry(Integer.parseInt(lineInfo[0]),Integer.parseInt(lineInfo[1]), Double.parseDouble(lineInfo[2]));
            }
           
            in.close();
            
            //outfile open
	   PrintWriter out = null;
            out = new PrintWriter(new FileWriter(args[1]));
            
            //prints out A info
            out.println("A has " + A.getNNZ() + " non-zero entries");
            out.println(A.toString());
        
            
            //print out B info
            out.println("B has " + B.getNNZ() + " non-zero entries");
            out.println(B.toString());
           
            
            //multiplies by scalar
            out.println("(1.5)*A =");
            out.println(A.scalarMult(1.5).toString());
            
            
            //adds A and B
            out.println("A+B =");
            out.println(A.add(B).toString());
            
            
            //adds A and A
            out.println("A+A =");
            out.println(A.add(A).toString());
          
            
             //subtracts A from B
            out.println("B-A =");
            out.println(B.sub(A).toString());
        
            
             //subtracts A from A
            out.println("A-A =");
            out.println(A.sub(A).toString());
          
            
             //transposes A
            out.println("Transpose(A) = ");
            out.println(A.transpose().toString());
           
            
             //multiplies A and B
            out.println("A*B =");
            out.println(A.mult(B).toString());
           
             //multiplies B and B
            out.println("B*B =");
            out.println(B.mult(B).toString());
         
            
            out.close(); 
        } 
    }

}
