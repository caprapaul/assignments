package models.values;

import models.types.IType;
import utils.ICopy;

public interface IValue extends ICopy<IValue> {
    IType getType();
}
