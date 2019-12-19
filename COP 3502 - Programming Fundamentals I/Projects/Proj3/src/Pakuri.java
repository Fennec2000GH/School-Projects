import java.util.Comparator; 

public class Pakuri {
    //MEMBER VARIABLES 
    private String species;
    private int attack, defense, speed; 

    //MEMBER FUNCTIONS  
    //CONSTRUCTORS 
    public Pakuri(String species){ 
        this.species = species; 
        this.attack = species.length() * 7 + 9; 
        this.defense = species.length() * 5 + 17; 
        this.speed = species.length() * 6 + 13; 
    }

    //ACCESSORS 
    //gets the species name 
    public String getSpecies(){ return this.species; } 

    //gets attack score 
    public int getAttack(){ return this.attack; } 

    //gets defense score 
    public int getDefense(){ return defense; } 

    //gets speed value 
    public int getSpeed(){ return this.speed; } 

    //MUTATORS 
    //resets attack score to new value 
    public void setAttack(int newAttack){ this.attack = newAttack; } 

    //level up attack, defense, and speed by factors of 2, 4, and 3, respectively 
    public void evolve(){
        this.attack = this.attack * 2; 
        this.defense = this.defense * 4; 
        this.speed = this.speed * 3;  
    } 
} 

class PakuriComparator implements Comparator<Pakuri> {
    @Override
    public int compare(Pakuri p1, Pakuri p2){ return p1.getSpecies().compareTo(p2.getSpecies()); }
}