package views.commands;

import controllers.Controller;
import exceptions.InterpreterException;

public class RunExampleCommand extends Command {
    private final Controller controller;

    public RunExampleCommand(String key, String description, Controller controller){
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            this.controller.run();
        }
        catch (InterpreterException e) {
            System.out.println(e.getMessage());
        }
    }
}
