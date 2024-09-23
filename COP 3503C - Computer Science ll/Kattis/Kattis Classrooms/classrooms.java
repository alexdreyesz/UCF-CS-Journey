/*
COP 3503 Spring 2024 Homework #3: Making Connections
Copyright 2024 Alex D. Reyes
*/

import java.util.*;

public class classrooms {
	
	public static void main (String[] args) {
		// Variables For Input
		int activities = 0;
		int classrooms = 0;
		
		Scanner scanInt = new Scanner (System.in);
		
		activities = scanInt.nextInt(); // Input Amount Of Activities 
		classrooms = scanInt.nextInt(); // Input Amount Of Classrooms Available 
		
		// Variables To Store The Starting And Ending Time Of The Activities
		int total = 0;
		int [][] timeFrames = new int[activities][2]; // x Axis Start Time y Axis End Time 
		
		// Loop To Get All Values And Find The Optimal Solution 
		for(int i = 0; i < activities; i++) {
			timeFrames[i][0] = scanInt.nextInt(); // Start Times
			timeFrames[i][1] = scanInt.nextInt(); // End Times 	
		}
	
		total = greedy(timeFrames, activities, classrooms); // Greedy Algorithm 

		System.out.println(total);
		
	}
	
	// Greedy Algorithm  
	public static int greedy(int[][] timeFrames, int activities, int classrooms) {
		
		// Variables To Handle The Activities Time 
		int total = 0;
		int [][][] timeChart = new int[1][2][classrooms]; // Chart To Keep Track Of Time Collision Between Rooms
		
		// Variable To Handle Time Management 
		int smaller = 0;
		int range = 0;
		boolean isFound = false;
		int tracking = 0; // Keep Track Of Best Classroom
		
		Arrays.sort(timeFrames, Comparator.comparingInt(a -> a[1])); // Sort By End Times
				
		// Loop Through All Activities 
		for(int i = 0; i < timeFrames.length; i++) {
			
			smaller = Integer.MAX_VALUE; // Set Smaller To Max

			// Loop Though All Classrooms
			for(int x = 0; x < classrooms; x++) {	

				
				if(timeChart[0][1][x] < timeFrames[i][0]) {
									
					isFound = true; // Found A Possible Value
					
					range = timeFrames[i][0] - timeChart[0][1][x]; // Check The Range
					
					// If It Is Smalle A Value Was Found 
					if(range < smaller) {
						smaller = range; 
						tracking = x;
					}

				}
				
				//If Empty Just Add Value On 0 Space
				if(timeChart[0][0][x] == 0 && timeChart[0][1][x] == 0) {
					break;
				}
						
			} // LOOP INSIDE
				
			// If A Solution Was Found Add It To The Chart 
			if(isFound == true) {
				timeChart[0][0][tracking] = timeFrames[i][0]; // Keep Track Of Top Starting Time At X Position
				timeChart[0][1][tracking] = timeFrames[i][1]; // Keep Track Of Top Ending Time At X Position
				total++;  // A Solution Was Found Update Total
				isFound = false;
			}	
		} 
	
		return total; // Return Value 
	}
	
	
	
	
	
	
	
} // Classrooms

