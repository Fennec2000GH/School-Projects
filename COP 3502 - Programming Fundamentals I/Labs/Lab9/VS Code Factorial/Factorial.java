

public class Factorial {
    //pure recursion 
    public static long pureRecursive(int n){ 
        if(n <= 0)
            throw new IllegalArgumentException("n must be positive!"); 
        return n == 1 ? 1 : n * pureRecursive(n - 1);  
    }
    
    //tail recursion primary function 
    public static long tailRecursive(int n){ return Factorial.tail(n, 1); } 
    
    //helper function for tail recursion 
    private static long tail(int n, int accumulator){
        if(n <= 0) 
            throw new IllegalArgumentException("n must be positive!"); 
        else if(n == 1)
            return accumulator; 
        return tail(n - 1, n * accumulator); 
    }

    //non-recursive method for factorial 
    public static long iterative(int n){
        if(n <= 0) 
            throw new IllegalArgumentException("n must be positive!"); 
        int fact = 1; 
        for(int i = n; i >= 1; --i) 
            fact *= i; 
        return fact; 
    } 

    // public static void main(String[] args){
    //     for(int i = 1; i <= 14; i++)
    //         System.out.println(Factorial.pureRecursive(i) + "\t" + Factorial.tailRecursive(i) + "\t" + Factorial.iterative(i)); 
    // }

}

