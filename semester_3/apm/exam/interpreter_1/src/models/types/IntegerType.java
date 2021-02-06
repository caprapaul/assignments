package models.types;

import models.values.IValue;
import models.values.IntegerValue;

public class IntegerType implements IType {
    @Override
    public IValue getDefaultValue() {
        return new IntegerValue(0);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof IntegerType;
    }

    @Override
    public String toString() {
        return "int";
    }
}
