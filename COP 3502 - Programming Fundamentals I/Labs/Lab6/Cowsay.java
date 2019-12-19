import java.util.Arrays; 
import java.util.ArrayList; 
import java.util.stream.Collectors;

public class Cowsay {
	//MEMBER FUNCTIONS
	//prints out a list of all available cows from HeiferGenerator 
    private static void listCows(Cow[] cows){
		ArrayList<String> arr = (ArrayList<String>)Arrays.stream(HeiferGenerator.getCows()).map(n -> n.getName()).collect(Collectors.toList()); 
		System.out.print("Cows available: "); 
		for(String cow : arr) 
			System.out.print(cow + " "); 
		System.out.println(""); 
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
		switch(args[0]){		
			//lists available cows 
			case "-l" : {
				Cowsay.listCows(cowArr); 
				System.out.println(""); 
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
