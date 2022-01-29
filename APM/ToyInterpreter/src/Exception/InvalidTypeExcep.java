package Exception;

public class InvalidTypeExcep extends Exception {
    public InvalidTypeExcep() {
        super("Invalid type");
    }

    public InvalidTypeExcep(String message) {
        super(message);
    }
}
