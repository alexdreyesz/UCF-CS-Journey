import java.util.*;

public class sga {

    public static void main(String[] args) {

        // Scanner Types
        Scanner scanInt = new Scanner(System.in);
        Scanner scanStr = new Scanner(System.in);
        
        // HashMap To Organize And Count Same Names
        HashMap<String, Integer> people = new HashMap<>();
        
        // HashMap To Organize And Count Letter Initials Quantity
        HashMap<Character, Integer> letter = new HashMap<>();

        // Amount of Name couples
        int couples = 0;
        
        // Amount Of Actions
        int amount = scanInt.nextInt();

        // Loop To Create List According To Amount Of Actions
        for (int i = 0; i < amount; i++) {

            // Input Name
            String name = scanStr.nextLine();

            // Check If The Name Is Already In The HashMap
            if (people.containsKey(name)) {
                // If Yes Increment The Count
                int count = people.get(name);
                people.put(name, count + 1);
            } else {
                // If It Is Not Add The Name With A Count Of 1
                people.put(name, 1);
            }

            // Check If The Initial Letter Is Already In The HashMap
            char initial = name.charAt(0);
            if (letter.containsKey(initial)) {
                // If Yes Increment The Count
                int count = letter.get(initial);
                letter.put(initial, count + 1);
            } else {
                // If It Is Not Add The Initial Letter With A Count Of 1
                letter.put(initial, 1);
            }
        }
        
        // For Loop To Use Both Hashmaps To Find The Values
        for (Map.Entry<String, Integer> entryPeople : people.entrySet()) {
        	
        	// Find The Amount Of Double Names And Find The Appropiate Value For Each Duplicate Pair And Individual Pair
            for (Map.Entry<Character, Integer> entryLetter : letter.entrySet()) {
                if (entryLetter.getValue() != 1 && entryPeople.getKey().charAt(0) == entryLetter.getKey()) {         
                    couples = couples + (entryLetter.getValue() - entryPeople.getValue()) * entryPeople.getValue();
                }
            }

        }

        // Print Final Result
        System.out.println(couples);

        // Close Integer Scan Scanner
        scanInt.close();
        // Close String Scan Scanner
        scanStr.close();
    }
}
