/*
COP 3503 Spring 2024 Kattis #5: Tight Words
Copyright 2024 Alex D. Reyes
*/

import java.util.*;
import java.io.*;
import java.text.DecimalFormat;

public class tight {

	// Variables To Handle Tight Data
	public static DecimalFormat decimalPlaces = new DecimalFormat("0.000000000");
    public static int alphabet = 0;
    public static int wordLength = 0;
    public static double result = 0;
    
    // Fast IO Scanner 
    static class FastScanner {
    	// Variables To Handle Tokens
    	BufferedReader br;
        StringTokenizer st;
        
        // Method To Create Scanner 
        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        
        // Check For Next Token 
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null)
                        return null; // No More Input
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        
        // Get Next Integer 
        int nextInt() {
            return Integer.parseInt(next());
        }
        
        // Close Fast Scanner 
        void close() throws IOException {
            br.close();
        }
    }

    public static void main(String[] args) throws IOException {
    	FastScanner scanner = new FastScanner(); // Fast IO Scanner 

        // Loop Until There Is No More Inputs
        while (true) {
            String token = scanner.next(); // Get Input 
            
            // If No More Input Break The Loop As String Is Null 
            if (token == null) {
            	break;
            }
                
            alphabet = Integer.parseInt(token); // Parse String Input To Integer 
            wordLength = scanner.nextInt();
            tightWords(); // Calculate The Amount Of Tight Words 
            System.out.println(decimalPlaces.format(result)); // Output The Tight Percentage Result 
        }
        
        scanner.close(); // Close The Scanner 
    }
    
    // Function To Calculate The Percentage Of How Tight A Word Is 
    public static void tightWords() {
        // Variables To Handle Data Handling  
    	double tightPercentage = 0;
    	double[][] dynamicProgramming = new double[wordLength + 1][alphabet + 1];
        
        // Initialize The Data Of The Double Array To 1
        for (int i = 0; i <= alphabet; i++) {
        	dynamicProgramming[1][i] = 1;
        }

        // Add The Data To The Dynamic Double Array
        for (int i = 2; i <= wordLength; i++) { // Loop Through The Words Length 
            for (int j = 0; j <= alphabet; j++) { // Loop Through The Alphabet Combinations 
            	// Get The Previous Neighbor      	
            	dynamicProgramming[i][j] = dynamicProgramming[i-1][j];
            	         
            	// Try Words With A Lower Neighbor Number 
                if (j > 0) { 
                	dynamicProgramming[i][j] = dynamicProgramming[i][j] + dynamicProgramming[i-1][j-1];
                }
                
                // Try Words With A Higher Neighbor Number 
                if (j < alphabet) {
                	dynamicProgramming[i][j] = dynamicProgramming[i][j] + dynamicProgramming[i-1][j+1];
                }       
            }
        }

        // Count The Amount Of Tight Words Of Length N
        for (int i = 0; i <= alphabet; i++) {
        	tightPercentage = tightPercentage + dynamicProgramming[wordLength][i];
        }
        
        tightCalculation(tightPercentage); // Get The Tight Percentage Calculation 
    }
    
    // Calculate The Tight Percentage
    public static void tightCalculation(double tightPercentage) {
    	// Variables To Handle The Exponent Calculation 
    	double base = alphabet + 1;
    	double exponent = wordLength;
    	double calculation = 1;
    	
    	// Get The Exponential Power Of The Base In Respect Of The Exponent 
    	for (int i = 0; i < exponent; i++) {
    		calculation = calculation * base; 
    	}
    	
    	// Get The Calculation Result 
    	result = 100 * (tightPercentage / calculation);
    }
}