package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.expressions.IExpression;
import models.types.IType;
import models.types.RefType;
import models.values.IValue;
import models.values.RefValue;

public class WriteHeapStatement implements IStatement{
    private final String variableName;
    private final IExpression expression;

    public WriteHeapStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        IHeap<IValue> heap = state.getHeap();
        IValue variableValue = symbols.get(this.variableName);

        if (variableValue == null) {
            throw new StatementException("Variable '" + this.variableName + "' not declared.");
        }

        IType variableType = variableValue.getType();
        IValue expressionValue = this.expression.evaluate(symbols, heap);
        IType expressionType = expressionValue.getType();

        if (!variableType.equals(new RefType(expressionType))) {
            throw new StatementException("Cannot assign value of type '" + new RefType(expressionType) +
                    "' to variable of type '" + variableType + "'.");
        }

        RefValue ref = (RefValue)variableValue;
        IValue value = heap.get(ref.getAddress());

        if (value == null) {
            throw new StatementException("Unallocated address: '" + ref.getAddress() + "'.");
        }

        heap.update(ref.getAddress(), expressionValue)  ;

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType variableType = typeEnv.get(this.variableName);
        IType expressionType = this.expression.typeCheck(typeEnv);

        if (!variableType.equals(new RefType(expressionType)))
        {
            throw new StatementException(String.format(
                    "Cannot assign value of type '%s' to variable of type '%s'.",
                    new RefType(expressionType),
                    variableType
            ));
        }

        return typeEnv;
    }


    @Override
    public IStatement copy() {
        return new WriteHeapStatement(this.variableName, this.expression.copy());
    }

    @Override
    public String toString() {
        return String.format("writeHeap(%s, %s)", this.variableName, this.expression);
    }
}
