import java.util.Scanner;

public class hello {
    static char gradeFunction(double avg) {
        if (avg >= 90) return 'A';
        else if(avg >= 80) return 'B';
        else if (avg >= 70) return 'C';
        else if (avg >= 60) return 'D';
        else return 'F';
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("How many grades? (1 to 5) ");
        int count = scanner.nextInt();

        if(count < 1 || count > 5) {
            System.out.print("Sorry, try again.");
            scanner.close();
            return;
        }

        double sum = 0.0;
        for(int i=1;i<=count;i++) {
            System.out.print("Enter grade " + i + ": ");
            double grade = scanner.nextDouble();
            sum += grade;
        }

        double avg = sum / count;
        System.out.println("Average: " + avg);
        System.out.println("Grade Average: " + gradeFunction(avg));

        scanner.close();
    }
}