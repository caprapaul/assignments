package models.values;

import utils.IInto;
import models.types.IType;
import models.types.IntegerType;

public class IntegerValue implements IValue, IInto<Integer> {
    private final int value;

    public IntegerValue(int value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new IntegerType();
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override
    public Integer into() {
        return this.value;
    }

    @Override
    public IValue copy() {
        return new IntegerValue(this.value);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof IntegerValue && ((IntegerValue) obj).into() == this.value;
    }
}
