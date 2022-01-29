package Model.Types;

import Model.Values.IValue;
import Model.Values.RefValue;

public class RefType implements IType {
    private final IType inner;

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return this.inner;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof RefType) {
            return inner.equals(((RefType) o).getInner());
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        return "Ref(" + this.inner.toString() + ")";
    }

    @Override
    public IValue getDefaultValue() {
        return new RefValue(0, inner);
    }
}
