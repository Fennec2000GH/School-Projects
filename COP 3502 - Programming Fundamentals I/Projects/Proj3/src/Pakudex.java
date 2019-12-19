import java.util.Arrays; 
import java.util.Collections; 
import java.util.stream.Collectors; 
import java.util.List; 
import java.util.Objects; 
import java.util.stream.Stream; 

public final class Pakudex {
    //MEMBER VARIABLES 
    private Pakuri[] pakudex; 

    //MEMBER FUNCTIONS 
    //CONSTRUCTORS 
    //default constructor 
    public Pakudex(){ this.pakudex = new Pakuri[20]; } 

    //constructor that accepts initial capacity for pakudex 
    public Pakudex(int capacity){ this.pakudex = new Pakuri[capacity]; } 

    //ACCESSORS 
    //current count of Pakuri in pakudex 
    public int getSize(){
        return (int)Arrays
            .stream(this.pakudex)
            .filter(Objects::nonNull)
            .count(); 
    } 

    //maximum capacity pakudex has to store Pakuri 
    public int getCapacity(){ return this.pakudex.length; } 

    //get string array of species name of Pakuri in same order 
    public String[] getSpeciesArray(){
        if(this.getSize() == 0) 
            return null; 
        String[] output = new String[this.getSize()]; 
        Arrays
            .stream(this.pakudex)
            .filter(Objects::nonNull)
            .map(n -> n.getSpecies())
            .collect(Collectors.toList()) 
            .toArray(output); 
        return output; 
    } 

    //3-element array containing attack, defense, and speed statistics for a specific Pakuri from given species name 
    public int[] getStats(String species){
        if(species == null) 
            return null; 
        if(this.pakudex == null) 
            return null; 
        if(!Arrays.asList(this.getSpeciesArray()).contains(species))
            return null; 
        int[] output = new int[3]; 
        Pakuri temp = null;           
        for(Pakuri p : Arrays.stream(this.pakudex).filter(Objects::nonNull).collect(Collectors.toList())) 
            if(p.getSpecies().equals(species)){
                temp = p; 
                break; 
            } 
        if(temp == null) 
            return null; 
        output[0] = temp.getAttack(); 
        output[1] = temp.getDefense(); 
        output[2] = temp.getSpeed(); 
        return output; 
    } 

    //MUTATORS 
    //sorts pakudex in lexicographical order by species name 
    public void sortPakuri(){ 
        if(this.pakudex == null) 
            return; 
        List<Pakuri> pakudexList = Arrays.stream(this.pakudex).filter(Objects::nonNull).collect(Collectors.toList()); 
        Collections.sort(pakudexList, new PakuriComparator()); 
        pakudexList.toArray(this.pakudex); 
    } 

    //add species to the Pakudex, and returns true for success and false for failure 
    public boolean addPakuri(String species){
        if(species == null) 
            return false; 
        int index = Arrays.asList(this.pakudex).indexOf(null); 
        if(index == -1 || Arrays.asList(this.pakudex).contains(species)) //no null elements left means pakudex is full 
            return false; 
        this.pakudex[index] = new Pakuri(species);  
        return true; 
    } 

    //evolve a species within the Pakudex, and returns true for success and false for failure 
    public boolean evolveSpecies(String species){
        if(species == null) 
            return false; 
        if(this.pakudex == null) 
            return false; 
        if(!Arrays.asList(this.getSpeciesArray()).contains(species))
            return false; 
        int index = 0; 
        for(int i = 0; i <= Arrays.stream(this.pakudex).filter(Objects::nonNull).collect(Collectors.toList()).size() - 1; i++) 
            if(this.pakudex[i].getSpecies().equals(species)){
                index = i; 
                break; 
            }
        this.pakudex[index].evolve(); 
        return true; 
    } 

    
}

