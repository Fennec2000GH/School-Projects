import java.util.ArrayList;
import java.util.AbstractMap;
import java.util.Map;
import java.util.stream.IntStream;
import java.util.Scanner;
import java.util.TreeMap;

public class Blackjack {
    //MEMBER VARIABLES
    public final static TreeMap<Integer, String> faceValue = new TreeMap<>(Map.ofEntries(
            new AbstractMap.SimpleImmutableEntry<>(1, "ACE"),
            new AbstractMap.SimpleImmutableEntry<>(2, "2"),
            new AbstractMap.SimpleImmutableEntry<>(3, "3"),
            new AbstractMap.SimpleImmutableEntry<>(4, "4"),
            new AbstractMap.SimpleImmutableEntry<>(5, "5"),
            new AbstractMap.SimpleImmutableEntry<>(6, "6"),
            new AbstractMap.SimpleImmutableEntry<>(7, "7"),
            new AbstractMap.SimpleImmutableEntry<>(8, "8"),
            new AbstractMap.SimpleImmutableEntry<>(9, "9"),
            new AbstractMap.SimpleImmutableEntry<>(10, "10"),
            new AbstractMap.SimpleImmutableEntry<>(11, "JACK"),
            new AbstractMap.SimpleImmutableEntry<>(12, "QUEEN"),
            new AbstractMap.SimpleImmutableEntry<>(13, "KING")
    ));

    private static ArrayList<Integer> playerDeck = new ArrayList<>();
    private static int[] scores = new int[] {0, 0, 0};
    private static int gameCounter = 1;

    //MEMBER FUNCTIONS
    public static void printMenu(){
        System.out.println("1. Get another card");
        System.out.println("2. Hold hand");
        System.out.println("3. Print statistics");
        System.out.println("4. Exit\n");
    }
    public static int faceValueToScore(int fv){
        if(fv >= 10)
            return 10;
        return fv;
    }
    public static int getPlayerHand(){
        return Blackjack.playerDeck.stream().reduce(0, Integer::sum);
    }
    public static int getPlayerScore(){ return Blackjack.scores[0]; }
    public static int getDealerScore(){
        return Blackjack.scores[1];
    }
    public static int getTies(){
        return Blackjack.scores[2];
    }
    public static int getTotalPlays(){
        return IntStream.of(Blackjack.scores).sum();
    }
    public static double getPlayerWinPercentage(){
        return (double) Math.round((double) Blackjack.getPlayerScore() / Blackjack.getTotalPlays() * 1000) / 10;
    }
    public static void reset(){
        Blackjack.playerDeck.clear();
    }

    public static void main(String[] args) {
        P1Random rng = new P1Random();
        Scanner scanner = new Scanner(System.in);
        boolean newGame = true;
        boolean afterStats = false;
        int menuChoice = -1;
        int playerCard = 0;

        while(menuChoice != 4){
            if(newGame) {
                System.out.println("START GAME #" + Blackjack.gameCounter + "\n");
                newGame = false;
            }
            if(!afterStats){
                playerCard = rng.nextInt(13) + 1;
                Blackjack.playerDeck.add(Blackjack.faceValueToScore(playerCard));
                System.out.println("Your card is a " + Blackjack.faceValue.get(playerCard) + "!");
                System.out.println("Your hand is: " + Blackjack.getPlayerHand() + "\n");
                if (Blackjack.getPlayerHand() == 21) {
                    System.out.println("BLACKJACK! You win!\n");
                    ++Blackjack.scores[0];
                    ++Blackjack.gameCounter;
                    newGame = true;
                    Blackjack.reset();
                    continue;
                } else if(Blackjack.getPlayerHand() > 21) {
                    System.out.println("You exceeded 21! You lose.\n");
                    ++Blackjack.scores[1];
                    ++Blackjack.gameCounter;
                    newGame = true;
                    Blackjack.reset();
                    continue;
                }
            }
            afterStats = false;
            Blackjack.printMenu();
            System.out.print("Choose an option: ");
            menuChoice = scanner.nextInt();
            System.out.println("");
            while(menuChoice < 1 || menuChoice > 4){
                System.out.println("Invalid input!");
                System.out.println("Please enter an integer value between 1 and 4.\n");
                Blackjack.printMenu();
                System.out.print("Choose an option: ");
                menuChoice = scanner.nextInt();
            }
            switch(menuChoice){
                case 2: {
                    int dealersHand = rng.nextInt(11) + 16;
                    System.out.println("Dealer's hand: " + dealersHand);
                    System.out.println("Your hand is: " + Blackjack.getPlayerHand() + "\n");
                    if(Blackjack.getPlayerHand() > dealersHand || dealersHand > 21) {
                        System.out.println("You win!\n");
                        ++Blackjack.scores[0];
                    } else if(Blackjack.getPlayerHand() < dealersHand) {
                        System.out.println("Dealer wins!\n");
                        ++Blackjack.scores[1];
                    } else {
                        System.out.println("It's a tie! No one wins!\n");
                        ++Blackjack.scores[2];
                    }
                    ++Blackjack.gameCounter;
                    newGame = true;
                    Blackjack.reset();
                    break;
                }
                case 3: {
                    System.out.println("Number of Player wins: " + Blackjack.getPlayerScore());
                    System.out.println("Number of Dealer wins: " + Blackjack.getDealerScore());
                    System.out.println("Number of tie games: " + Blackjack.getTies());
                    System.out.println("Total # of games played is: " + Blackjack.getTotalPlays());
                    System.out.println("Percentage of Player wins: " + Blackjack.getPlayerWinPercentage() + "%\n");
                    afterStats = true;
                }
            }
        }
    }
}

