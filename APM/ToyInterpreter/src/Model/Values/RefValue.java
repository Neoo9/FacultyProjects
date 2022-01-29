package Model.Values;

import Model.Types.IType;
import Model.Types.RefType;

public class RefValue implements IValue {
    private final int address;
    private final IType locationType;

    public RefValue(int addr, IType loc) {
        this.address = addr;
        this.locationType = loc;
    }

    public int getAddress() {
        return this.address;
    }

    public IType getLocationType() {
        return this.locationType;
    }

    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString() {
        return "(" + this.address + ", " + this.locationType.toString() + ")";
    }
}
