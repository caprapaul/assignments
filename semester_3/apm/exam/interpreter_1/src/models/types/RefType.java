package models.types;

import models.values.IValue;
import models.values.RefValue;

public class RefType implements IType {
    private final IType inner;

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return this.inner;
    }

    @Override
    public IValue getDefaultValue() {
        return new RefValue(0, this.inner);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof RefType) {
            return this.inner.equals(((RefType) obj).getInner());
        }
        else {
            return false;
        }
    }

    @Override
    public String toString() {
        return String.format("ref %s", this.inner);
    }
}
