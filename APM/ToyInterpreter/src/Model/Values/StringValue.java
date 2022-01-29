package Model.Values;

import Model.Types.IType;
import Model.Types.StringType;

import java.util.Objects;

public class StringValue implements IValue {
    private final String value;

    public StringValue() {
        this.value = "";
    }

    public StringValue(String v) {
        this.value = v;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != this.getClass())
            return false;
        StringValue o_value = (StringValue) o;
        return Objects.equals(o_value.value, this.value);
    }

    @Override
    public String toString() {
        return this.value;
    }

    public String getValue() {
        return this.value;
    }
}
