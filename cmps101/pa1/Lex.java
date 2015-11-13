//Alix Feinsod
//afeinsod
//CMPS 101 PA1
//Lex.java - program to alphabetize files

import java.io.*;
import java.util.Scanner;

public class Lex {

    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            System.err.println("Usage: Lex infile outfile");
            System.exit(1);
        } else {
            BufferedReader reader = new BufferedReader(new FileReader(args[0]));
            int lines = 0;
            while (reader.readLine() != null) {
                lines++;
            }
            reader.close();
            String[] S = new String[lines];
            lines = 0;
            Scanner in = null;
            PrintWriter out = null;
            String line = null;
            in = new Scanner(new File(args[0]));
            out = new PrintWriter(new FileWriter(args[1]));

            //Adds all lines of input file to list of strings.
            while (in.hasNextLine()) {
                line = in.nextLine();
                S[lines++] = line;
            }
            in.close();
            
	    //sorting into indexList
            List L = new List();
	    L.append(0);
            for (int i = 1; i < S.length; i ++) {
		L.moveTo(0);
		while ((L.getIndex() >= 0) && (S[L.getElement()].compareTo(S[i])<0)) {
			L.moveNext();
		}
		if (L.getIndex() < 0) {
			L.append(i);
		}
		else {
			L.insertBefore(i);
		}
	    }

            //prints lines to doc
            for(L.moveTo(0); L.getIndex()>=0; L.moveNext()){
         	out.println(S[L.getElement()]);
	    }
            out.close();
        }
    }
}