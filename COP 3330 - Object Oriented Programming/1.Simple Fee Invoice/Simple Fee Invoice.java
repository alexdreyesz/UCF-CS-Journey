/*
COP3330 Fall 2023 Unit1_HW1
Copyright 2023 Alex Reyes
*/

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		
		String FullName, StudentId, Input1, Input2;
		int CourseNumber1, CourseNumber2, CreditHour1, CreditHour2;
		String Items1[], Items2[];
		double CreditHourPrice = 120.25, HealthFee = 35.00; 
		
		Scanner myscan = new Scanner(System.in);
		
		System.out.print("Enter the Student’s Id: ");
		StudentId = myscan.nextLine();
		
		System.out.print("Enter the Student’s full name: ");
		FullName = myscan.nextLine();
		
		System.out.print("\n");
				
		System.out.print("Enter crn/credit hours for the first class like (CRN/CreditHours): ");
		Input1 = myscan.nextLine();
		Items1 = Input1.split("/");
		
		CourseNumber1 = Integer.parseInt(Items1[0]);
		CreditHour1 = Integer.parseInt(Items1[1]);
		
		System.out.print("Enter crn/credit hours for the second class like (CRN/CreditHours): ");
		Input2 = myscan.nextLine();
		Items2 = Input2.split("/");
		
		CourseNumber2 = Integer.parseInt(Items2[0]);
		CreditHour2 = Integer.parseInt(Items2[1]);
		
		double CourseTotal1 = CreditHourPrice * CreditHour1; 
		double CourseTotal2 = CreditHourPrice * CreditHour2; 
		
		System.out.print("\n");
		
		System.out.println("Thank you!");
		System.out.println("Fee invoice prepared for: " + FullName);
		
		System.out.print("\n");
		System.out.println("               SIMPLE COLLEGE");
		System.out.println("               ORLANDO FL 10101");
		System.out.println("               *************************\n");
		System.out.println("               Fee Invoice Prepared for:");
		System.out.println("               [" + FullName + "]" + "[" + StudentId + "]" + "\n");
		System.out.println("               1 Credit Hour = $" + CreditHourPrice + "\n");
		System.out.println("               CRN       CREDIT HOURS");
		System.out.printf("               %-10d%-15d      $%-10.2f\n", CourseNumber1, CreditHour1, CourseTotal1);
		System.out.printf("               %-10d%-15d      $%-10.2f \n \n ", CourseNumber2, CreditHour2, CourseTotal2);
		System.out.println("                        Health & id fees" + "     $" + HealthFee + "\n");
		System.out.println("               ----------------------------------------");
		System.out.printf("                         Total Payments       $%.2f\n", (CourseTotal1 + CourseTotal2 + HealthFee));
	}
}
