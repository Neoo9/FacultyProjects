package Exception;

public class IOException extends Exception {
    public IOException() {
        super("Input/Output error");
    }

    public IOException(String message) {
        super(message);
    }
}
