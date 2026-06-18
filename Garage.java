import java.util.Scanner;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

public class Garage {
    private static Scanner scanner = new Scanner(System.in);
    private static Random random = new Random();

    //upgradable
    public static int garageSpaces = 10;
    public static int maxGarageTime = 2;
    public static double parkingFee = 5.00;

    //statistics
    public static int garageLevel = 1;
    public static double garageMoney = 0;
    public static double garageRevenue = 0;

    private static final String ALPHA_NUMERIC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    public static String generateLicense() {
        StringBuilder sb = new StringBuilder(6);
        
        for (int i = 0; i < 6; i++) {
            int index = random.nextInt(ALPHA_NUMERIC.length());
            sb.append(ALPHA_NUMERIC.charAt(index));
        }
        return sb.toString();
    }

    private static ArrayList<Car> parkedCars = new ArrayList<>();
    static class Car {
        String license;
        int time;
        public Car() {
            this.license = generateLicense();
            this.time = random.nextInt(0, maxGarageTime) + 1;

            garageMoney += this.time * parkingFee;
        }

        public boolean update() {
            this.time--;
            if(this.time <= 0) {
                return true;
            }
            return false;
        }
    }

    public static void main(String[] args) {
        boolean continueLoop = true;

        while (continueLoop) {
            System.out.print("=== Parking Garage ===\n\n1. View Garage Status\n2. View Parked Cars\n3. Next Hour\n4. Exit\n\n> ");
            String command = scanner.nextLine().toLowerCase();
            
            switch(command) {
                case "view garage status":
                case "1":
                    System.out.println("Total Spaces: " + garageSpaces + "\nOccupied Spaces: " + parkedCars.size() + "\nAvailable Spaces: " + (garageSpaces - parkedCars.size()));
                    break;

                case "view parked cars":
                case "2":
                    String carText = "";
                    for(int i=0; i < parkedCars.size(); i++) {
                        Car car = parkedCars.get(i);
                        carText += "\n" + (i + 1) + ". " + car.license + " | " + car.time + " hr.";
                    }

                    System.out.println("Parked Cars:\n" + carText);
                    break;

                case "next hour":
                case "3":
                    Iterator<Car> iterator = parkedCars.iterator();
                    while (iterator.hasNext()) {
                        Car car = iterator.next();
                        boolean carRemove = car.update();

                        if(carRemove == true) {
                            iterator.remove();
                        }
                    }
                    
                    int carsEntering = random.nextInt(garageLevel * 5) + 1;
                    int availableSpaces = garageSpaces - parkedCars.size();
                    if(availableSpaces >= carsEntering) {
                        for(int i=0; i < carsEntering; i++) {
                            parkedCars.add(new Car());
                        }

                        System.out.println(carsEntering + " cars have entered the garage.");
                    } else {
                        for(int i=0; i < availableSpaces; i++) {
                            parkedCars.add(new Car());
                        }

                        System.out.println(availableSpaces + " out of " + carsEntering + " cars have entered the garage due to no space.");
                    }
                    break;
                
                case "exit":
                case "4":
                    continueLoop = false;
                    System.out.println("Exited instance.");
                    break;

                default:
                    System.out.println("Not a command...");
                    break;
            }

            System.out.println("\nPress [enter] to continue...");
            scanner.nextLine();
        }

        scanner.close();
    }
}