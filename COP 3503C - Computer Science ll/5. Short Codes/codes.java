/*
COP 3503 Spring 2024 Homework #5: Short Codes
Copyright 2024 Alex D. Reyes
*/

import java.io.*;
import java.util.*;

public class codes {
	
	// Variable Declaration To Handle Drug And Code Data
	public static int drugAmount = 0;
	public static int codeAmount = 0;
	public static int capacity = 0;
	public static String[] drugNames;
	public static String[] codeNames;
	public static Boolean[] isCodeUsed;
	
	// Add All Of The Input Information On The Graph
	public static void addGraphData(FordFulkerson Graph) {
		//Use Capacity Array To Keep Track Of The Flow
        for (int i = 0; i < drugAmount; i++) {
            for (int j = 0; j < codeAmount; j++) {
                if (drugNames[i].contains(codeNames[j])) {
                	Graph.add(i, drugAmount + j, 1);
                	isCodeUsed[j] = true;
                }              
            }
        }
        
        //Add All Of The Codes To The Sink
        for (int i = 0; i < codeAmount; i++) {
        	Graph.add(drugAmount + i, Graph.sink, 1); 
        }

        //Add All Of The Drugs To The Source
        for (int i = 0; i < drugAmount; i++) {
        	Graph.add(Graph.source, i, 1);
        }
	}
	
	// Check If Max Flow Was Achieved With FordFulkerson Algorithm 
	public static void achievedMaxFlow(FordFulkerson Graph) {
		//If Flow Equals The Amount Of Drugs Then Max Flow Was Achieved 
        if (Graph.ff() == drugAmount) {
            // Max Flow Was Achieved
        	System.out.println("yes");
            
            int counter = 0;
            
            // Print The Codes
            for(int i = 0; i < drugAmount;) {
            	
            	if(isCodeUsed[counter] == true) {
            		System.out.println(codeNames[i]);
            		i++;
            	}
            	
            	if (counter < codeAmount) {
            		counter++;
            	}
            }
        } else {
            System.out.println("no");
        }  
	}
	
	// Print Capacity From FordFulkerson
	public void printCapacity(FordFulkerson Graph) {
		System.out.print("\n\n");
        for(int i = 0; i < capacity; i++) {
        	for(int j = 0; j < capacity; j++) {
            	System.out.print(Graph.cap[i][j]);
            }
        	System.out.print("\n");
        }
	}

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
		
		FastScanner scan = new FastScanner(); // Fast IO Scanner To Scan Input 
		
		// Get Input Data
		drugAmount = scan.nextInt();
		codeAmount = scan.nextInt();
		
		capacity = drugAmount + codeAmount; // The Capacity To Use In The Graph 
		
        FordFulkerson Graph = new FordFulkerson(capacity); 	//Create A FordFulkerson With Drugs Plus Codes Amount
		
		// Modify Arrays To Fill The Specific Amount Of Data 
		drugNames = new String[drugAmount];
		codeNames = new String[codeAmount];
		isCodeUsed = new Boolean[codeAmount];
		
		Arrays.fill(isCodeUsed, false); // Set isCodeUsed to false Default 
		
		// Get All Drug Names 
		for(int i = 0; i < drugAmount; i++) {
			drugNames[i] = scan.next();
		}
		
		// Get All Code Names
		for(int i = 0; i < codeAmount; i++) {
			codeNames[i] = scan.next();
		}
		
		addGraphData(Graph); // Add All Of The Data In The Graph
		
		achievedMaxFlow(Graph); // Check If Max Flow Was Achieved With FordFulkerson Algorithm   
		
		scan.close(); // Close Scanner 
	}
}

class FordFulkerson { 
	
	// Stores Graph.
	public int[][] cap;
	public int n;
	public int source;
	public int sink;

	// "Infinite" Flow.
	final public static int oo = (int)(1E9);

	// Set Up Default Flow Network With Size+2 Vertices, Size Is Source, Size+1 Is Sink.
	public FordFulkerson(int size) {
		n = size + 2;
		source = n - 2;
		sink = n - 1;
		cap = new int[n][n];
	}

	// Adds An Edge From v1 -> v2 With Capacity c.
	public void add(int v1, int v2, int c) {
		cap[v1][v2] = c;
	}

	// Wrapper Function For Ford-Fulkerson Algorithm
	public int ff() {

		// Set Visited Array And Flow.
		boolean[] visited = new boolean[n];
		int flow = 0;

		// Loop Until No Augmenting Paths Found.
		while (true) {

			// Run One DFS.
			Arrays.fill(visited, false);
			int res = dfs(source, visited, oo);

			// Nothing Found, Get Out.
			if (res == 0) break;

			// Add This Flow.
			flow += res;
		}

		// Return It.
		return flow;
	}

	// DFS To Find Augmenting Math From v With Maxflow At Most Min.
	public int dfs(int v, boolean[] visited, int min) {

		// Got To The Sink, This Is Our Flow.
		if (v == sink)  return min;

		// We've Been Here Before - No Flow.
		if (visited[v])  return 0;

		// Mark This Node And Recurse.
		visited[v] = true;
		int flow = 0;

		// Just Loop Through All Possible Next Nodes.
		for (int i = 0; i < n; i++) {

			// We Can Augment In This Direction.
			if (cap[v][i] > 0)
				flow = dfs(i, visited, Math.min(cap[v][i], min));

			// We Got Positive Flow On This Recursive Route, Return It.
			if (flow > 0) {

				// Subtract It Going Forward.
				cap[v][i] -= flow;

				// Add It Going Backwards, So That Later, We Can Flow Back Through This Edge As A Backedge.
				cap[i][v] += flow;

				// Return This Flow.
				return flow;
			}
		}

		// If We Get Here There Was No Flow.
		return 0;
	}
}


