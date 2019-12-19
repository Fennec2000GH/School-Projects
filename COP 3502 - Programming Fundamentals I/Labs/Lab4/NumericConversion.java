import java.util.AbstractMap; 
import java.util.Map; 
import java.util.Scanner; 

public class NumericConversion {
    //MEMBER VARIABLES 
    public static final Map<Character, Integer> hexToDec = Map.ofEntries(
        new AbstractMap.SimpleImmutableEntry<>('0', 0), 
        new AbstractMap.SimpleImmutableEntry<>('1', 1), 
        new AbstractMap.SimpleImmutableEntry<>('2', 2), 
        new AbstractMap.SimpleImmutableEntry<>('3', 3), 
        new AbstractMap.SimpleImmutableEntry<>('4', 4), 
        new AbstractMap.SimpleImmutableEntry<>('5', 5), 
        new AbstractMap.SimpleImmutableEntry<>('6', 6), 
        new AbstractMap.SimpleImmutableEntry<>('7', 7), 
        new AbstractMap.SimpleImmutableEntry<>('8', 8), 
        new AbstractMap.SimpleImmutableEntry<>('9', 9), 
        new AbstractMap.SimpleImmutableEntry<>('A', 10), 
        new AbstractMap.SimpleImmutableEntry<>('B', 11), 
        new AbstractMap.SimpleImmutableEntry<>('C', 12), 
        new AbstractMap.SimpleImmutableEntry<>('D', 13), 
        new AbstractMap.SimpleImmutableEntry<>('E', 14),
        new AbstractMap.SimpleImmutableEntry<>('F', 15) 
    );

    //MEMBER FUNCTIONS 
    //converts hexadecimal to decimal equivalent 
    public static long hexStringDecode(String hex){
        long decimal = 0; 
        String temp = hex; 
        if(temp.substring(0, 2).equals("0x") || temp.substring(0, 2).equals("0b"))
            temp = temp.substring(2); 
        temp = NumericConversion.reverseStr(temp); 
        for(int i = 0; i <= temp.length() - 1; i++)
            decimal += Double.valueOf(NumericConversion.hexToDec.get(Character.toUpperCase(temp.charAt(i))) * Math.pow(16, i)).longValue(); 
         return decimal;    
    }
    
    //converts single hexadecimal character to decimal equivalent 
    public static short hexCharDecode(char digit){
        return NumericConversion.hexToDec.get(Character.toUpperCase(digit)).shortValue(); 
    } 

    //converts binary number to decimal equivalent 
    public static short binaryStringDecode(String binary){
        int decimal = 0; 
        String temp = binary; 
        if(binary.substring(0, 2).equals("0x") || binary.substring(0, 2).equals("0b"))
            temp = temp.substring(2); 
        temp = NumericConversion.reverseStr(temp); 
        for(int i = 0; i <= temp.length() - 1; i++) 
            decimal += Integer.parseInt(String.valueOf(temp.charAt(i))) * (int)Math.pow(2, i); 
        return Integer.valueOf(decimal).shortValue(); 
    }

    //converts binary number to hexadecimal equivalent 
    public static String binaryToHex (String binary){
        short decimal = NumericConversion.binaryStringDecode(binary); 
        return Integer.toString(Integer.valueOf(Short.valueOf(decimal).intValue()), 16).toUpperCase(); 
    } 

    //prints the menu 
    public static void printMenu(){
        System.out.println("Decoding Menu"); 
        System.out.println("-------------"); 
        System.out.println("1. Decode hexadecimal"); 
        System.out.println("2. Decode binary"); 
        System.out.println("3. Convert binary to hexadecimal"); 
        System.out.println("4. Quit\n"); 
    }

    //reverses order of characters in string 
    public static String reverseStr(String str){
        String temp = ""; 
        for(int i = str.length() - 1; i >= 0; i--)
            temp += str.charAt(i); 
        return temp; 
    } 

    //main method 
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in); 
        int menuChoice = 0; //must be 1-4 inclusive 
        String number = ""; //number to manipulate or convert 
        String result = ""; //result of each calculation 
        do{
            NumericConversion.printMenu(); 
            System.out.print("Please enter an option: "); 
            menuChoice = scanner.nextInt(); 
            if(menuChoice == 4){ 
                System.out.println("Goodbye!"); 
                return; 
            }
            System.out.print("Please enter the numeric string to convert: "); 
            number = scanner.next(); 

            //performs action specific to menuChoice 
            switch(menuChoice){
                case 1: {result = String.valueOf(NumericConversion.hexStringDecode(number)); break;}
                case 2: {result = String.valueOf(NumericConversion.binaryStringDecode(number)); break;}
                case 3: {result = NumericConversion.binaryToHex(number);}
            }
            System.out.println("Result: " + result + "\n"); 
        }while(menuChoice != 4); 
    }


}




