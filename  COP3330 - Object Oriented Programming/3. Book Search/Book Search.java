import java.util.Scanner;
import java.util.Random;

public class Main {
	
	public static void main(String args[]) {
		
		
		int loop = 0;
		int index = 0;
		int deduction = 0;
		double bookPrice = 0;
		String createObject;
		BookList list = new BookList();
		String bookInfo;
		String[] infoSplit;
		Scanner input = new Scanner(System.in);
		Scanner inputNumber = new Scanner(System.in);
		String splitInt;
		String[] splittedInt;
		
		System.out.println("Welcome to the book program!\n");
		
		//______________________________________________________________________________________________________________________\\
		while(loop != 1) {
			
			System.out.print("Would you like to create a book object? (yes/no): ");
			
			//______________________________________________________________________________________________________________________\\
			while(loop != 1) {
				
				createObject = input.nextLine();
				
				System.out.print("\n");
				
				if(createObject.compareToIgnoreCase("YES") == 0) {
					loop = 0;
					break;
				}
				else if(createObject.compareToIgnoreCase("NO") == 0) {
					loop = 1;
					
					System.out.print("Sure!");
					System.out.print("\n\n\n\n");
					
					break;
				} 
				else {
					System.out.print("I'm sorry but " + createObject + " isn't a valid answer. Please enter either yes or no: ");
				}
			}
			
			//______________________________________________________________________________________________________________________\\
			if(loop == 0) {
				
			System.out.print("Please enter the author, title and the isbn of the book separated by /: ");	
			
			bookInfo = input.nextLine();
			infoSplit = bookInfo.split("/");
			
			System.out.print("\nGot it!\n\n");
			
			System.out.print("Now, tell me if it is a bookstore book or a library book (enter BB for bookstore book or LB for library book): ");
			
			//______________________________________________________________________________________________________________________\\
			while(loop != 1) {
				
				createObject = input.nextLine();
				
				System.out.print("\n");
				
				//______________________________________________________________________________________________________________________\\
				if(createObject.compareToIgnoreCase("BB") == 0) {
					
					System.out.print("Got it!\n\n");
					
					System.out.print("Please enter the list price of " + infoSplit[1].toUpperCase() + " by " + infoSplit[0].toUpperCase() + ": ");
					
					bookPrice = inputNumber.nextDouble();
					
					System.out.print("\n");
					
					list.addBook(new BookstoreBook(infoSplit[0], infoSplit[1], infoSplit[2], bookPrice));
					
					System.out.print("Is it on sale? (y/n): ");
					
					//______________________________________________________________________________________________________________________\\
					while(loop != 1) {
						
						createObject = input.nextLine();
						
						System.out.print("\n");
						
						if(createObject.compareToIgnoreCase("Y") == 0) {
							
							list.getBook(index).setBookOnSale(true);
							
							System.out.print("Deduction percentage: ");
							
							splitInt = input.nextLine();
							splittedInt = splitInt.split("%");
							deduction = Integer.parseInt(splittedInt[0]);
							
							System.out.print("\n");
							
							list.getBook(index).setBookPrice(list.getBook(index).bookOnSale(list.getBook(index).isBookOnSale(), deduction));
							
							System.out.print("Got it!\n");
							
							System.out.print("\n\nHere is your bookstore book information\n");
							System.out.println(list.getBook(index).toString() + "\n \n");
							
							break;
						}
						
						else if(createObject.compareToIgnoreCase("N") == 0) {
							
							System.out.print("Got it!\n");
							
							System.out.print("\n\nHere is your bookstore book information\n");
							System.out.println(list.getBook(index).toString() + "\n \n");
							
							break;
						} 
						
						else {
							System.out.print("I'm sorry but " + createObject + " isn't a valid answer. Please enter either y or n: ");
						}
						
					}	
					
					index++;
					
					break;
				}
				
				//______________________________________________________________________________________________________________________\\
				else if(createObject.compareToIgnoreCase("LB") == 0) {
					
					list.addBook(new LibraryBook(infoSplit[0], infoSplit[1], infoSplit[2]));
					
					list.getBook(index).setCallNumber(list.getBook(index).callNumbers(infoSplit[0], infoSplit[2]));
					
					System.out.print("\nHere is your library book information\n");
					System.out.println(list.getBook(index).toString() + "\n \n");
					
					index++;
					
					break;
				} 
				else {
					System.out.print("Oops! That's not a valid entry. Please try again: ");
				}
			}
			
			
			
				
			}
			
			//______________________________________________________________________________________________________________________\\
			if(loop == 1) {
				
				
				list.printBooks();
				
				System.out.print("Take care now! ");
				
				
			}
			
			
			
		}
	
		//
		
	}
}


//______________________________________________________________________________________________________________________\\
abstract class Book {
	
	private String author;
	private String title;
	private String isbn;
	
	
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getIsbn() {
		return isbn;
	}
	public void setIsbn(String isbn) {
		this.isbn = isbn;
	}	
	
	abstract public void setBookPrice(double bookPrice);
	abstract public void setBookOnSale(boolean bookOnSale);
	abstract public boolean isBookOnSale();
	abstract public double bookOnSale(boolean bookOnSale, int deduction);
	
	abstract public void setCallNumber(String callNumber);
	abstract public String callNumbers( String author, String isbn); 
	
	public Book() {
		author = "No Name";
		title = "No Title";
		isbn = "No Isbn";
	}
	
	public Book(String isbn) {
		this.isbn = isbn;
	}
	
	public Book(String author, String title, String isbn) {
		this.author = author;
		this.title = title;
		this.isbn = isbn;
	}
	
	@Override
	public String toString() {
		return "Book\n " + "\nAuthor: " + author + "\nTitle: " + title + "\nIsbn: " + isbn;  
	}
	
}


//______________________________________________________________________________________________________________________\\
class BookstoreBook extends Book {
	
	private double bookPrice;
	private double oldPrice;
	private boolean bookOnSale = false;	
	
	
	public double getBookPrice() {
		return bookPrice;
	}
	public void setBookPrice(double bookPrice) {
		this.bookPrice = bookPrice;
	}
	public boolean isBookOnSale() {
		return bookOnSale;
	}
	public void setBookOnSale(boolean bookOnSale) {
		this.bookOnSale = bookOnSale;
	}
	public double getOldPrice() {
		return oldPrice;
	}
	public void setOldPrice(double oldPrice) {
		this.oldPrice = oldPrice;
	}
	
	@Override 
	public double bookOnSale(boolean bookOnSale, int deduction) {
		
		if(bookOnSale == true) {
			return (bookPrice * ( 1 - ((double)deduction/100)));
		} 
		
		return bookPrice;
	}
	
	
	public BookstoreBook() {
		bookPrice = 0;
	}
	
	public BookstoreBook(double bookPrice) {
		this.bookPrice = bookPrice;
	}
	
	public BookstoreBook(String author, String title, String isbn, double bookPrice) {
		super(author, title, isbn);
		this.bookPrice = bookPrice;
		oldPrice = bookPrice;
	}
	
	@Override
	public String toString() {
		
		String formattedBookPrice = String.format("%.02f", getBookPrice());
		
		return "[" + getIsbn() + "-" + getTitle().toUpperCase() + " by " + getAuthor().toUpperCase() + ", $"  + getOldPrice() + " listed for $" + formattedBookPrice + "]";
	}
	
	@Override
	public String callNumbers(String author, String isbn) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public void setCallNumber(String callNumber) {
		// TODO Auto-generated method stub
		
	}
	
}


//______________________________________________________________________________________________________________________\\
class LibraryBook extends Book {
	
	private String callNumber;
	private int floorNumber;
	
	
	public String getCallNumber() {
		return callNumber;
	}
	public void setCallNumber(String callNumber) {
		this.callNumber = callNumber;
	}
	public int getFloorNumber() {
		return floorNumber;
	}
	public void setFloorNumber(int floorNumber) {
		this.floorNumber = floorNumber;
	}

	
	public LibraryBook() {
		callNumber = "No Call Number";
	}
	
	public LibraryBook(String callNumber) {
		this.callNumber = callNumber;
	}
	
	public LibraryBook(String author, String title, String isbn) {
		super(author, title, isbn);
	}
	
	public String callNumbers( String author, String isbn) {
		
		Random rand = new Random(); 
		
		floorNumber =  rand.nextInt(100);
		
		String formattedFloorNumber = String.format("%02d", floorNumber);
		
		return formattedFloorNumber + "." + author.substring(0, 3) + "." + isbn.substring(isbn.length()-1);
	}
	
	@Override
	public String toString() {
		return "[" + getIsbn() + "-" + getTitle().toUpperCase() + " by " + getAuthor().toUpperCase() + "-" + getCallNumber().toUpperCase() + "]";                                    
	}
	
	
	
	@Override
	public void setBookOnSale(boolean bookOnSale) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public boolean isBookOnSale() {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public void setBookPrice(double bookPrice) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public double bookOnSale(boolean bookOnSale, int deduction) {
		// TODO Auto-generated method stub
		return 0;
	}

}


//______________________________________________________________________________________________________________________\\
class BookList {
	
	private Book [] list;
	
	
	public BookList() {
		
		list = new Book[100];
		
		for (int index = 0; index < 100; index++) {
			list[index] = null;
		}
	
	}

	
	public void addBook(Book book) {
		
		boolean full = true;
		
		for(int index = 0; index < 100; index++) {
			if(list[index] == null) {
				list[index] = book;
				full = false;
				break;
			}
		}
		
		if(full) {
			System.out.println("sorry we can't add more books");
		}
	}
	
	
	public Book getBook(int index) {
		
        if (index >= 0 && index < 100) {
            return list[index];
        } else {
            return null;
        }
        
    }
	
	
	public void printBooks() {
		
		int index = 0;
		
		System.out.println("Here are all your books...\n");
		
		for(Book e : list) {
			if(e instanceof LibraryBook) {
				 index++;
			} 
		}
		
		System.out.println("Library Books (" + index + ")\n");
		
		for(Book e : list) {
			if(e instanceof LibraryBook) {
				 System.out.println(e);
			} 
		}
		
		System.out.println("\n_ _ _ _\n");
		
		index = 0;
		
		for(Book e : list) {
			if(e instanceof BookstoreBook) {
				 index++;
			} 
		}
		
		System.out.println("Bookstore Books (" + index + ")\n");
		
		for(Book e : list) {
			if(e instanceof BookstoreBook) {
				 System.out.println(e);
			} 
		}
		
		System.out.println("\n_ _ _ _\n");
		
	}
	
	
	
}

