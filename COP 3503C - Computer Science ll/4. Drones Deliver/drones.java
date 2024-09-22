/*
COP 3503 Spring 2024 Homework #4: Drones Deliver to Senior Design Groups
Copyright 2024 Alex D. Reyes
*/

import java.io.*;
import java.util.*;

public class drones {
	// Grid Variables To Handle Grid Data Manipulation
    public static String[][] grid = new String[8][8];
    public static int GRID_DIMENSION = grid.length;
    public static int INFINITY = Integer.MAX_VALUE;
	
	// Directions To Handle Coordinates Changes 
    final public static int[] DX = {-1,0,0,1};
	final public static int[] DY = {0,-1,1,0};
 
    // Variables To Store Initial, Current, And Ending Bitmasks
    public static int initialPosition = 0x00;
    public static int currentPosition = 0x00;
    public static int finalPosition = 0x00; 
    
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
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        
        // Check If it Is An Integer
        int nextInt() {
            return Integer.parseInt(next());
        }
        
        // Method To Close Scanner 
        void close() throws IOException {
            br.close();
        }
    }
    
    public static void main(String[] args) throws IOException {	
    	int droneAmount = 0; // Variable For The Amount Of Drones And Senior Design Groups
    	
    	FastScanner scan = new FastScanner(); // Fast IO Scanner To Scan Input 
		
    	droneAmount = scan.nextInt(); // Input For The Amount Of Drones And Senior Design Groups
		 
		int[][] droneCoordinates = new int[droneAmount][2]; // 2D Array To Store Coordinates For Drones
		
		int[][] groupCoordinates = new int[droneAmount][2]; // 2D Array To Store Coordinates For The Senior Design Group
		
		// Grab Input To Create The 64 Grids Graph 
		for(int i = 0; i < 8; i++) { // Columns
			for(int x = 0; x < 8; x++) { // Rows 
				grid[i][x] = scan.next(); // Enter Input
				
				int current = 0; // VAriable To Keep Track Of Current Drone Or Group Index 
				
				// If input Has A 'D' It Is A Drone
				if(grid[i][x].charAt(0) == 'D') {
				    current = Character.getNumericValue(grid[i][x].charAt(1)) - 1; // Check Next Character And Pass It To An Integer To Grab The Index
				    droneCoordinates[current][0] = i; // Store Columns Coordinate
				    droneCoordinates[current][1] = x; // Store Row Coordinate
				}

				// If input Has A 'G' It Is A Senior Design Group
				if(grid[i][x].charAt(0) == 'G') {
				    current = Character.getNumericValue(grid[i][x].charAt(1)) - 1;  // Check Next Character And Pass It To An Integer To Grab The Index
				    groupCoordinates[current][0] = i; // Store Columns Coordinate
				    groupCoordinates[current][1] = x; // Store Row Coordinate
				}		
			}
		}
		
		initialPosition = Bitmask(droneCoordinates); // Get Starting Positions For Drones 
		
		finalPosition = Bitmask(groupCoordinates); // Get Final Position Of The Drones Based On The Senior Design Groups Coordinates
        
        int minActions = bfs(droneAmount, initialPosition, finalPosition); // Find Minimum Amount Of Controller Actions Needed With BFS
        System.out.println(minActions);
        
        // Close the scanner
        scan.close();
    }
    
    // Use Drone Coordinates Data And Store Them In A 24 Bits Integer With Bitmask
    private static int Bitmask(int[][] coordinates) {
        int bitmask = 0x00; // Variable For Bitmask Result
        
        // Loop Thought All Drone Coordinates And Store The Data In An 24 bits Integer To Store The Data
        for (int i = 0; i < coordinates.length; i++) {
            int position = coordinates[i][0] * 8 + coordinates[i][1]; // Calculate Position IndeX
            bitmask |= position << (6 * i); // Shift And Combine Into The Bitmask
        }

        return bitmask;
    }
    
    //Check If Current Coordinate Is Inside Of Established Bounds 
    public static boolean inbounds(int row, int column){
        return row >= 0 && row < GRID_DIMENSION && column >= 0 && column < GRID_DIMENSION;
    }
    
    // Check If The Drone Arrived To its Corresponding Senior Design Group 
    public static boolean arrived(int droneNumber, int updatedRow, int updatedColumn) {
    	String seniorDesignGroup = grid[updatedRow][updatedColumn]; // Check Current Grid
    	
    	// Check If The Current Grid Is A Senior Design Spot
    	if(seniorDesignGroup.charAt(0) == 'G') {	
    		return seniorDesignGroup.equals("G" + (droneNumber + 1)); // If Drone Is The Same Then Return True Else False
    	}

    	return true; // If The Grid Is Not A Senior Design Group return True 
    }
    
    //Check For All The Exceptions That Need To Be Taken In Consideration 
    public static boolean exceptions(int droneNumber, int updatedPosition, int row, int column, int updatedRow, int updatedColumn){
    	// Check  For Exceptions If Updated Row Is Out Of Bounds, Has Arrived To If Senior Design Group, Its A Different Design Group, or Grid Is No fly Zone "XX" 
    	if(!inbounds(updatedRow, updatedColumn) || !arrived(droneNumber, updatedRow, updatedColumn) || grid[updatedRow][updatedColumn].equals("XX") || grid[row][column].equals("G" + (droneNumber + 1))) {
    		return true;
    	}
    	
        return false;
    }
    
    // Function That Given A Bitmask For A Current Position, Calculates The Set Of Bitmasks That Could Be The Next Position
    public static int currentBitmask(int droneNumber, int updatedPosition, int row, int column, int updatedRow, int updatedColumn) {
    	int updatedCoordinates = 0; // Variable For Updated Coordinates 
    	
    	// Check For Exceptions 
    	if(exceptions(droneNumber, updatedPosition, row, column, updatedRow, updatedColumn)) {
    		updatedCoordinates  = updatedPosition; // No Change In Coordinates
    	} else {
    		updatedCoordinates  = updatedRow * GRID_DIMENSION + updatedColumn; // Update Coordinates 
    	}
    	
    	currentPosition |= updatedCoordinates  << (6 * droneNumber); // Bitmask Current Drone Into Integer To Store Updated Location
    	
    	return currentPosition;
    }
    
    // BFS To Find The Minimum Amount Of Actions Needed To Arrive To Each Senior Design Group
    public static int bfs(int droneAmount, int initialPosition, int finalPosition) {
    	// Data Structures To handle Queue And Distances 
    	int[] distance = new int[(int) Math.pow(2, 6 * droneAmount)]; // Accommodate Size For All Possible Grid State Variations Size 2^(6 * numDrones)
        Arrays.fill(distance, INFINITY); // Initialize Distances To Highest Value Infinity
    	Queue<Integer> queue = new LinkedList<>(); // Queue To Store Next Bitmask State 
        queue.add(initialPosition); // Start With The Drones Initial Position 
        distance[initialPosition] = 0; // Initial Distance Set to 0
        
        // Variables To Update Current Drone Coordinates  
        int current = 0;
        int updatedPosition = 0;
        int row = 0;
        int column = 0;
        int updatedRow = 0;
        int updatedColumn = 0;
        
        // Loop While Queue Is Not Empty
        while (!queue.isEmpty()) {
            current = queue.poll(); // Get Next Coordinate From The Queue
           
            // If Current Is The Same As Final Position That Means All Drones Have Arrived To Their Respective Groups
            if (current == finalPosition) {
                return distance[current];
            }
            
            // Loop Thought All Directions To Update The Coordinates 
            for (int d = 0; d < DX.length; d++) {
            	currentPosition = 0x00; // Reset Current Position And Get A New One 
                
            	// Update Each Drone Coordinates 
                for(int i = 0; i < droneAmount; i++) {
                	updatedPosition = (current >> (6 * i)) & 63; // Get Current Updated Position 
                	
                	row = updatedPosition / GRID_DIMENSION; // Gets Updated Position Row Index
                	column = updatedPosition % GRID_DIMENSION; // Gets Updated Position Column Index
                	
                	updatedRow = row + DX[d]; // Update Row To A New Direction DX
                	updatedColumn = column + DY[d]; // Update Column To A New Direction With DY
                	
                	currentPosition = currentBitmask(i, updatedPosition, row, column, updatedRow, updatedColumn); // Function To Get Next Bitmask With Updated Coordinate 
                }
            	// Update Closest Distance 
            	if (distance[currentPosition] > distance[current] + 1) {
            		distance[currentPosition] = distance[current] + 1;
            		queue.add(currentPosition);
            	}	
            }
        }
    	return -1; //There Is No Solution Found 
    }  
}