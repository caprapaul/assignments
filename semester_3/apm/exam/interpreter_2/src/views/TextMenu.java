package views;

import views.commands.Command;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private final Map<String, Command> commands;

    public TextMenu() {
        this.commands = new HashMap<>();
    }

    private void printMenu() {
        for (Command command : this.commands.values()) {
            String line=String.format("%4s. %s", command.getKey(), command.getDescription());
            System.out.println(line);
        }
    }

    public void addCommand(Command command) {
        this.commands.put(command.getKey(), command);
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);

        while(true) {
            this.printMenu();

            System.out.println("Input option: ");
            String key = scanner.nextLine();
            Command command = this.commands.get(key);

            if (command==null) {
                System.out.println("Invalid option.");
                continue;
            }

            command.execute();
        }
    }
}
