import java.util.Scanner;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.text.DecimalFormat;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Comparator;


public class FinalProject { 
	
	public static void main(String args[]) {
		
		System.out.printf("\t\t\t\tWelcome to my Personal Management Program\n\n");
		System.out.printf("Choose one of the options:\n\n");
		
		String name = "";
		String id = "";
		String rank = "";
		String department = "";
		String status = "";
		String createReport = "";
		
		int creditHours = 0;
		int selection = 0;
		int counterPeople;
		
		double gpa = 0.00;
		
		boolean loop = false;
		
		Scanner stringScanner = new Scanner(System.in);
		Scanner intScanner = new Scanner(System.in);		
				
		University list = new University();
					
		while (!loop) {
			
			try {
				
				System.out.println("1- Enter the information a faculty");
				System.out.println("2- Enter the information of a student");
				System.out.println("3- Print tuition invoice for a student");
				System.out.println("4- Print faculty information");
				System.out.println("5- Enter the information of a staff member");
				System.out.println("6- Print the information of a staff member");
				System.out.println("7- Delete a person");
				System.out.println("8- Exit Program");
				
				
				System.out.print("\n\tEnter your selection: ");
				
				selection = intScanner.nextInt();     
				
				System.out.print("\n\n");
				
				switch(selection){
				
				case 1: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////					
					
					System.out.println("Enter the faculty info: ");			
					
					System.out.print("\t   Name of the faculty: ");
					name = stringScanner.nextLine();
							
					while (true) {
						System.out.print("\t   ID: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("\t   Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					while (true) {
						System.out.print("\t   Rank: ");
						rank = stringScanner.nextLine();
						
						if(rank.compareToIgnoreCase("Professor") == 0) {
							break;
						} else if (rank.compareToIgnoreCase("Adjunct") == 0) {
							break;
						} else {
							System.out.println("\t         \"" + rank + "\" is invalid");
						}
					} // While Loop Ending Bracket
					
					while (true) {
						System.out.print("\t   Department: ");
						department = stringScanner.nextLine();
						
						if(rank.compareToIgnoreCase("Mathematics") == 0) {
							break;
						} else if (department.compareToIgnoreCase("Engineering") == 0) {
							break;
						} else if(department.compareToIgnoreCase("English") == 0) {
							break;
						} else {
							System.out.println("\t               \"" + department + "\" is invalid");
						}
					} // While Loop Ending Bracket
										
					System.out.println("Faculty added!");	
					System.out.print("\n\n\n");
					
					list.addPerson(new Faculty(name, id, department, rank));
					
					break;	
				case 2: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////					
				
					System.out.println("Enter the student info: ");
										
					System.out.print("\t   Name of Student: ");
					name = stringScanner.nextLine();
					
					while (true) {
						System.out.print("\t   ID: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("\t   Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					while (true) {
			            try {
			                System.out.print("\t   Gpa: ");
			                gpa = intScanner.nextDouble();
			                break;
			            } catch (InputMismatchException e) {
			                System.out.println("\t   Invalid input. Please enter a double value.");
			                intScanner.nextLine();
			            }
			        }// While Loop Ending Bracket
					
					while (true) {
			            try {
			            	System.out.print("\t   Credit hours: ");
							creditHours = intScanner.nextInt();
			                break;
			            } catch (InputMismatchException e) {
			                System.out.println("\t   Invalid input. Please enter an integer value.");
			                intScanner.nextLine();
			            }
			        }// While Loop Ending Bracket
						
					System.out.print("Student added!");
					System.out.print("\n\n\n");
					
					list.addPerson(new Student(name, id, gpa, creditHours));
					
					break;
				case 3: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					while (true) {
						System.out.print("Enter the student's id: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					list.printStudent(id);
					
					break;					
				case 4: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									
					while (true) {
						System.out.print("Enter the Faculty's id: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					list.printFaculty(id);
					
					break;
				case 5: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										
					System.out.print("Name of the staff member: ");
					name = stringScanner.nextLine();
					
					while (true) {
						System.out.print("Enter the id: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					while (true) {
						System.out.print("Department: ");
						department = stringScanner.nextLine();
						
						if(rank.compareToIgnoreCase("Mathematics") == 0) {
							break;
						} else if (department.compareToIgnoreCase("Engineering") == 0) {
							break;
						} else if(department.compareToIgnoreCase("English") == 0) {
							break;
						} else {
							System.out.println("\t    \"" + department + "\" is invalid");
						}
					} // While Loop Ending Bracket
					
					while (true) {
						System.out.print("Status, Enter P for Part Time, or Enter F for Full Time: ");
						status = stringScanner.nextLine();
						
						if(status.compareToIgnoreCase("P") == 0) {
							break;
						} else if (status.compareToIgnoreCase("F") == 0) {
							break;
						} else {
							System.out.println("\t    \"" + status + "\" is invalid");
						}
					}// While Loop Ending Bracket
					
					System.out.print("Staff member added!");
					System.out.print("\n\n\n");
					
					list.addPerson(new Staff(name, id, department, status));
						
					break;
				case 6: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					while (true) {
						System.out.print("Enter the Staff's id: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					list.printStaff(id);
					
					break;	
				case 7: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					while (true) {
						System.out.print("Enter the id of the person to delete: ");
                        id = stringScanner.nextLine();
                        if (id.matches("^[a-zA-Z]{2}\\d{4}$")) {
                            break;
                        } else {
                            System.out.println("Invalid ID format. Must be LetterLetterDigitDigitDigitDigit");
                        }
                    }// While Loop Ending Bracket
					
					list.removePerson(id);					
					
					break;
				case 8: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					loop = true;
					System.out.print("\n\n");
					break;
				default:
	                System.out.println("Invalid Value- Please Try Again");
	                System.out.print("\n\n\n");
				}// End Of Switch	
				
			} catch (InputMismatchException e) {
				System.out.print("\n\n");
			    System.out.println("Invalid entry- please try again");
			    System.out.print("\n\n\n");
			    intScanner.next();
			} catch (NoSuchElementException e) {
				System.out.print("\n\n");
			    System.out.println("No such element. Please enter a valid input.");
			    System.out.print("\n\n\n");
			} catch (Exception e) {
				System.out.print("\n\n");
			    System.out.println("An unexpected error occurred. Please try again.");
			    System.out.print("\n\n\n");
			}//  End Of Catch
				
		} // End Of While Loop		
				
		while (true) {
			
			try {
				
				System.out.print("Would you like to create the report? (Y/N): ");
				
				createReport = stringScanner.nextLine();
				
				if(createReport.equalsIgnoreCase("Y")) {
					break;
				} else if (createReport.equalsIgnoreCase("N")) {
					break;
				} else {
					System.out.println("Wrong Input. Please Try Again");
					System.out.print("\n\n");
				}
				
				
			} catch (InputMismatchException e) {
				System.out.print("\n\n");
			    System.out.println("Invalid entry- please try again");
			    System.out.print("\n\n\n");
			    intScanner.next();
			} catch (NoSuchElementException e) {
				System.out.print("\n\n");
			    System.out.println("No such element. Please enter a valid input.");
			    System.out.print("\n\n\n");
			} catch (Exception e) {
				System.out.print("\n\n");
			    System.out.println("An unexpected error occurred. Please try again.");
			    System.out.print("\n\n\n");
			}//  End Of Catch
			
		} // End Of While Loop
		
		
		if (createReport.equalsIgnoreCase("Y")) {
			
			while (true) {
				
				try {
					
					System.out.print("Would like to sort your students by descending gpa or name (1 for gpa, 2 for name): ");
					selection = intScanner.nextInt();
					
					if(selection == 1) {
						break;
					} else if (selection == 2) {
						break;
					} else {
						System.out.println("Wrong Input. Please Try Again");
						System.out.print("\n\n");
					}
					
				} catch (InputMismatchException e) {
					System.out.print("\n\n");
				    System.out.println("Input mismatch. Please enter a valid number.");
				    System.out.print("\n\n\n");
				    intScanner.next();
				} catch (NoSuchElementException e) {
					System.out.print("\n\n");
				    System.out.println("No such element. Please enter a valid input.");
				    System.out.print("\n\n\n");
				} catch (Exception e) {
					System.out.print("\n\n");
				    System.out.println("An unexpected error occurred. Please try again.");
				    System.out.print("\n\n\n");
				}//  End Of Catch
				
			} // End Of While Loop

            Date currentDate = new Date();
            SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
            String formattedDate = dateFormat.format(currentDate);

            // Create a filename with the current date
            String fileName = "report.txt";

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
               
                writer.write("\tReport created on " + formattedDate + "\n");
                writer.write("\t***************************\n\n\n");               
                
                counterPeople = 1;
                
                // Print Faculty Members
                writer.write("Faculty Members\n");
                writer.write("-------------------------\n");
                
                for (Person person : list.getPeople()) {
                    if (person instanceof Faculty) {
                    	writer.write("\t" + counterPeople + ". ");
                    	writer.write(((Faculty) person).writeText());
                    	 writer.write("\n\n");
                        counterPeople++;
                    }
                }
                writer.write("\n\n");                
                
                counterPeople = 1;

                // Print Staff Members
                writer.write("Staff Members\n");
                writer.write("-------------------\n");

                for (Person person : list.getPeople()) {
                    if (person instanceof Staff) {
                    	writer.write("\t" + counterPeople + ". ");
                        writer.write(((Staff) person).writeText());
                        writer.write("\n\n");
                        counterPeople++;
                    }
                }
                writer.write("\n\n");

                counterPeople = 1;

                // Print Students
                writer.write("Students\n");
                writer.write("-----------\n");
 
                for (Person person : list.sortStudents(selection)) {
                	if (person instanceof Student) {
                		writer.write("\t" + counterPeople + ". ");
                        writer.write(((Student) person).writeText());
                        writer.write("\n\n");
                        counterPeople++;
                    }
                }
                writer.write("\n\n");
                

                System.out.println("Report created and saved on your hard drive!");
                
            } catch (IOException e) {
                System.out.println("Error writing to file: " + e.getMessage());
            }//  End Of Catch
            
         
        } else if (createReport.equalsIgnoreCase("N")) {
        	System.out.println("No Report");
        }// End Of If Statement 

		System.out.println("Goodbye!");
		
		stringScanner.close();
		intScanner.close();
		
		//*/
		
		
	} // Main Program Closing Bracket 
} // Public Class Closing Bracket


////////////////////////////////////////////////////////////University Class////////////////////////////////////////////////////////////
class University{
	
	private ArrayList<Person> list;
	
	public University() {
		list = new ArrayList<Person>();
	}
	
	public void addPerson(Person p) {
		list.add(p);
	}
	
	public void removePerson(String id) {
		boolean personFound = false;
		
		
		for (Person person : list) {
	        if (person.getId().equals(id)) {
	            list.remove(person);
	            personFound = true;
	            System.out.print("\n\n\n");
	            break;
	        }
	    }
		
		if (!personFound) {
			System.out.printf("Sorry no such person exists.\n");
			System.out.printf("\n\n");
		}
		
	}
	
	public void printStudent(String id) {
		int counter = 0;
		boolean personFound = false;
		
		
		for (Person person : list) {
	        if (person.getId().equals(id)) {
	        	list.get(counter).tuitionInvoice();
	            personFound = true;
	            break;
	        }
	        counter++;
	    }
		
		if (!personFound) {
			System.out.printf("No student matched!\n");
			System.out.printf("\n\n");
		}
		
	}
	
	public void printStaff(String id) {
		int counter = 0;
		boolean personFound = false;
		
		
		for (Person person : list) {
	        if (person.getId().equals(id)) {
	        	list.get(counter).print();
	            personFound = true;
	            break;
	        }
	        counter++;
	    }
		
		if (!personFound) {
			System.out.printf("No staff member matched!\n");
			System.out.printf("\n\n");
		}
		
	}
	
	public void printFaculty(String id) {
		int counter = 0;
		boolean personFound = false;
		
		
		for (Person person : list) {
	        if (person.getId().equals(id)) {
	        	list.get(counter).print();
	            personFound = true;
	            break;
	        }
	        counter++;
	    }
		
		if (!personFound) {
			System.out.printf("No faculty member matched!\n");
			System.out.printf("\n\n");
		}
		
	}
	

    public ArrayList<Person> getPeople() {
        return list;
    }
	
	public void printUniversity() {
		System.out.println(list);
	}
	
	
	private static double getStudentGpa(Person person) {
        return (person instanceof Student) ? ((Student) person).getGpa() : 0.0;
    }

    private static String getPersonFullName(Person person) {
        return person.getFullName();
    }
	
	public ArrayList<Person> sortStudents(int selection) {
		
		 ArrayList<Person> listTemporary = new ArrayList<>(list);
		 	
		 // Sort By GPA
		 if (selection == 1) {   
			 	listTemporary.sort(Comparator.comparingDouble(University::getStudentGpa).reversed());
	        }
		 
		 //Sort By Name
		 if (selection == 2) {
			 	listTemporary.sort(Comparator.comparing(University::getPersonFullName));
	        }

	        return listTemporary;	
	}
	
	
}


////////////////////////////////////////////////////////////Person Abstract Class//////////////////////////////////////////////////////////// 
abstract class Person{
	
	//Variables 
	private String fullName;
	private String id;
	
	
	// Setters And Getters
	public String getFullName() {
		return fullName;
	}

	public void setFullName(String fullName) {
		this.fullName = fullName;
	}
	
	public String getId() {
		return id;
	}
	
	public void setId(String id) {
		this.id = id;
	}
	
	
	//Constructors
	public Person() {
		fullName = "No Name";
		id = "No Id";
	}
	
	public Person(String fullName, String id) {
		this.fullName = fullName;
		this.id = id;
	}
	
	
	//Methods
	// Print
    public abstract void print();
	
	public void tuitionInvoice() {
		//Auto Method Code
	}
	

	public String writeText() {
		return fullName + "\nID: " + id + "\n";
	}
	
	@Override
	public String toString() {
		return "[Name: " + fullName + "\nId: " + id + "]";
	}
	
}


////////////////////////////////////////////////////////////Employee Abstract Class////////////////////////////////////////////////////////////
abstract class Employee extends Person{
	
	//Variables 
	private String department;

	
	// Setters And Getters
	public String getDepartment() {
		return department;
	}

	public void setDepartment(String department) {
		this.department = department;
	}
	
	
	//Constructors
	public Employee() {
		department = "Unemployed";
	}
		
	public Employee(String fullName, String id, String department) {
		super(fullName, id);
		this.department = department;
	}
	

	//Methods
	@Override
	public String toString() {
		return "[Name: " + super.getFullName() + "Id: " + super.getId() + "Department: " + department + "]";
	}
	
}


////////////////////////////////////////////////////////////Student Class//////////////////////////////////////////////////////////// 
class Student extends Person{
	
	//Variables 
	private double gpa;
	private int takenCreditHours;
	
	
	// Setters And Getters
	public double getGpa() {
		return gpa;
	}

	public void setGpa(double gpa) {
		this.gpa = gpa;
	}

	public int getTakenCreditHours() {
		return takenCreditHours;
	}

	public void setTakenCreditHours(int takenCreditHours) {
		this.takenCreditHours = takenCreditHours;
	}

	
	//Constructors
	public Student() {
		gpa = 0;
		takenCreditHours = 0;
	}
	
	public Student(String fullName, String id) {
        super(fullName, id);
    }
			
	public Student(String fullName, String id, double gpa, int takenCreditHours) {
		super(fullName, id);
		this.gpa = gpa;
		this.takenCreditHours = takenCreditHours;
	}
	
	
	//Methods	
	@Override
	public void print() {
		System.out.print("\n");
		System.out.println("Here is the tuition invoice for " + super.getFullName() + "\n");
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(super.getFullName() + " " + super.getId());
		System.out.println("GPA: " + gpa + " \nCredit Hours: " + takenCreditHours);
		System.out.println("---------------------------------------------------------------------------");
		System.out.print("\n\n\n");
	}
	
	@Override
    public void tuitionInvoice() {
		
		double creditHourCost = 236.45;
		int administrativeFee = 52;
		double gpaDiscount = 0.25;
		double totalPayment = 0.0;
        double discount = 0.0;
        
        totalPayment = (takenCreditHours * creditHourCost) + administrativeFee;
        
        DecimalFormat decimalFormat = new DecimalFormat("#,##0.00");
        String formattedTotalPayment = decimalFormat.format(totalPayment);

        if(gpa >= 3.85){
            discount = totalPayment * gpaDiscount;
            totalPayment = totalPayment - discount; 
        }
        System.out.print("\n");
        System.out.println("Here is the tuition invoice for " + super.getFullName() + ":\n");
        System.out.println("---------------------------------------------------------------------------");
        System.out.println(super.getFullName() + "\t\t\t  " + super.getId());
        System.out.println("Credit Hours: " + takenCreditHours + " ($" + creditHourCost + "/credit hour)");
        System.out.println("Fees: $" + administrativeFee);
        System.out.println("Total payment (after discount): $" + formattedTotalPayment + "\t($" + String.format("%.2f", discount) + " discount applied)");
        System.out.println("---------------------------------------------------------------------------");
        System.out.print("\n\n\n");
    }
	
	@Override
	public String writeText() {
		return super.getFullName() + "\n\tID: " + super.getId() + "\n\tGpa: " + String.format("%.2f", gpa) + "\n\tCredit Hours: " + takenCreditHours ;
	}

	@Override
	public String toString() {
		return "[Name: " + super.getFullName() + ", Id: " + super.getId() + ", GPA: " + gpa + ", Credit Hours Taken: " + takenCreditHours + "]\n";
	}
	
}


////////////////////////////////////////////////////////////Faculty Class////////////////////////////////////////////////////////////
class Faculty extends Employee{
	
	//Variables 
	private String rank;
	
	
	// Setters And Getters
	public String getRank() {
		return rank;
	}

	public void setRank(String rank) {
		this.rank = rank;
	}
	
	
	//Constructors
	public Faculty() {
		rank = "Unemployed";
	}
				
	public Faculty(String fullName, String id, String department, String rank) {
		super(fullName, id, department);
		this.rank = rank;
	}
	
	
	//Methods
	@Override
	public void print() {
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(super.getFullName() + "\t\t" + super.getId());
		System.out.println(super.getDepartment() + " Department, " + rank);
		System.out.println("---------------------------------------------------------------------------");
		System.out.print("\n\n\n");
	}
	
	@Override
	public String writeText() {
		return super.getFullName() + "\n\tID: " + super.getId() + "\n\t" + rank + ", " + super.getDepartment() ;
	}
	
	@Override
	public String toString() {
		return "[Name: " + super.getFullName() + ", Id: " + super.getId() + ", Department: " + super.getDepartment() + ", Rank: " + rank + "]\n";
	}
	
}


////////////////////////////////////////////////////////////Staff Class////////////////////////////////////////////////////////////
class Staff extends Employee{
	
	//Variables 
	private String status;

	
	// Setters And Getters
	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}
	
	
	//Constructors
	public Staff() {
		status = "Unemployed";
	}
					
	public Staff(String fullName, String id, String department, String status) {
		super(fullName, id, department);
		this.status = status;
	}
	
	
	//Methods
	@Override
	public void print() {
		
		if(status.equalsIgnoreCase("P")) {
			status = "Part Time";
		}
		
		if(status.equalsIgnoreCase("F")) {
			status = "Full Time";
		}
		
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(super.getFullName() + "\t\t" + super.getId());
		System.out.println(super.getDepartment() + " Department, " + status);
		System.out.println("---------------------------------------------------------------------------");
		System.out.print("\n\n\n");
	}
	
	@Override
	public String writeText() {
		
		if(status.equalsIgnoreCase("P")) {
			status = "Part Time";
		}
		
		if(status.equalsIgnoreCase("F")) {
			status = "Full Time";
		}	
		
		return super.getFullName() + "\n\tID: " + super.getId() + "\n\t" + super.getDepartment() + ", " + status ;
	}
	
	@Override
	public String toString() {
		return "[Name: " + super.getFullName() + ", Id: " + super.getId() + ", Department: " + super.getDepartment() + ", Status: " + status + "]\n";
	}
	
}
