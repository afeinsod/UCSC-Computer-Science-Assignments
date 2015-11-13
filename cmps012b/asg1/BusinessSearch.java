//Alix Feinsod
//CruzID: afeinsod
//Programming Assignment 1
//CMPS 12B
//Due October 22, 2014
//BusinessSearch.java


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;



//this class holds each business record

class businessRecord {
    private String name;
    private String phoneNumber;
   
    //Constructor
    businessRecord(String newName, String newPhoneNumber) {
        name = newName;
        phoneNumber = newPhoneNumber;
    }
    //Access Name
    public String getName() {
        return name;
    }
    //Access Phone Number
    public String getPhoneNumber() {
        return phoneNumber;
    }
    //Set Name
    public void setName(String n) {
        name = n;
    }
    //set Phone Number
    public void setPhoneNumber(String n) {
        phoneNumber = n;
    }
    //returns string with business information
    public String stringOut() {
        return name + " , " + phoneNumber;
    }
    //prints name and phone number
    public void printOut() {
        System.out.println(name);
        System.out.println(phoneNumber);
    }
    
    
}


//this class is for holding arrays of businesses

class businessList {

    private int numberOfBusinesses;
    public businessRecord[] theBusinessList;
    private int searchCount = 0;
    private int notFoundCount = 0;
    
    //Constructor
    businessList(String[] directory) throws IOException {

        try (BufferedReader in = new BufferedReader(
                
                new FileReader(directory[0]))) {
            
            
            String firstLine = in.readLine();
            
            numberOfBusinesses = Integer.parseInt(firstLine);
            
            theBusinessList = new businessRecord[numberOfBusinesses];
            
            for (int i = 0; i < numberOfBusinesses; i++) {
                
                String textIn = in.readLine();
		// makes the business into a record with 2 parts,
		// name and phone number
                String[] businessIn = textIn.split(","); 
		//checks if the line has a name and phone number
		if (businessIn.length != 2) {
		}
		else {
                businessRecord b = new businessRecord(businessIn[0], businessIn[1]);
                ////adds the business into the array
                theBusinessList[i] = b;}
            }
        }
    }

 
    //Merge Sort Method
    public void mergeSort() {
        businessRecord[] workSpace = new businessRecord[numberOfBusinesses];
        recMergeSort(workSpace, 0, numberOfBusinesses - 1);
    }

    //Recursive Merge Sort, called by mergeSort
    private void recMergeSort(businessRecord[] workSpace, int lowerBound, int upperBound) {
        if (lowerBound == upperBound) {
        } else {
            int mid = (lowerBound + upperBound) / 2;
            recMergeSort(workSpace, lowerBound, mid);
            recMergeSort(workSpace, mid + 1, upperBound);
            merge(workSpace, lowerBound, mid + 1, upperBound);
        }
    }

    //merge method, called by recMergeSort
    private void merge(businessRecord[] workSpace, int lowPointer, int highPointer, int upperBound) {
        int j = 0;
        int lowerBound = lowPointer;
        int mid = highPointer - 1;
        int n = upperBound - lowerBound + 1;

        while (lowPointer <= mid && highPointer <= upperBound) {
            if (0 >= (theBusinessList[lowPointer].getName().compareTo(theBusinessList[highPointer].getName()))) {
                workSpace[j++] = theBusinessList[lowPointer++];
            } else {
                workSpace[j++] = theBusinessList[highPointer++];
            }
        }

        while (lowPointer <= mid) {
            workSpace[j++] = theBusinessList[lowPointer++];
        }

        while (highPointer <= upperBound) {
            workSpace[j++] = theBusinessList[highPointer++];
        }

        for (j = 0; j < n; j++) {
            theBusinessList[lowerBound + j] = workSpace[j];
        }
    }
    
    
    // searched for business name, returns 
    // phone number if found, NOT FOUND if not found.
    

    public String find(String searchName) {
        int lowerBound = 0;
        int upperBound = numberOfBusinesses - 1;
        int curIn;

        while (true) {
            curIn = (lowerBound + upperBound) / 2;
            if (theBusinessList[curIn].getName().equals(searchName)) {
                return theBusinessList[curIn].getPhoneNumber();
            } else if (lowerBound > upperBound) {
                return "NOT FOUND";
            } else {
                if (theBusinessList[curIn].getName().compareTo(searchName) < 0) {
                    lowerBound = curIn + 1;
                } else {
                    upperBound = curIn - 1;
                }
            }
        }
    }
    

    //interactive: allows user to enter business name to be searched
    //until blank line. Then, prints total queries and total not found.
    
    public void search() {
        
        Scanner keyboard = new Scanner(System.in);
       

        while(true) {
        String query = keyboard.nextLine();
        if (query.equals("")) {
	    System.out.println(searchCount + " total queries, " + notFoundCount + " not found.");
            break;
        }
        System.out.println(find(query));
	searchCount = searchCount + 1;
	if (find(query).equals("NOT FOUND")) {
		notFoundCount = notFoundCount + 1;
	    }
        }
    }

}

//this class has the main

public class BusinessSearch {

    public static void main(String[] args) throws IOException {
	//checks to make sure user entered an argument
	if (args.length ==  0) {
		System.out.println("Usage: BusinessSearch businessDB");
	    }
	else {
	    // creates a list from the directory entered
	    businessList theList = new businessList(args);
	    //sorts the list
	    theList.mergeSort();
	    //allows user to search list
	    theList.search();
	}

    }
}  
