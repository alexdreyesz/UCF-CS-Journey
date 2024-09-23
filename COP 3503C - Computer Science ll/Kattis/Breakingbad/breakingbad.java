/*
COP 3503 Spring 2024 Kattis #4: Breaking Bad
Copyright 2024 Alex D. Reyes
*/

import java.util.*;
import java.io.*;

public class breakingbad {
	
	// Fast IO Scanner 
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

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

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
    
    // BFS To Traverse The Graph And Find Available Solution Pairs 
    public static boolean bfs(int index, int[] vertices, ArrayList<Integer>[] edges) {
    	// Set Up Queue For BFS
    	Queue<Integer> queue = new LinkedList<>();
        queue.add(index);
        
        vertices[index] = 1; // Start With A Fresh Node

        while (queue.isEmpty() == false) { // Keep Going While Queue Is Not Empty
            int next = queue.poll(); // Get Next Node
            
            // Enqueue neighbors
            for (int i = 0; i < edges[next].size(); i++) {
            	
            	int current = edges[next].get(i);
            	
                if (vertices[current] == 0) { // Node Not Visited
                	
                	if (vertices[next] == 1) {
                	    vertices[current] = 2;
                	} else {
                	    vertices[current] = 1;
                	}
                	
                    queue.add(current);
                } else if (vertices[current] == vertices[next]) { // If They Are The Same Then It Is Not A Solution
                    return false;
                }
            }
        }

        return true; // If There Is A Solution Return True 
    }
    
    // Check If There Are Any Available Solutions 
    public static boolean isTwoColorable(int itemAmount, int[] vertices, ArrayList<Integer>[] edges) {
    	boolean foundSoultion = true; // Is There A Solution?
    	
    	for (int i = 0; i < itemAmount; i++) {
            if (vertices[i] == 0) {
            	
            	foundSoultion = bfs(i, vertices, edges); // Check For Solutions
            	
                if (foundSoultion == false) { // If There Is No Solution Return False
                    return foundSoultion;
                }
            }
        }
        return foundSoultion;  // If there is a Solution Return True
    }

    public static void main(String[] args) throws IOException {
    	
    	FastScanner scan = new FastScanner();

        // Variables To Handle The Input Data
        int itemAmount = 0; // Amount Of Items
        String[] itemNames; // Name Of Each Item
        int itemPairs = 0; // Amount Of Pairs To Be Made
        boolean foundSoultion = true; // Is There A Solution?

        // Data Structures To Handle The Manipulation Of Data
        int[] vertices; // Keeps Track Of The Amount Of Vertices
        ArrayList<Integer>[] edges; // Keeps Track Of The Amount Of Edges
        HashMap<String, Integer> itemsGraph = new HashMap<>(); // Keeps Track Of The Graph

        itemAmount = scan.nextInt(); // Input For The Amount Of Items

        itemNames = new String[itemAmount];

        edges = new ArrayList[itemAmount];

        vertices = new int[itemAmount];

        // For Loop To Input The Name Of All Items Add Them To The Graph And Populate The Edges Array List
        for (int i = 0; i < itemAmount; i++) {
        	edges[i] = new ArrayList<>();
            itemNames[i] = scan.next();
            itemsGraph.put(itemNames[i], i);
        }

        itemPairs = scan.nextInt(); // Input For The Amount Of Pairs
        
        // For Loop To Handle Data Of The Pair Of Suspicious Items That Can't Be Bought Together
        for (int i = 0; i < itemPairs; i++) {
            String[] pair = {scan.next(), scan.next()}; // Getting Input From Both Items And Separating Them
            edges[itemsGraph.get(pair[0])].add(itemsGraph.get(pair[1])); // Creating Relation Between Item 1 and Item 2
            edges[itemsGraph.get(pair[1])].add(itemsGraph.get(pair[0])); // Creating Relation Between Item 2 and Item 1
        }
        
        foundSoultion = isTwoColorable(itemAmount, vertices, edges);
        
        // If Statement To Display The Possible Combination Values With BFS 
        if (foundSoultion == true) { // A Solution Was Found 
            for (int i = 0; i < itemAmount; i++) { // Find And Print All Possible Combinations For Mr. White
                if (vertices[i] == 1) {
                    System.out.print(itemNames[i]);
                    System.out.print(" ");
                }
            }
            
            System.out.print("\n");
            
            for (int i = 0; i < itemAmount; i++) { // Find And Print All Possible Combinations For Jesse
                if (vertices[i] == 2) {
                    System.out.print(itemNames[i]);
                    System.out.print(" ");
                }
            }
        } else { // If No Possible Combination Was Found Then It Is Impossible To Solve
            System.out.println("impossible"); 
        }
    }
}
