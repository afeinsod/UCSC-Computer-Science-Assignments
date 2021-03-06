//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B
// edfile.java
// Line-oriented text editor inspired by ed.

import java.util.Scanner;
import static java.lang.System.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

class edfile{

   public static void main (String[] args) throws IOException {
      String line;
      String fileIn = null;
      boolean want_echo = false;
      dllist lines = new dllist();
      Scanner stdin = new Scanner (in);
      if (args.length !=0) {
	if (args[0].equals("-e")) {
		want_echo = true;
		if (args[1] != null) {
			fileIn = args[1];
		}
	}
	else {
	fileIn = args[0];
	}
      
	try (BufferedReader in = new BufferedReader(
                    new FileReader(fileIn))) {
                while ((line = in.readLine()) != null) {
                    lines.insert(line, dllist.position.LAST);
                }

            }
	
      }


      for (;;) {
         if (! stdin.hasNextLine()) break;
         String inputline = stdin.nextLine();
         if (want_echo) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         char command = inputline.charAt(0);
         switch (command) {
            case '#': break;
            case '$': if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			lines.setPosition(dllist.position.LAST);
			System.out.println(lines.getItem());
		}
		break;
	    case '*': if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			lines.setPosition(dllist.position.LAST);
			String temp = lines.getItem();
			lines.setPosition(dllist.position.FIRST);
	        	while (lines.getItem() != temp) {
		    		System.out.println(lines.getItem());
		    		lines.setPosition(dllist.position.FOLLOWING);
		}
		System.out.println(temp);
		}
	        break;
	    case '.': if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			System.out.println(lines.getItem());
		}
		break;
	    case '0': if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			lines.setPosition(dllist.position.FIRST);
			System.out.println(lines.getItem());
		}
		break;
            case '<':  if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			lines.setPosition(dllist.position.PREVIOUS);
			System.out.println(lines.getItem());
		}
		break;
            case '>':  if (lines.isEmpty()) {
			System.out.println("no lines in editor.");
		}
		else { 
			lines.setPosition(dllist.position.FOLLOWING);
			System.out.println(lines.getItem());
		}
		break;
	    case 'a': if (lines.isEmpty()) {
			lines.insert(inputline.substring(1), dllist.position.FIRST);
			System.out.println(lines.getItem());
		}
		else {
			try { 
			lines.insert(inputline.substring(1), dllist.position.FOLLOWING);
			System.out.println(lines.getItem());
			}
			catch (IllegalArgumentException e) {
			lines.insert(inputline.substring(1), dllist.position.LAST);
			System.out.println(lines.getItem());
			}
		}
		break;
	    case 'd': if (! lines.isEmpty()) {
			lines.delete();
			}
		break;
            case 'i': if (lines.isEmpty()) {
			lines.insert(inputline.substring(1), dllist.position.FIRST);
			System.out.println(lines.getItem());
		}
		else {
			try { 
			lines.insert(inputline.substring(1), dllist.position.PREVIOUS);
			System.out.println(lines.getItem());
			}
			catch (IllegalArgumentException e) {
			lines.insert(inputline.substring(1), dllist.position.FIRST);
			System.out.println(lines.getItem());
			}
		}
		break;
            case 'r': fileIn = inputline.substring(1);
		int tempint = 0; 
		try (BufferedReader in = new BufferedReader(
                    new FileReader(fileIn))) {
                	while ((line = in.readLine()) != null) {
                    		lines.insert(line, dllist.position.FOLLOWING);
				tempint ++;
                	}
		}
		System.out.println(tempint + " new lines inserted.");
		break;
            case 'w': String fileOut = inputline.substring(1);
		lines.setPosition(dllist.position.LAST);
		String temp = lines.getItem();
		tempint = 0;
		lines.setPosition(dllist.position.FIRST);
		try (PrintWriter out = new PrintWriter (new BufferedWriter(new FileWriter(fileOut)))) {
		        	while (lines.getItem() != temp) {
		    		out.write(lines.getItem() + "\n");
		    		lines.setPosition(dllist.position.FOLLOWING);
				tempint ++;
				}
				out.write(temp);
				tempint ++;
				out.close();
		}
		System.out.println(tempint + " lines printed to " + fileOut);
	        break;

            default : System.out.println("Invalid Command"); break;
         }
      }
      auxlib.die("(eof)");
   }

}

