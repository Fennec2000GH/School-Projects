import java.util.Arrays; 
import java.util.Scanner; 

public class PakuriProgram {

    //MEMBER FUNCTIONS 
    //ACCESSORS 
    public static void printMenu(){
        System.out.println("Pakudex Main Menu"); 
        System.out.println("-----------------"); 
        System.out.println("1. List Pakuri"); 
        System.out.println("2. Show Pakuri"); 
        System.out.println("3. Add Pakuri"); 
        System.out.println("4. Evolve Pakuri"); 
        System.out.println("5. Sort Pakuri"); 
        System.out.println("6. Exit"); 
    }

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in); 
        int menuChoice = 0; 
        int capacity = 0; //maximum number of pakuri creatures able to hold 
        String speciesInput; //temporary placeholder for user-given species names 
        Pakudex mainDex; 

        System.out.println("Welcome to Pakudex: Tracker Extraordinaire!"); 
        System.out.print("Enter max capacity of the Pakudex: ");  
        String testCapacity = scanner.next(); //tests for correct data type (int) 
        while(!testCapacity.chars().mapToObj(n -> (char)n).allMatch(Character::isDigit)){
            System.out.println("Please enter a valid size. "); 
            System.out.print("Enter max capacity of the Pakudex: ");  
            testCapacity = scanner.next(); 
        } 
        capacity = Integer.valueOf(testCapacity); 
        mainDex = new Pakudex(capacity); 
        System.out.println("The Pakudex can hold " + capacity + " species of Pakuri.\n"); 
        while(menuChoice != 6){
            PakuriProgram.printMenu(); 
            System.out.print("\nWhat would you like to do? "); 
            String testMenuChoice = scanner.next(); 
            while(!testMenuChoice.chars().mapToObj(n -> (char)n).allMatch(Character::isDigit)){
                System.out.println("Unrecognized menu selection!\n"); 
                PakuriProgram.printMenu(); 
                System.out.print("\nWhat would you like to do? "); 
                testMenuChoice = scanner.next(); 
            }
            menuChoice = Integer.valueOf(testMenuChoice); 
            switch(menuChoice){
                //prints out each existing Pakuri by species name 
                case 1 : { 
                    if(mainDex.getSize() == 0) 
                        System.out.println("No Pakuri in Pakudex yet!\n"); 
                    else {
                        String[] arr = mainDex.getSpeciesArray(); 
                        System.out.println("Pakuri In Pakudex: "); 
                        int num = 1; 
                        for(String species : mainDex.getSpeciesArray()){
                            System.out.println(num + ". " + species); 
                            ++num; 
                        } 
                        System.out.println(""); 
                    } 
                    break; 
                } 
                //displays information about a chosen species of Pakuri 
                case 2 : {
                    System.out.print("Enter the name of the species to display: "); 
                    speciesInput = scanner.next(); 
                    if(mainDex.getSpeciesArray() == null) 
                        System.out.println("Error: No such Pakuri!\n");          
                    else if(!Arrays.asList(mainDex.getSpeciesArray()).contains(speciesInput)) 
                        System.out.println("Error: No such Pakuri!\n");                 
                    else {     
                        int[] statsArray = mainDex.getStats(speciesInput); 
                        System.out.println("\nSpecies: " + speciesInput); 
                        System.out.println("Attack: " + statsArray[0]); 
                        System.out.println("Defense: " + statsArray[1]); 
                        System.out.println("Speed: " + statsArray[2]);  
                        System.out.println(""); 
                    }    
                    break; 
                }  
                //adding new Pakuri to mainDex 
                case 3 : {
                    if(mainDex.getSize() >= mainDex.getCapacity()){ 
                        System.out.println("Error: Pakudex is full!\n"); 
                        scanner.next(); 
                        break; 
                    }
                    System.out.print("Enter the name of the species to add: "); 
                    speciesInput = scanner.next(); 
                    if(mainDex.getSpeciesArray() == null){
                        mainDex.addPakuri(speciesInput); 
                        System.out.println("Pakuri species " + speciesInput + " successfully added!\n"); 
                    } else {
                        if(Arrays.asList(mainDex.getSpeciesArray()).contains(speciesInput)) 
                            System.out.println("Error: Pakudex already contains this species!\n"); 
                        else { 
                            mainDex.addPakuri(speciesInput); 
                            System.out.println("Pakuri species " + speciesInput + " successfully added!\n"); 
                        }
                    }
                    break; 
                } 
                //evolves a specific species in mainDex 
                case 4 : {
                    System.out.print("Enter the name of the species to evolve: "); 
                    speciesInput = scanner.next(); 
                    if(mainDex.getSpeciesArray() == null) 
                         System.out.println("Error: No such Pakuri!\n"); 
                    else if(!Arrays.asList(mainDex.getSpeciesArray()).contains(speciesInput))
                        System.out.println("Error: No such Pakuri!\n"); 
                    else {
                        mainDex.evolveSpecies(speciesInput); 
                        System.out.println(speciesInput + " has evolved!\n"); 
                    }
                    break; 
                } 
                //sorts mainDex in lexicogrphical ascending order 
                case 5 : {
                    mainDex.sortPakuri(); 
                    System.out.println("Pakuri have been sorted!\n"); 
                    break; 
                } 
                case 6 : {
                    scanner.close(); 
                    System.out.println("Thanks for using Pakudex! Bye!"); 
                    return; 
                } 
                default : {
                    System.out.println("Unrecognized menu selection!\n"); 
                }
            }
        }
    }
}
