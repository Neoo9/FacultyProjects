package Model.Types;

import Model.Values.BoolValue;
import Model.Values.IValue;

public class BoolType implements IType {
    @Override
    public IValue getDefaultValue() {
        return new BoolValue();
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof BoolType);
    }

    @Override
    public String toString() {
        return "bool";
    }
}
