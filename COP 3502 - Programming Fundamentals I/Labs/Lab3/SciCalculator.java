import java.util.stream.DoubleStream; 
import java.util.Scanner; 
import java.util.Vector; 

public class SciCalculator {
    public static void printMenu(){
        System.out.println("Calculator Menu"); 
            System.out.println("---------------"); 
            System.out.println("0. Exit Program"); 
            System.out.println("1. Addition"); 
            System.out.println("2. Subtraction"); 
            System.out.println("3. Multiplication"); 
            System.out.println("4. Division"); 
            System.out.println("5. Exponentiation"); 
            System.out.println("6. Logarithm"); 
            System.out.println("7. Display Average\n"); 
        }
    
    public static String truncate(double num){
        String str = String.valueOf((double)Math.round(num * 100) / 100); 
        // int index = str.indexOf('.'); 
        // if(index == -1 || index + 3 > str.length())
        //     return str; 
        // return str.substring(0, index + 3); 
        return str; 
    } 

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in); 
        Vector<Double> history = new Vector<>();
        boolean skipPrintMenu = false; 
        boolean displayInitialValue = true; 
        double currentResult = 0; 
        int menuChoice = 0; 
        double firstDouble = 0, secondDouble = 0; 
        do {
            menuChoice = scanner.nextInt(); 
            // menuChoice = scanner.nextInt();  
            // scanner.nextLine(); 
            if(menuChoice < 0 || menuChoice > 7){
                if(displayInitialValue) 
                    System.out.println("Current Result: 0.0\n"); 
                SciCalculator.printMenu(); 
                System.out.println("Enter Menu Selection: "); 
                System.out.println("Error: Invalid selection!\n"); 
                skipPrintMenu = true; 
                displayInitialValue = false; 
                continue; 
            } 

            if(menuChoice == 0){
                if(displayInitialValue)
                    System.out.println("Current Result: 0.0\n");  
                if(!skipPrintMenu)
                    SciCalculator.printMenu(); 
                System.out.println("Enter Menu Selection: "); 
                System.out.println("Thanks for using this calculator. Goodbye!"); 
                break;
            } 
            
            if(menuChoice != 7){
                firstDouble = scanner.nextDouble();
                secondDouble = scanner.nextDouble(); 
            } 

            if(displayInitialValue){ 
                System.out.println("Current Result: 0.0\n");  
                displayInitialValue = false; 
            } 

            if(!skipPrintMenu)
                SciCalculator.printMenu(); 
            skipPrintMenu = false; 

            System.out.print("Enter Menu Selection: ");     

            if(menuChoice != 7){
                System.out.print("Enter first operand: "); 
                System.out.print("Enter second operand: ");  
                System.out.println(""); 
            }
            
            switch(menuChoice){
                case 1: {currentResult = firstDouble + secondDouble; System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;} 
                case 2: {currentResult = firstDouble - secondDouble; System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;} 
                case 3: {currentResult = firstDouble * secondDouble; System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;}
                case 4: {currentResult = firstDouble / secondDouble; System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;}
                case 5: {currentResult = Math.pow(firstDouble, secondDouble); System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;} 
                case 6: {currentResult = Math.log(secondDouble) / Math.log(firstDouble); System.out.println("Current Result: " + currentResult + "\n"); history.addElement(currentResult); break;}
                case 7: {
                    skipPrintMenu = true;  
                    if(history.isEmpty()){
                        System.out.println("\nError: No calculations yet to average!\n");  
                    } else { 
                        DoubleStream.Builder b = DoubleStream.builder(); 
                        for(double element : history) 
                            b.add(element); 
                        double sumResult = b.build().sum();
                        double numResult = history.size(); 
                        double avgResult = sumResult / numResult; 
                        System.out.println("Sum of calculations: " + SciCalculator.truncate(sumResult)); 
                        System.out.println("Number of calculations: " + (int)numResult); 
                        System.out.println("Average of calculations: " + SciCalculator.truncate(avgResult));
                        System.out.println(""); 
                        history.addElement(avgResult); 
                    } 
                }
            } 
        } while(menuChoice != 0); 

    }
}



