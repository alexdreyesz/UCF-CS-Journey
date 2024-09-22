import java.util.*;

public class hexagram {
	
	// Integer For Result Value 
	private static int result = 0;
	
	public static void main(String[] args) {
		// The Positions That Make Up All The Lines Values That Need To be Checked
		int[][] hexPositions = { {1, 2, 3, 4,}, {7, 8, 9, 10,}, {0, 3, 6, 10,}, {0, 2, 5, 7,}, {1, 5, 8, 11,}, {4, 6, 9, 11,}};
		// All 12 Values For The Input
		int[] values = new int[12];
		// Array For The Permutations
		int [] permutations = new int[12];
		//Boolean Array To Keep Track Of The Lines 
		boolean [] checkPosition = new boolean[12];
		// Integer To Store The Sum Value Needed For The Line Sum Calculation
		int hexSum = 0;
		Scanner scanInt = new Scanner(System.in);
		int counter = 0;
		int loop = 0;

		while(loop != 1) {		
			values[counter] = scanInt.nextInt();
			//HexSum Sum Of All Values 
			hexSum = hexSum + values[counter]; 
			counter++;
			// When All Values Are Entered Calculate The Hexagram 
			if(counter == 12) { 		
				// If The Sum Of All Values Equals 0 Means Input All 0's Program Termination 
				if(hexSum == 0) {
					break;
				}
	            // Hexagram Sum And Division By Half Of Its Vertices 
				hexSum = hexSum/3;
	            // Find The Permutation Result For Current Hexagram
				hexPermutation(values, permutations, hexSum, hexPositions, checkPosition, 0);
				// Reset HexSum And Counter To 0 To Reuse In New Hexagram
				hexSum = 0;
				counter = 0;
				//Divide By The Amount Of Rotation And Reflection That Is 12
				result = result/12;
				System.out.println(result);
			}			
		}		
	}
	
	// Find The Number Of Permutations In The Hexagram 
    private static void hexPermutation(int[] values, int [] permutations, int hexSum, int[][] hexPositions, boolean [] checkPosition, int position){ 
    	// If All The Positions Of The Array IN The Hexagram Are Full And Match Values Lenght Then Compare If They Match With HexSum  
        if(position == values.length){
            if(compareHexPositionSum(permutations, hexSum, hexPositions)){
            	result++;
            }
        }
        // Populate The Hexagram Lines To Be Able to Compare If All Of Their Individual Sums MAtch The HexSum
        for(int i = 0; i < values.length; i++){
            if(checkPosition[i] == false){
                //Populate Permutation Array With Values Array To Mirror The Hexagram	
            	permutations[position] = values[i];
            	// Set CheckPosition To True To Stop Loop If Array Is Correct
                checkPosition[i] = true;
                //If A Line Does Match The HexSum Then Find A Different One 
                if (fillLine(permutations, hexSum,hexPositions, position) == false) {
                	hexPermutation(values, permutations, hexSum, hexPositions, checkPosition, position + 1);
                }
                // Set CheckPosition To False To Keep Loop Going On
                checkPosition[i] = false;
            }
        }
    }
    
    // Search Hex Position With The Summation Of Its Values And Then Compare It To Hex Sum 
    private static boolean compareHexPositionSum(int[] permutations, int hexSum,  int[][] hexPositions){
        //Travel The Given Permutation Compare The HexPosition And Compare Its Sum With The HexSum 
        for(int i = 0; i < hexPositions.length; i++){
        	int[] hexNumber = hexPositions[i];
        	int permutationSum = 0;
        	// Get The Summation From The Determined Spots On The HexPosition 
            for(int x = 0; x < hexNumber.length; x++){           	
            	permutationSum = permutations[hexNumber[x]] + permutationSum;
            }
            // If Permutation Summation Is Not The Same As Hex Sum Then It Is Wrong
            if(hexSum != permutationSum){
                return false;
            } 
        }
        // If Permutation Summation Is The Same As Hex Sum Then It's Correct
        return true;
    }
    
    // Search For All Positions of HexPosition And Find If The Array Is Full Or If It Is Incomplete
    private static boolean fillLine(int[] permutations, int hexSum, int[][] hexPositions, int position) { 
        // Check If The Array Is Full 
        for (int i = 0; i < hexPositions.length; i++) {
        	int[] hexNumber = hexPositions[i];
        	int permutationSum = 0;
        	boolean isFull = true;    	
            // Travel The Array Until Is Full
            for (int x = 0; x < hexNumber.length; x++) {       	
                if (hexNumber[x] > position) {
                	isFull = false;
                    break;
                }
            }
            // When The Array Is Full Then Add The Numbers To Find If It Is A Solution
            if (isFull) {
            	// Get The Summation From The Determined Spots On The HexPosition
                for (int x = 0; x < hexNumber.length; x++) {
                	permutationSum = permutations[hexNumber[x]] + permutationSum;
                }       
                // If Permutation Summation Is Not The Same As Hex Sum Then It Is Wrong
                if (hexSum != permutationSum) {
                    return true; 
                }
            }
        }
        // If Permutation Summation Is The Same As Hex Sum Then It's Correct
        return false;
    } 
}
