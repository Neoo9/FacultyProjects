package Model.Types;

import Model.Values.IValue;
import Model.Values.IntValue;

public class IntType implements IType {
    @Override
    public IValue getDefaultValue() {
        return new IntValue();
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof IntType);
    }

    @Override
    public String toString() {
        return "int";
    }

}
