package Exception;

public class FullADTExcep extends Exception{
    public FullADTExcep() {
        super("Container is full");
    }

    public FullADTExcep(String message) {
        super(message);
    }
}
