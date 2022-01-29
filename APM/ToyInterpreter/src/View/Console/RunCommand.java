package View;

import Controller.Controller;

public class RunCommand extends Command {
    private final Controller cont;

    public RunCommand(String key, String desc, Controller ct) {
        super(key, desc);
        cont = ct;
    }

    @Override
    public void execute() {
        try {
            cont.allStep();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
