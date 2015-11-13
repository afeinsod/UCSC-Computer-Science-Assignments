public class option {
    /*
    -has a room called tag
    -has a string with the text of the option
    -has a print method
    */
    public String optionTag;
    public String text;
    public char letter;
    
    option(char a) {
        letter = a;
    }
    
    public void setOptionTag(String r) {
        optionTag = r;
    }
    
}