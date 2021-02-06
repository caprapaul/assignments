package models.values;

import utils.IInto;
import models.types.BooleanType;
import models.types.IType;

public class BooleanValue implements IValue, IInto<Boolean> {
    private final boolean value;

    public BooleanValue(boolean value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new BooleanType();
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override
    public Boolean into() {
        return this.value;
    }

    @Override
    public IValue copy() {
        return new BooleanValue(this.value);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof BooleanValue && ((BooleanValue) obj).into() == this.value;
    }
}
