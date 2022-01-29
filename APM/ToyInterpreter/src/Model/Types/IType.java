package Model.Types;

import Model.Values.IValue;

public interface IType {
    boolean equals(Object o);

    String toString();

    IValue getDefaultValue();
}
