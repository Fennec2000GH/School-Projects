import java.util.Scanner;

public class Hello {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        String firstLine = scanner.next();
        String secondLine = scanner.next();
        String thirdLine = scanner.next(); 
        System.out.print("Hello. What is your name? ");
        System.out.print("It's nice to meet you, " + firstLine + ". How old are you? ");
        System.out.println("I see that you are still quite young at only " + secondLine + ".");
        System.out.print("Where do you live? ");
        System.out.print("Wow! I've always wanted to go to " + thirdLine + ". Thanks for chatting with me. Bye!");
    }
}

