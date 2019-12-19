import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class RleProgram {
    //MEMBER FUNCTIONS
    //converts an array of bytes into hexadecimal form stored in a string; may be either in rle or raw format
    public static String toHexString(byte[] data){
        String temp = "";
        for(byte b : data)
            temp += Integer.toHexString(b);
        return temp;
    }

    //gets number of runs of any single color from a byte array
    public static int countRuns(byte[] flatData){
        int numRuns = 1;
        byte prev, now, counter = 0;
        for(int i = 1; i <= flatData.length - 1; i++){
            ++counter;
            now = flatData[i];
            prev = flatData[i - 1];
            if(now != prev) {
                while (counter > 15){
                    ++numRuns;
                    counter -= 15;
                }
                ++numRuns;
                counter = 0;
            }
        }
        return numRuns;
    }

    //lossless compression of raw data representation of colored pixels into RLE format
    public static byte[] encodeRle(byte[] flatData){
        ArrayList<Integer> encodedData = new ArrayList<>();
        encodedData.ensureCapacity(RleProgram.countRuns(flatData) * 2);
        int prev, now, counter = 0;
        for(int i = 1; i <= flatData.length - 1; i++) {
            ++counter;
            now = flatData[i];
            prev = flatData[i - 1];
            if(now != prev){
                while(counter > 15){
                    encodedData.add(15);
                    encodedData.add(prev);
                    counter -= 15;
                }
                encodedData.add(counter);
                encodedData.add(prev);
                counter = 0;
            }
        }
        byte[] output = new byte[encodedData.size()];
        for(int i = 0; i <= encodedData.size() - 1; i++)
            output[i] = encodedData.get(i).byteValue();
        return output;
    }

    //finds number of distinct and continuous runs in copmressed rle data
    public static int getDecodedLength(byte[] rleData){
        int sum = 0;
        for(int i = 0; i <= rleData.length - 1; i += 2)
            sum += rleData[i];
        return sum;
    }

    //re-converts compressed rle data back to uncompressed raw format
    public static byte[] decodeRle(byte[] rleData){
        byte[] decodedArr = new byte[RleProgram.getDecodedLength(rleData)];
        int index = 0;
        for(int i = 0; i <= rleData.length - 1; i += 2){
            for(int j = 0; j <= rleData[i] - 1; j++){
                decodedArr[index] = rleData[i + 1];
                ++index;
            }
        }
        return decodedArr;
    }

    //converts hexadecimal string to byte array, where each element corresponds to 1 character in hex string
    public static byte[] stringToData(String dataString){
        byte[] byteData = new byte[dataString.length()];
        for(int i = 0; i <= dataString.length() - 1; i++)
            byteData[i] = (byte)Character.digit(dataString.charAt(i), 16);
        return byteData;
    }

    //converts rle data into string as follows for each run:
    //run length in decimal, run value in hexadecimal, delimiter ":"
    public static String toRleString(byte[] rleData){
        String temp = "";
        for(int i = 0; i <= rleData.length - 1; i += 2){
            temp = temp.concat(String.valueOf(rleData[i]));
            temp = temp.concat(Integer.toHexString(rleData[i + 1]));
            temp = temp.concat(":");
        }
        temp = temp.substring(0, temp.length() - 1);
        return temp;
    }

    //translates human-readable string representation of rle back into regular rle data array; inverse of previous function
    public static byte[] stringToRle(String rleString){
        String[] pairs = rleString.split(":");
        byte[] arr = new byte[pairs.length * 2];
        int index = 0;
        for(int i = 0; i <= arr.length - 1; i++){
            if(i % 2 == 0) {
                if (pairs[index].length() == 3)
                    arr[i] = Byte.valueOf(pairs[index].substring(0, 2));
                else
                    arr[i] = Byte.valueOf(Character.toString(pairs[index].charAt(0)));
            } else {
                arr[i] = (byte)Character.digit(pairs[index].charAt(pairs[index].length() - 1), 16);
                ++index;
            }
        }
        return arr;
    }

    //converts raw hex string to rle or hex string
    public static String rawStringToHexString(String rawString){
        String str = "";
        int counter = 0;
        char currentChar;
        for(int i = 1; i <= rawString.length() - 1; i++){
            ++counter;
            if(rawString.charAt(i) != rawString.charAt(i - 1)){
                currentChar = rawString.charAt(i - 1);
                while(counter > 15) {
                    str += ("f".concat(Character.toString(currentChar)));
                    counter -= 15;
                }
                str += Character.toString(Character.forDigit(counter, 16));
                str += currentChar;
                counter = 0;
            }
        }
        char lastChar = rawString.charAt(rawString.length() - 1);
        if(lastChar != rawString.charAt(rawString.length() - 2))
            str += ("1" + String.valueOf(lastChar));
        else
            str += (Character.forDigit(counter + 1, 16) + lastChar);
        return str;
    }

    //menu printing
    public static void printMenu(){
        System.out.println("RLE Menu");
        System.out.println("--------");
        System.out.println("0. Exit");
        System.out.println("1. Load File");
        System.out.println("2. Load Test Image");
        System.out.println("3. Read RLE String");
        System.out.println("4. Read RLE Hex String");
        System.out.println("5. Read Data Hex String");
        System.out.println("6. Display Image");
        System.out.println("7. Display RLE String");
        System.out.println("8. Display Hex RLE Data");
        System.out.println("9. Display Hex Flat Data\n");
    }

    public static void main(String[] args){
        //most essential variables needed
        Scanner scanner = new Scanner(System.in);
        int menuChoice;
        String filename;
        byte[] file = null;
        byte[] rawData = null;
        byte[] rleData = null;
        String rleString = "";
        String rleHexString = "";
        String rawHexString = "";

        System.out.println("Welcome to the RLE image encoder! \n");
        System.out.println("Displaying Spectrum Image:");
        ConsoleGfx.displayImage(ConsoleGfx.testRainbow);
        System.out.println("\n");

        do{
            do {
                RleProgram.printMenu();
                System.out.print("Select a Menu Option: ");
                menuChoice = scanner.nextInt();
                if(menuChoice < 0 || menuChoice > 9)
                    System.out.println("Error! Invalid input.\n");
            } while(menuChoice < 0 || menuChoice > 9);
            if(scanner.hasNextLine())
                scanner.nextLine();
            switch(menuChoice){
                case 1 : {
                    System.out.print("Enter name of file to load: ");
                    filename = scanner.nextLine();
                    file = ConsoleGfx.loadFile(filename);
                    rleData = Arrays.copyOf(file, file.length);
                    rawData = RleProgram.decodeRle(rleData);
                    rleString = RleProgram.toRleString(rleData);
                    rleHexString = RleProgram.toHexString(rleData);
                    rawHexString = RleProgram.toHexString(rawData);
                    break;
                }
                case 2 : {
                    file = ConsoleGfx.testImage;
                    if(file.equals(ConsoleGfx.testImage)){
                        rleData = Arrays.copyOf(file, file.length);
                        rawData = RleProgram.decodeRle(rleData);
                        rleString = RleProgram.toRleString(rleData);
                        rleHexString = RleProgram.toHexString(rleData);
                        rawHexString = RleProgram.toHexString(rawData);
                        System.out.println("Test image data loaded.\n");
                    }
                    break;
                }
                case 3 : {
                    System.out.print("Enter an RLE string to be decoded: ");
                    rleString = scanner.nextLine();
                    rleData = RleProgram.stringToRle(rleString);
                    rawData = RleProgram.decodeRle(rleData);
                    rleHexString = RleProgram.toHexString(rleData);
                    rawHexString = RleProgram.toHexString(rawData);
                    break;
                }
                case 4 : {
                    System.out.print("Enter the hex string holding RLE data: ");
                    rleHexString = scanner.nextLine();
                    rleData = RleProgram.stringToData(rleHexString);
                    rawData = RleProgram.decodeRle(rleData);
                    rleString = RleProgram.toRleString(rleData);
                    rawHexString = RleProgram.toHexString(rawData);
                    break;
                }
                case 5 : {
                    System.out.print("Enter the hex string holding flat data: ");
                    rawHexString = scanner.nextLine();
                    rleHexString = RleProgram.rawStringToHexString(rawHexString);
                    rleData = RleProgram.stringToData(rleHexString);
                    rawData = RleProgram.decodeRle(rleData);
                    rleString = RleProgram.toRleString(rleData);
                    break;
                }
                case 6 : {
                    System.out.println("Displaying image...");
                    if(rleData == null)
                        System.out.print("(no data)");
                    else
                        ConsoleGfx.displayImage(rleData);
                    System.out.println("\n");
                    break;
                }
                case 7 : {
                    System.out.println("RLE representation: " + (rleString.isEmpty() ? "(no data)" : rleString) + "\n");
                    break;
                }
                case 8 : {
                    System.out.println("RLE hex values: " + (rleHexString.isEmpty() ? "(no data)" : rleHexString) + "\n");
                    break;
                }
                case 9 : {
                    System.out.println("Flat hex values: " + (rawHexString.isEmpty() ? "(no data)" : rawHexString) + "\n");
                    break;
                }
                default : return;
            }
        } while(menuChoice != 0);
    }
}