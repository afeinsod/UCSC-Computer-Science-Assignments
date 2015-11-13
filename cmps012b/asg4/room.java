package cyoa;

/**
 *
 * @author Owner
 */
public class room {
    /*
    -has a String description, can be added to or printed out
    -has an unordered array of options, can be added to and printed out (in order of first added, first printed)
    -has a play method that presents the options and then scans for user input using switch, swtich includes r, q, y, z, etc as well

    */
    public String tag;
    public String description;
    public option[] options;
    public int numOptions;
    
    room(String s) {
        numOptions = 0;
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
    
    public void addOption(String s) {
        options[numOptions].text = s;
        numOptions++;
    }
    
    public void updateDestinationTag(String r) {
        options[numOptions - 1].setOptionTag(r);
    }
    
    public void play() {
        System.out.println(description);
        for (int i = 0; i < numOptions; i++) {
            System.out.println(options[i].text);
        }
    }
    
    public void printRoom() {
        System.out.print(tag);
        for (int i = 0; i < numOptions; i ++) {
            System.out.print(options[i].optionTag);
        }
        System.out.println();
    }
}