public class Dragon extends Cow {
    //MEMBER FUNCTIONS 
    //tells whether the dragon is fire-breathing or not; default is true 
	public boolean canBreatheFire(){
        return true; 
    } 

	//CONSTRUCTORS 
	public Dragon(String name, String image){ 
        super(name); 
        super.setImage(image); 
	} 

} 