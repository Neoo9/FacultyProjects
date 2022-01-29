package Model.Values;

import Model.Types.IType;
import Model.Types.IntType;

public class IntValue implements IValue {

    private final int value;

    public IntValue() {
        this.value = 0;
    }

    public IntValue(int i) {
        this.value = i;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != this.getClass())
            return false;
        IntValue o_value = (IntValue) o;
        return o_value.value == this.value;
    }

    @Override
    public String toString() {
        return Integer.toString(this.value);
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    public int getValue() {
        return this.value;
    }

}
