/*
Asks the user to enter up to 5 items they need to buy
Stores the items in an array
Prints the full shopping list
Counts how many items were entered
*/
import java.util.Scanner;

public class list {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("How many items? ");
        int count = scanner.nextInt();

        String[] items = new String[count];
        for(int i=1;i<=count;i++) {
            System.out.print("Item name: ");
            String item = scanner.next();
            items[i-1] = item;
        }

        System.out.print("(" + items.length + ") " + String.join(", ", items));
        scanner.close();
    }
}