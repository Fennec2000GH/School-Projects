import java.util.Arrays; 
import java.util.ArrayList; 
import java.util.stream.Collectors;

public class Cowsay {
	//MEMBER FUNCTIONS
	//prints out a list of all available cows and dragons from HeiferGenerator 
    private static void listCows(Cow[] cows){
		ArrayList<String> regularArr = (ArrayList<String>)Arrays.stream(HeiferGenerator.getCows()).map(n -> n.getName()).collect(Collectors.toList()); 
		System.out.print("Regular cows available: "); 
		for(String cow : regularArr) 
			System.out.print(cow + " "); 
		System.out.println(""); 
		ArrayList<String> fileArr = (ArrayList<String>)Arrays.stream(HeiferGenerator.getFileCows()).map(n -> n.getName()).collect(Collectors.toList()); 
		System.out.print("File cows available: "); 
		for(String fileCow : fileArr) 
			System.out.print(fileCow + " "); 
		System.out.println("\n"); 
	}
	//finds Cow object in a given array of Cow objects by name matching 
	private static Cow findCow(String name, Cow[] cows){
		for(Cow cow : cows) 
			if(cow.getName().equals(name)) 
				return cow; 
		return null; 
	} 

    public static void main(String[] args) {
		Cow[] cowArr = HeiferGenerator.getCows(); 
		Cow[] fileCowArr = HeiferGenerator.getFileCows(); 
		switch(args[0]){		
			//lists available cows 
			case "-l" : {
				Cowsay.listCows(cowArr); 
				break; 
			}

			//prints out message with specified Cow object 
			case "-n" : {
				Cow specificCow = Cowsay.findCow(args[1], cowArr); 
				if(specificCow == null) 
					System.out.println("Could not find " + args[1] + " cow!\n"); 
				else {
					System.out.println(""); 
					for(int index = 2; index <= args.length - 1; index++)
						System.out.print(args[index] + " "); 
					System.out.println(""); 
					System.out.println(specificCow.getImage()); 
					if(specificCow.getName().equals("dragon")) 
						System.out.println("This dragon can breathe fire. \n"); 
					else if(specificCow.getName().equals("ice-dragon")) 
						System.out.println("This dragon cannot breathe fire. \n"); 
				} 
				break; 
			} case "-f" : {
				Cow specificCow = Cowsay.findCow(args[1], fileCowArr); 
				if(specificCow == null) 
					System.out.println("Could not find " + args[1] + " cow!\n"); 
				else {
					System.out.println(""); 
					for(int index = 2; index <= args.length - 1; index++)
						System.out.print(args[index] + " "); 
					System.out.println(""); 
					System.out.println(specificCow.getImage());  
				} 
				break; 
			}
			default : {
				Cow defaultCow = cowArr[0]; 
				System.out.println(""); 
				for(int index = 0; index <= args.length - 1; index++)
						System.out.print(args[index] + " "); 
					System.out.println(""); 
					System.out.println(defaultCow.getImage()); 
			}
		}
    }
} 


