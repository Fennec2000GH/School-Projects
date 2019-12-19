
import java.util.Scanner; 

public class Calculator{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        System.out.print("Enter first operand: "); 
        double op1 = scanner.nextDouble(); 
        System.out.print("Enter second operand: "); 
        double op2 = scanner.nextDouble(); 
        System.out.println("Calculator Menu"); 
        System.out.println("---------------"); 
        System.out.println("1. Addition"); 
        System.out.println("2. Subtraction"); 
        System.out.println("3. Multiplication"); 
        System.out.println("4. Division"); 
        System.out.print("Which operation do you want to perform? "); 
        int selection = scanner.nextInt(); 
        double answer; 
        switch(selection){
            case 1: {answer = op1 + op2; break;}
            case 2: {answer = op1 - op2; break;} 
            case 3: {answer = op1 * op2; break;} 
            case 4: {answer = op1 / op2; break;}
            default: {System.out.println("Error: Invalid selection! Terminating program."); return;} 
        }
        System.out.println("The result of the operation is " + answer + ". Goodbye!"); 

    }
}



