//Alix Feinsod
//CruzID: afeinsod
//CMPS 12B/M
//cyoa.java
//includes all classes and main for the Choose Your Own Adventure program, assignment 4

import java.util.Scanner;
import static java.lang.System.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class option {
    /*
    -has a String called optionTag
    -has a string with the text of the option
    -has a char letter (a-l)     */

    public String optionTag;
    public String text;
    public char letter;
    
//Constructor
    option(char a) {
        letter = a;
    }
    
//Method to set the tag of the option
    public void setOptionTag(String r) {
        optionTag = r;
    }
    
}

class room {
    /*
    -has an unordered array of Strings called description, can be added to or printed out
    -has an unordered array of options, can be added to and printed out
    -has a play method that presents the options
    */
    public String tag;
    public String[] description;
    public option[] options;
    public int numOptions;
    public int numDescriptions;
    
//Constructor, creates room with no options and no description with tag s
    room(String s) {
        numOptions = 0;
        numDescriptions = 0;
	description = new String[20];
        tag = s;
        options = new option[12];
        options[0] = new option('a');
        options[1] = new option('b');
        options[2] = new option('c');
        options[3] = new option('d');
        options[4] = new option('e');
        options[5] = new option('f');
        options[6] = new option('g');
        options[7] = new option('h');
        options[8] = new option('i');
        options[9] = new option('j');
        options[10] = new option('k');
        options[11] = new option('l');
        
    }

//method to add options    
    public void addOption(String s) {
        options[numOptions].text = s;
        numOptions++;
    }
    
//method to add lines of description
    public void addDescription(String s) {
        description[numDescriptions] = s;
        numDescriptions++;
    }
    
//method to update the tag of the most recent option
    public void updateDestinationTag(String r) {
        options[numOptions - 1].setOptionTag(r);
    }
    
//method to print out the options
    public void play() {
        for (int i = 0; i < numDescriptions; i++) {
            System.out.println(description[i]);
        }
        for (int i = 0; i < numOptions; i++) {
            System.out.println(options[i].letter + " : " + options[i].text);
        }
    }
    
//method to print out the tag of the room and the tag of the rooms represented by the options
    public void printRoom() {
        System.out.print(tag + " : ");
        for (int i = 0; i < numOptions; i ++) {
            System.out.print(options[i].optionTag + " ");
        }
        System.out.println();
    }
}

class Stack {

//Stack used to store the rooms that have been visited during game play, 
// so that the "z" option works

    private room[] stack;
    private int size;

    // Constructor for stack
    Stack() {
        stack = new room[100];
    }

    public void push(room d) {
        stack[size++] = d;
    }

    public room pop() {
        room temp = stack[size - 1];
        stack[size - 1] = null;
        size--;
        return temp;
    }

    public room peek() {
        return stack[size - 1];
    }

    public int size() {
        return size;
    }

}

public class cyoa {

//Sort method for sorting the array of rooms
	public static room[] sort(room[] arr){
         
        for (int i = 0; i < arr.length - 1; i++)
        {
            int index = i;
            for (int j = i + 1; j < arr.length; j++)
                if (arr[j].tag.compareTo(arr[index].tag) < 0)
                    index = j;
      
            room smallerRoom = arr[index]; 
            arr[index] = arr[i];
            arr[i] = smallerRoom;
        }
        return arr;
    }   
   
//main method
    public static void main(String[] args) throws IOException {

	int exitStatus = 0;
        Stack roomsPlaying = new Stack();
        room[] rooms = new room[100];
        int numRooms = 0;

        if (args.length == 0) {
//in no input file speicified, prints usage info
            System.out.println("Usage: cyoa adventurefile");
        } else {
//reads in game file, creates all rooms and options 
	    String needBreak;
            String line;
            String fileIn = null;
            Scanner stdin = new Scanner(in);
            fileIn = args[0];
            try (BufferedReader in = new BufferedReader(
                    new FileReader(fileIn))) {
                while ((line = in.readLine()) != null) {
			if ( line.trim().length() == 0 ) {  
    				continue;  // Skip blank lines  
  				}
                    char command = line.charAt(0);
                    switch (command) {
                        case 'r':
			//creates a new room
                            room r = new room(line.substring(2));
                            rooms[numRooms++] = r;
                            break;
                        case 'd':
			//updates the description of the most recently added room
                            if (numRooms == 0) {
                                exitStatus = 1;
                            } else {
                                rooms[numRooms-1].addDescription(line.substring(2));
                            }
                            break;
                        case 'o':
			//adds an option to the most recently added room
                            if (numRooms == 0) {
                                exitStatus = 1;
                            } else {
                                rooms[numRooms-1].addOption(line.substring(2));
                            }
                            break;
                        case 't':
			//updates the tag of the most recently added option to the most recently added room
                            if (numRooms == 0) {
                                exitStatus = 1;
                            } else if (rooms[numRooms-1].numOptions == 0) {
				exitStatus = 1;
                            } else {
                                rooms[numRooms-1].updateDestinationTag(line.substring(2));
                            }
                            break;
                        default:
                            break;
                    }

                }
//end parsing file. Stores first room so it doesn't get lost in the sort
		room firstRoom = rooms[0];
//creates a temporary array of rooms so that rooms can be updated to correct size array, or else sort won't work.
		room []temp = new room[numRooms];
		for (int i = 0; i < numRooms; i ++) {
			temp[i] = rooms[i];
		}
		rooms = new room[numRooms];
		for (int i = 0; i < numRooms; i ++) {
			 rooms[i] = temp[i];
		}
//sorts the array of rooms into alphabetical order
		sort(rooms);
//pushes the first room onto the stack rooms in play
                roomsPlaying.push(firstRoom);
//displays the first room's information
                roomsPlaying.peek().play();
//begins play
		needBreak = "no";
                while (!needBreak.equals("yes")) {
                    if (!stdin.hasNextLine()) {
                        break;
                    }
                    String inputline = stdin.nextLine();
                    if (inputline.matches("^\\s*$")) {
                        continue;
                    }
		    int i = 0;
                    char command = inputline.charAt(0);
                    switch (command) {
		//cases a-l find room with that destination tag, then push that room onto the stack and display its options.
                    case 'a':
                        if (roomsPlaying.peek().numOptions < 1) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[0].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[0].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                 break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'b':
                        if (roomsPlaying.peek().numOptions < 2) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[1].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[1].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                 break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'c':
                        if (roomsPlaying.peek().numOptions < 3) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[2].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[2].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
				    break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'd':
                        if (roomsPlaying.peek().numOptions < 4) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[3].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[3].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                  break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'e':
                        if (roomsPlaying.peek().numOptions < 5) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[4].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[4].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                  break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'f':
                        if (roomsPlaying.peek().numOptions < 6) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[5].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[5].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                   break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'g':
                        if (roomsPlaying.peek().numOptions < 7) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[6].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[6].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                   break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'h':
                        if (roomsPlaying.peek().numOptions < 8) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[7].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[7].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                   break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'i':
                        if (roomsPlaying.peek().numOptions < 9) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[8].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[8].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                  break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'j':
                        if (roomsPlaying.peek().numOptions < 10) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[9].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[9].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                   break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'k':
                        if (roomsPlaying.peek().numOptions < 11) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[10].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[10].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
                                   break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
                    case 'l':
                        if (roomsPlaying.peek().numOptions < 12) {
                            System.out.println("Not a valid option");
                        } else {
                            System.out.println("[" + roomsPlaying.peek().options[11].text + "]");
                            for (i = 0; i < numRooms; i++) {
                                if (rooms[i].tag.equals(roomsPlaying.peek().options[11].optionTag)) {
                                    roomsPlaying.push(rooms[i]);
                                    roomsPlaying.peek().play();
				    break;
                                }
                            }
			    if (i == numRooms) {
					System.out.println("Destination tag does not match any rooms.");
					exitStatus = 1;
				}
                        }
                        break;
		//case r restarts the game
                    case 'r':
                        roomsPlaying = new Stack();
                        roomsPlaying.push(firstRoom);
                        roomsPlaying.peek().play();
                        break;
                    case 'q':
		//case q ends the program
                        needBreak = "yes";
                        break;
                    case 'y':
		//case y prints out the information for all the rooms
                        System.out.println("[Information]");
                        for (i = 0; i < numRooms; i++) {
                            rooms[i].printRoom();
                        }
                        break;
		//case z goes back a room by popping off of the rooms playing stack
                    case 'z':
                        if (roomsPlaying.size() <= 1) {
                            System.out.println("Invalid command, cannot go back because in first room.");
                        } else {
                            roomsPlaying.pop();
                            roomsPlaying.peek().play();
                        }
                        break;
                    default:
                        System.out.println("Invalid command.");
                        break;
                }
            }
		//displays exit status
                System.out.println("Exit Status is " + exitStatus);
            }

        }

    }
}