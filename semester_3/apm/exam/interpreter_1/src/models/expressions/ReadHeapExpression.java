package models.expressions;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.types.IType;
import models.types.RefType;
import models.values.IValue;
import models.values.RefValue;

public class ReadHeapExpression implements IExpression {
    private final IExpression expression;

    public ReadHeapExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) throws ExpressionException {
        IValue expressionValue = this.expression.evaluate(symbols, heap);

        if (!(expressionValue instanceof RefValue)) {
            throw new ExpressionException("Expression '" + this.expression + "' does not evaluate to a reference.");
        }

        RefValue ref = (RefValue)expressionValue;
        IValue value = heap.get(ref.getAddress());

        if (value == null) {
            throw new ExpressionException("Unallocated address: '" + ref.getAddress() + "'.");
        }

        return value;
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException {
        IType type = this.expression.typeCheck(typeEnv);

        if (!(type instanceof RefType)) {
            throw new ExpressionException("Expression '" + this.expression + "' does not evaluate to a reference.");
        }

        RefType refType = (RefType)type;
        return refType.getInner();
    }

    @Override
    public IExpression copy() {
        return new ReadHeapExpression(this.expression.copy());
    }

    @Override
    public String toString() {
        return String.format("readHeap(%s)", this.expression);
    }
}
