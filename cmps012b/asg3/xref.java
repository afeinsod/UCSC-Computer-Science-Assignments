//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B
//xref.java
//Main for asg3

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class xref {

    static void processFile(String filename, boolean debug) throws IOException {
        Scanner scan = new Scanner (new File(filename));
        Tree tree = new Tree();
        for (int linenr = 1; scan.hasNextLine (); ++linenr) {
            for (String word: scan.nextLine().split ("\\W+")) {
                tree.insert(word, linenr);
            }
        }
        scan.close();
        if (debug) {
            tree.debug();
        } else {
            tree.output();
        }
    }

    public static void main(String[] args) {
	boolean debug = false;
	String filename="";
	if (args.length !=0) {
	    if (args[0].equals("-d")) {
		debug = true;
		if (args[1] != null) {
			filename = args[1];
		}
	    }
	    else {
		filename = args[0];
	    }
	}
        try {
            processFile(filename, debug);
        }catch (IOException error) {
            auxlib.warn (error.getMessage());
        }
        auxlib.exit();

    }
}
