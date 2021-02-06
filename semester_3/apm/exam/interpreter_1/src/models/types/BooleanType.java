package models.types;

import models.values.BooleanValue;
import models.values.IValue;

public class BooleanType implements IType {
    @Override
    public IValue getDefaultValue() {
        return new BooleanValue(false);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof BooleanType;
    }

    @Override
    public String toString() {
        return "bool";
    }
}
