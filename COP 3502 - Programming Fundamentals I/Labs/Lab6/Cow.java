
public class Cow {
    //MEMBER VARIABLES 
    private String cowName; 
    private String cowImage;

    //MEMBER FUNCTIONS
    public String getName(){return this.cowName;} //getter for cowName 
    public String getImage(){return this.cowImage;} //getter for cowImage 
    public void setImage(String _image){this.cowImage = _image;} //sets a new image for this 
    public Cow(String name){this.cowName = name;} //constructor 
}