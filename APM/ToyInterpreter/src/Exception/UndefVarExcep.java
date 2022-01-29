package Exception;

public class UndefVarExcep extends Exception {
    public UndefVarExcep() {
        super("Variable not defined");
    }

    public UndefVarExcep(String message) {
        super(message);
    }
}
