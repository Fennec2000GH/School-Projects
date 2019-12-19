import java.io.File; 
import java.io.FileReader; 
import java.io.BufferedReader; 
import java.io.IOException; 

public class FileCow extends Cow {

    //MEMBER FUNCTIONS 
    //CONSTRUCTORS 
    public FileCow(String name, String filename) {
        super(name); 
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename)); 
            String line, currentImage = ""; 
            while((line = br.readLine()) != null) 
                currentImage = currentImage.concat(line); 
            br.close(); 
            super.setImage(currentImage); 
        } catch (IOException e) {
            throw new RuntimeException("MOOOOO!!!!!!"); 
        } 
    } 

    //MUTATORS 
    //not allowed to reset cow image for FileCow objects 
    public void setImage(){ throw new RuntimeException("Cannot reset FileCow Image"); } 



}