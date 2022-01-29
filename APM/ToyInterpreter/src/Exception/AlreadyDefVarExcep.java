package Exception;

public class AlreadyDefVarExcep extends Exception {
    public AlreadyDefVarExcep() {
        super("Variable is already defined");
    }

    public AlreadyDefVarExcep(String message) {
        super(message);
    }
}
