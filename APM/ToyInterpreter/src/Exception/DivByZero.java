package Exception;

public class DivByZero extends Exception {
    public DivByZero() {
        super("Division by zero");
    }

    public DivByZero(String message) {
        super(message);
    }
}
