import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

//Driver Class
public class DriverClass {
   
	//Main Project
	public static void main(String[] array) throws IOException{
        
        // Create Array Lists For Storing Text 
        List<String> onlineLectures = new ArrayList<>();
        List <String> noLabLectures = new ArrayList<>();

        //Open "lec.txt" File 
        Scanner scanFile = new Scanner(new File("lec.txt"));
        
        //Scan The File And Look For Lectures 
        int onlineLectureAmount = 0;
        String textLines = "";

        while (scanFile.hasNextLine()) {
            textLines = scanFile.nextLine();
            String[] split = textLines.split(",");

            if (split.length > 2 && split[4].equalsIgnoreCase("Online")) {
                onlineLectureAmount++;
                onlineLectures.add(textLines);
            } 
            
            if (split.length > 5 && split[6].equalsIgnoreCase("No")) {
                noLabLectures.add(textLines);
            }
        }
        
        //Close "lec.txt" File 
        scanFile.close();
        
        // Reopen "lec.txt" File 
        scanFile = new Scanner(new File("lec.txt"));
        
        //Scanner To Get Classroom Prefix String 
        Scanner scanString = new Scanner(System.in);
        
        // Print Screen Text
        System.out.println("- There are " + onlineLectureAmount + " online lectures offered");
        System.out.print("- Enter the classroom: ");
        
        //Classroom Location Input
        String location = scanString.nextLine();
        
        //Scan The CRNs and then Print The String
        String crnTxt = "";
        String classroom = "";

        while (scanFile.hasNextLine()) {
        	classroom = scanFile.nextLine();
        	if (classroom.contains(location)) {
        		crnTxt += classroom.split(",")[0] + " ";
        	}
        }

        System.out.println("     The crns held in " + location + " are: " + crnTxt.trim());
       
        //Create File For Output
        String outputFileName = "lecturesOnly.txt";
        File outputFile = new File(outputFileName);
        
        //Check If The File Already Exists
        int copyNumber = 1;
        
        while (outputFile.exists()) {
            outputFileName = "lecturesOnly - Copy (" + copyNumber + ").txt";
            outputFile = new File(outputFileName);
            copyNumber++;
        }
        
        PrintWriter createTxtFile = new PrintWriter(new FileWriter(outputFileName));
  
        //Print All Online Lectures 
        createTxtFile.println("Online Lectures");
        onlineLectures.forEach(lecture -> createTxtFile.println(lecture));
        createTxtFile.print("\n");
        
        // Print All Lectures With No Labs 
        createTxtFile.println("Lectures with No Lab");
        noLabLectures.forEach(lecture -> createTxtFile.println(lecture));
                
        //Print "lecturesOnly.txt" Amount
        if(copyNumber == 1) {
        	System.out.println("- lecturesOnly.txt is created");
        }
        
        if(copyNumber > 1) {
        	System.out.println("- lecturesOnly - Copy (" + (copyNumber - 1) + ").txt is created");
        }
       
        System.out.println("\n\nGoodbye!");
              
        //Close Scanners To Avoid Memory Leaking 
        scanFile.close();
        scanString.close();
        createTxtFile.close();
        
	} // Main Program Closing Bracket 
	
} // Driver Class Closing Bracket




