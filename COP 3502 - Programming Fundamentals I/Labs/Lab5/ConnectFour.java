import java.util.Queue;
import java.util.Scanner;
import java.util.concurrent.LinkedBlockingQueue;
public class ConnectFour{
    //MEMBER VARIABLES 
    private static char[][] board; 
    
    //MEMBER FUNCTIONS 
    //prints the board 
    public static void printBoard(char[][] array){
        for(char[] row : array){ 
            for(char c : row)
                System.out.print(c + " "); 
            System.out.println(""); 
        }
        System.out.println(""); 
    }

    //initializes each element to '-' 
    public static void initializeBoard(char[][] array){
        for(int i = 0; i <= array.length - 1; i++) 
            for(int j = 0; j <= array[0].length - 1; j++)
                array[i][j] = '-'; 
    }

    //drops chip in specified column 
    public static int insertChip(char[][] array, int col, char chipType){
        int rowIndex = -1; 
        for(int i = array.length - 1; i >= 0; i--){ 
            if(array[i][col] == '-'){
                rowIndex = i;  
                array[i][col] = chipType; 
                break; 
            }
        }
        return rowIndex; 
    } 

    //returns true only if token in specified row and col designates a winner (either 4 across or vertical) 
    public static boolean checkIfWinner(char[][] array, int col, int row, char chipType){
        if(row < 0 || row >= array.length || col < 0 || col >= array[0].length || chipType == '-')
            return false;    
        int streak = 0; 

        //calculating number of contiguous chipType elements containing specified coordinate in specific column 
        for(int i = 0; i <= (row >= 3 ? 3 : row); i++) 
            if(array[row - i][col] == chipType)
                ++streak;
        for(int i = 1; i <= (array.length - 1 - row < 4 ? array.length - 1 - row : 4); i++) 
            if(array[row + i][col] == chipType) 
                ++streak; 
        if(streak >= 4)
            return true; 
        
        //column failed; time to check for streak of 4 or more chipType in row horizontally 
        streak = 0; 
        for(int i = 0; i <= (col >= 3 ? 3 : col); i++) 
            if(array[row][col - i] == chipType) 
                ++streak; 
        for(int i = 1; i <= (array[0].length - 1 - col < 4 ? array[0].length - 1 - col : 4); i++) 
            if(array[row][col + i] == chipType)
                ++streak;  
        if(streak >= 4)
            return true; 
        return false; 
    } 

    //detects fully filled board, regardless of game outcome 
    public static boolean filledBoard(char[][] array, char defaultToken){
        for(char[] row : array) 
            for(char c : row)
                if(c == defaultToken)
                    return false; 
        return true; 
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        Queue<Integer> inputs = new LinkedBlockingQueue<>(); //stores inputs 
        while (scanner.hasNextInt())
            inputs.offer(scanner.nextInt());
            
        int height = inputs.poll(), length = inputs.poll(); 
        System.out.print("What would you like the height of the board to be? "); 
        System.out.print("What would you like the length of the board to be? ");         

        //setting the board up 
        ConnectFour.board = new char[height][length]; 
        ConnectFour.initializeBoard(ConnectFour.board); 
        ConnectFour.printBoard(ConnectFour.board); 
        System.out.println("Player 1: x"); 
        System.out.println("Player 2: o"); 
        
        int playerTurn = 1; //alternates between 1 and 2 for player turn 
        int column = -1; 
        char[] tokens = {'x', 'o'}; 

        //interaction with players 
        while(true){
            System.out.print("Player " + playerTurn + ": Which column would you like to choose? "); 
            column = inputs.poll(); 
            int row = ConnectFour.insertChip(ConnectFour.board, column,tokens[playerTurn - 1]); //row index of token 
            ConnectFour.printBoard(ConnectFour.board); 
            
            if(ConnectFour.checkIfWinner(ConnectFour.board, column, row, tokens[playerTurn - 1])){
                System.out.println("Player " + playerTurn + " won the game!\n"); 
                break; 
            } 
            if(ConnectFour.filledBoard(ConnectFour.board, '-')){
                System.out.println("Draw. Nobody wins."); 
                break; 
            }
            playerTurn = playerTurn == 1 ? 2 : 1; 
        }
        scanner.close(); 
    }

}




