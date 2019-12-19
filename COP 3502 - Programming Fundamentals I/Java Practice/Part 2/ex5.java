//ex5
import java.util.Scanner;

public class ex5{
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);

        // input it
        System.out.print("Enter a message: ");
        String msg = keyboard.nextLine();

        // reverse it
        String rev = "";
        for(int i = msg.length() - 1; i >= 0; i--)
            rev += msg.substring(i, i + 1);

        // camel-case it
        String lower = rev.toLowerCase();
        String[] words = lower.split(" ");
        String result = "";
        for(String w : words)
            result += w.substring(0, 1).toUpperCase() + w.substring(1);

        // display it
        System.out.println(result);

    }

}
