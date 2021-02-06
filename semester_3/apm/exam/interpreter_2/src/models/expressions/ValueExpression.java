package models.expressions;

import exceptions.ExpressionException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.types.IType;
import models.values.IValue;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) {
        return this.value;
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException {
        return this.value.getType();
    }

    @Override
    public String toString() {
        return String.format("%s", this.value);
    }

    @Override
    public IExpression copy() {
        return new ValueExpression(this.value.copy());
    }
}
