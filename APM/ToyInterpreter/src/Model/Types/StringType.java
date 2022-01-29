package Model.Types;


import Model.Values.IValue;
import Model.Values.StringValue;

public class StringType implements IType {

    @Override
    public IValue getDefaultValue() {
        return new StringValue();
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof StringType);
    }

    @Override
    public String toString() {
        return "String";
    }
}
