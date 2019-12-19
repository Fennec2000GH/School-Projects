public class IceDragon extends Dragon { 
    //MEMBER FUNCTIONS 
    //tells whether the dragon is fire-breathing or not; ice-dragon is false 
    @Override 
    public boolean canBreatheFire(){
        return false; 
    } 
    
    //CONSTRUCTORS 
    public IceDragon(String name, String image){
        super(name, image); 
    }
} 
