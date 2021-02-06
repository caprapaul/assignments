package models.values;

import models.types.IType;
import models.types.RefType;

public class RefValue implements IValue {
    private final int address;
    private final IType type;

    public RefValue(int address, IType type) {
        this.address = address;
        this.type = type;
    }

    public int getAddress() {
        return this.address;
    }

    @Override
    public IType getType() {
        return new RefType(this.type);
    }

    @Override
    public IValue copy() {
        return new RefValue(this.address, this.type);
    }

    @Override
    public String toString() {
        return String.format("(%s, %s)" , this.address, this.type);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof RefValue)) {
            return false;
        }

        RefValue refObj = ((RefValue) obj);

        return refObj.address == this.address && refObj.type.equals(this.type);
    }
}
