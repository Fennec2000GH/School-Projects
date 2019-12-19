

public class Analyzer {
    //MEMBER METHODS 
    //finds element in linear time and returns index or -1 if not found 
    public static int linearSearch(String[] dataSet, String element){
        for(int i = 0; i <= dataSet.length - 1; i++) 
            if(dataSet[i].equals(element)) 
                return i; 
        return -1; 
    } 

    //finds element in log n time and returns index or -1 if not found 
    public static int binarySearch(String[] dataSet, String element){
        int start = 0, end = dataSet.length, mid; 
        while(start < end){
            mid = (start + end) / 2; 
            // System.out.println(mid); 
            if(dataSet[mid].equals(element)) 
                return mid;  
            else if(dataSet[mid].compareTo(element) > 0) 
                end = mid;
            else if(dataSet[mid].compareTo(element) < 0)
                start = mid + 1; 
        } 
        return -1; 
    }   
    
    //main method 
    public static void main(String[] args){ 
            long time1, time2, time3; 
            time1 = System.nanoTime(); 
            int not_here_index1 = Analyzer.linearSearch(StringData.getData(), "not_here"); 
            time2 = System.nanoTime(); 
            int not_here_index2 = Analyzer.binarySearch(StringData.getData(), "not_here"); 
            time3 = System.nanoTime(); 
            System.out.println("Index of 'not_here' is " + not_here_index1 + " (linear search) and " + not_here_index2 + " (binary search)"); 
            System.out.println("Linear search took " + (time2 - time1) + " ns, and binary search took " + (time3 - time2) + " ns. \n"); 

            time1 = System.nanoTime(); 
            int mzzzz_index1 = Analyzer.linearSearch(StringData.getData(), "mzzzz"); 
            time2 = System.nanoTime(); 
            int mzzzz_index2 = Analyzer.binarySearch(StringData.getData(), "mzzzz"); 
            time3 = System.nanoTime(); 
            System.out.println("Index of 'mzzzz' is " + mzzzz_index1 + " (linear search) and " + mzzzz_index2 + " (binary search)"); 
            System.out.println("Linear search took " + (time2 - time1) + " ns, and binary search took " + (time3 - time2) + " ns. \n"); 

            time1 = System.nanoTime(); 
            int aaaaa_index1 = Analyzer.linearSearch(StringData.getData(), "aaaaa"); 
            time2 = System.nanoTime(); 
            int aaaaa_index2 = Analyzer.binarySearch(StringData.getData(), "aaaaa"); 
            time3 = System.nanoTime(); 
            System.out.println("Index of 'aaaa' is " + aaaaa_index1 + " (linear search) and " + aaaaa_index2 + " (binary search)"); 
            System.out.println("Linear search took " + (time2 - time1) + " ns, and binary search took " + (time3 - time2) + " ns. \n"); 

    }
}