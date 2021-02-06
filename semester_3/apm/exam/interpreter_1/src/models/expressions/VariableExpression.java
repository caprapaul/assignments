package models.expressions;

import exceptions.ExpressionException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.types.IType;
import models.values.IValue;

public class VariableExpression implements IExpression{
    private final String name;

    public VariableExpression(String name) {
        this.name = name;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) throws ExpressionException {
        IValue value = symbols.get(this.name);

        if (value == null) {
            throw new ExpressionException("Variable '" + this.name + "' not declared.");
        }

        return value;
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException {
        IType type = typeEnv.get(this.name);

        if (type == null) {
            throw new ExpressionException("Variable '" + this.name + "' not declared.");
        }

        return type;
    }

    @Override
    public String toString() {
        return String.format("%s", this.name);
    }

    @Override
    public IExpression copy() {
        return new VariableExpression(this.name);
    }
}
