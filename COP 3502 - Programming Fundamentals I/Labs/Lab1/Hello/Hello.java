import java.util.Scanner;

public class Hello {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Hello. What is your name? ");
        String firstLine = scanner.nextLine();
        System.out.print("It's nice to meet you, " + firstLine + ". How old are you? ");
        String secondLine = scanner.nextLine();
        System.out.println("I see that you are still quite young at only " + secondLine + ". ");
        System.out.print("Where do you live? ");
        String thirdLine = scanner.nextLine();
        System.out.println("Wow! I've always wanted to go to " + thirdLine + ". Thanks for chatting with me. Bye! ");
    }
}

