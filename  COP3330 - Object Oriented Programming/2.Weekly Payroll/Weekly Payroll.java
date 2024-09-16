/*
COP 3330 Fall Unit4_HW_2
Copyright 2023 Alex Reyes
*/

import java.util.ArrayList;

public class DriverClass {

    public static void main(String[] args) {

    	String fullName = "Erika T. Jones";
        String employeeNumber = "ej789";
        double payRate = 100.0, hoursWorked = 1.0;

        Employee e = new Employee(fullName, employeeNumber, payRate, hoursWorked);

        System.out.println(e);
        
        e.printCheck();

        Company company = new Company();

        company.hire(new Employee("Saeed Happy", "sh895", 2, 200));
        company.hire(e);
        
        company.printCompanyInfo();

        company.hire(new Employee("Enrico Torres", "et897", 3, 150));

        company.printCheck("ab784");

        company.deleteEmployeesBySalary(256.36);

        company.reverseEmployees();

        System.out.println(company.searchByName("WaLiD WiLLiAms"));

        company.printEmployees();

        System.out.println("Bye!");
    }
}

class Employee {
    private String fullName;
    private String employeeNumber;
    private double payRate;
    private double hoursWorked;

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public String getEmployeeNumber() {
        return employeeNumber;
    }

    public void setEmployeeNumber(String employeeNumber) {
        this.employeeNumber = employeeNumber;
    }

    public double getPayRate() {
        return payRate;
    }

    public void setPayRate(double payRate) {
        this.payRate = payRate;
    }

    public double getHoursWorked() {
        return hoursWorked;
    }

    public void setHoursWorked(double hoursWorked) {
        this.hoursWorked = hoursWorked;
    }

    public Employee() {
        fullName = "No Name";
        employeeNumber = "No Employee Number";
        payRate = -1;
        hoursWorked = -1;
    }

    public Employee(String aFullName, String aEmployeeNumber, double aPayRate, double aHoursWorked) {
        fullName = aFullName;
        employeeNumber = aEmployeeNumber;
        payRate = aPayRate;
        hoursWorked = aHoursWorked;
    }
    
    public Employee(String aFullName, String aEmployeeNumber) {
        fullName = aFullName;
        employeeNumber = aEmployeeNumber;
    }
    
    public Employee(double aPayRate, double aHoursWorked) {
        payRate = aPayRate;
        hoursWorked = aHoursWorked;
    }

    @Override
    public String toString() {
        return employeeNumber + "/" + fullName + ", " + String.format("%.2f", hoursWorked) + " @ " + String.format("%.2f", payRate);
    }

    public double salary() {
        return payRate * hoursWorked;
    }

    public double taxDeductions() {
        return salary() * 0.06;
    }

    public double netPay() {
        return salary() - taxDeductions();
    }

    public void printCheck() {
        
        System.out.println(" ");
        System.out.println("-------------------------------------------------------");
        System.out.println("\tEmployee's Name: \t" + fullName);
        System.out.printf("\tEmployee's Number: \t%s\n", employeeNumber);
        System.out.println("\tHourly rate of pay: \t" + String.format("%.2f", payRate));
        System.out.println("\tHours worked: \t\t" + String.format("%.2f", hoursWorked) + "\n");

        System.out.println("\tTotal Gross Pay:        " + String.format("%.2f", salary()) + "\n");

        System.out.println("\tDeductions: \t\t" + String.format("%.2f", taxDeductions()));
        System.out.println("\tNet Pay: \t\t" + String.format("%.2f", netPay()) + "\n");

        System.out.println("-------------------------------------------------------");
        System.out.println(" ");
    }
}

class Company {

    private ArrayList<Employee> employeeList;
    private String companyName;
    private static String companyTaxId;
    
     public String getCompanyName() {
		return companyName;
	}

	public void setCompanyName(String companyName) {
		this.companyName = companyName;
	}
	
	public static String getCompanyTaxId() {
		return companyTaxId;
	}

	public static void setCompanyTaxId(String nCompanyTaxId) {
		nCompanyTaxId = companyTaxId;
	}

    public Company() {
        employeeList = new ArrayList<>();
        companyName = "People's Place";
        companyTaxId = "v1rtua7C0mpan1";
    }

    public boolean hire(Employee employee) {
        for (Employee emp : employeeList) {
            if (emp.getEmployeeNumber().equals(employee.getEmployeeNumber())) {
                return false;
            }
        }
        employeeList.add(employee);
        return true;
    }

    public void printCompanyInfo() {
        System.out.println("Company Name: " + companyName);
        System.out.println("Tax ID: " + companyTaxId);
        System.out.println("Number of Employees: " + employeeList.size());
    }

    public void printEmployees() {
        System.out.println("\nLIST OF EMPLOYEES:");
        for (Employee employee : employeeList) {
            System.out.println(employee);
        }
    }

    public int countEmployees(double maxSalary) {
        int count = 0;
        
        for (Employee employee : employeeList) {
            if (employee.salary() < maxSalary) {
                count++;
            }
        }
        System.out.println(" ");
        return count;
    }

    public boolean searchByName(String fullName) {
        for (Employee employee : employeeList) {
            if (employee.getFullName().equalsIgnoreCase(fullName)) {
                System.out.println(" ");
                return true;
            }
        }
        System.out.println(" ");
        return false;
    }

    public void reverseEmployees() {
        int size = employeeList.size();
        
        for (int i = 0; i < size / 2; i++) {
            Employee temp = employeeList.get(i);
            employeeList.set(i, employeeList.get(size - i - 1));
            employeeList.set(size - i - 1, temp);
        }
    }
    

    public void deleteEmployeesBySalary(double targetSalary) {
        int i = 0;
    
        while ( i < employeeList.size()) {
            Employee employee = employeeList.get(i);
        if (employee.salary() == targetSalary) {
            employeeList.remove(i);
        } else {
            i++;
            }
        }
    }

    public void printCheck(String employeeNumber) {
        boolean found = false;
        
        for (Employee employee : employeeList) {
            if (employee.getEmployeeNumber().equals(employeeNumber)) {
                employee.printCheck();
                found = true;
                break;
            }
        }
        if (found == false) {
            System.out.println(" ");
            System.out.println("NO SUCH EMPLOYEE EXISTS");
        }
    }
}
