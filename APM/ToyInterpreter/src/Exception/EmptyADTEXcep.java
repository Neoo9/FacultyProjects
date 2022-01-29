package Exception;

public class EmptyADTEXcep extends Exception {
    public EmptyADTEXcep() {
        super("Container is empty");
    }

    public EmptyADTEXcep(String msg) {
        super(msg);
    }
}
