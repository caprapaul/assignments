package models.types;

import models.values.IValue;
import models.values.StringValue;

public class StringType implements IType {
    @Override
    public IValue getDefaultValue() {
        return new StringValue("");
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof StringType;
    }

    @Override
    public String toString() {
        return "string";
    }
}
