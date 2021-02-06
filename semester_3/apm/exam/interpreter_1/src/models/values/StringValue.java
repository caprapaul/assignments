package models.values;

import models.types.IType;
import models.types.StringType;
import utils.IInto;

public class StringValue implements IValue, IInto<String> {
    private final String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue copy() {
        return new StringValue(this.value);
    }

    @Override
    public String into() {
        return this.value;
    }

    @Override
    public String toString() {
        return String.format("\"%s\"", this.value);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof StringValue && ((StringValue) obj).into().equals(this.value);
    }
}
