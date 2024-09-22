/*
COP 3503 Spring 2024 Homework #3: Making Connections
Copyright 2024 Alex D. Reyes
*/

import java.util.*;

public class connect {
	// Find The Greatest Common Denominator With The Euclidean Algorithm
	public static long GCD(long u, long v){
		   if ( v == 0) {
			   return u;
		   } else {
			   return GCD(v,u%v);   
		   }
	}

	public static void main(String[] args) {	
		// Variables To Handle User Input
		int computers = 0;
		int connections = 0;
		int operation = 0;
		int u =0;
		int v = 0;
		
		// Variables To Handle Data To Process Fractions Correctly
		long tempU = 0;
	    long tempV = 0; 
	    long GCD = 0;
		
		Scanner scanInt = new Scanner(System.in); 
		
		// Scan User Input
		computers = scanInt.nextInt();
		connections = scanInt.nextInt();	
		
		// Create The Disjoined Set
		disjoinedSet djSet = new disjoinedSet(computers);
		
		// Loop For Amount Of Connections That Are To Be Made 
		for(int i = 0; i < connections; i++) {
			operation = scanInt.nextInt(); // Operation To Be Performed 1 Or 2 Else Error
			
			// Create A Union
			if(operation == 1) {
				// INput For Sets To Be United 
				u = scanInt.nextInt();
				v = scanInt.nextInt();
				
				djSet.union(u, v); // Unit The Set 	
			} else if (operation == 2) { // Display Connectivity Amount 
				// Prepare Data To Be Converted To Fraction
				tempU = djSet.getConnectivity();
			    tempV = djSet.getDisconnected(); 
			    
			    // Find GCD
			    GCD = GCD(tempU, tempV);
			    
			    // Divide Data By The GCD To Find Appropriate Fraction
			    tempU = tempU/GCD;
			    tempV = tempV/GCD;
			    
			    System.out.println(tempU + "/" + tempV);	
			} else { // If Input Is Wrong An Error Occurred  
				System.out.println("Wrong Output");
				break;
			}
		} 
	} 
} 

class disjoinedSet {
	// Variables To Handle Disjoined Array Data For The Trees 
	private int[] parent;
	private long[] size;
	
	// Variable To keep Track Of The Connectivity Data Form The Computers
	private int disconnected; // Amount Of Computers Without A Connection
	private long connectivity; // Sum Of The Size Squares of The Respective Connectivity Amounts 
	
	// Creates A Disjoint Set With Items The Size Of The Amount Of Computers
	public disjoinedSet(int computers) {
		disconnected = computers; // Amount Of Connections For The Computers 
		
		// Allocate Memory For Both Arrays For The Disjoined Set
		parent = new int[computers + 1];
		size = new long[computers + 1];
		
		// Initialize And Populate The Separate Sets
		for (int i = 1; i <= computers; i++) {
			parent[i] = i;
			size[i] = 1;
		}
		connectivity = computers; // Amount Of Connections For The Computers 
	}	
	
	// Find The Parent Root With Path Compression
	public int find(int v) {
		if (parent[v] == v) return v;
		return parent[v] = find(parent[v]);
	}
	
	// Unions The Set Storing U With The Set Storing V
	public boolean union(int u, int v) {
		
		// Search And Get Both Parent Root In The Trees
		u = find(u);
		v = find(v);
		
		// If Both Parent Root Are Equal Don't Perform Any Action Else Continue 
		if (u == v) return false;
		
		// Lower The Amount Of Disconnected Computers 
		disconnected--;
		
		// Update The Connectivity Size 
		long updatedSize = size[u] + size[v];
		connectivity = connectivity + (updatedSize*updatedSize - (size[u]*size[u] + size[v]*size[v]));
		
		// Merge Both Trees And Update Their Sizes
		parent[v] = u; // Set The New Parent Root/Host Of The Connected Computer
		size[u] = size[u] + size[v]; // Increment Parent Root/Host Amount Of Connections  
		size[v] = - 1; // Set Already Connected Computer to -1 
		return true;
	}
	
	// Return The Disconnected Number Of Computers Of The Disjoined Set
	public long getDisconnected() {
		return disconnected;
	}
	
	// Return The Connectivity Of The Disjoined Set
	public long getConnectivity() {
		return connectivity;
	}
}