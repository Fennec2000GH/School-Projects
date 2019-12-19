
public class Cow {
    //MEMBER VARIABLES 
    /*the word "cow" was removed from previously named 
    "name" and "image" since this is no longer just 
    about cows */ 
    private String name; 
    private String image; 

    //MEMBER FUNCTIONS
    public String getName(){return this.name;} //getter for name 
    public String getImage(){return this.image;} //getter for image 
    public void setImage(String _image){this.image = _image;} //sets a new image for this 

    //CONSTRUCTORS 
    public Cow(String name){this.name = name;} 
} 
