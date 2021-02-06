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

public class NewStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public NewStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        IHeap<IValue> heap = state.getHeap();
        IValue oldValue = symbols.get(this.variableName);

        if (oldValue == null) {
            throw new StatementException("Variable '" + this.variableName + "' not declared.");
        }

        IType oldValueType = oldValue.getType();
        IValue value = this.expression.evaluate(symbols, heap);
        IType valueType = value.getType();


        if (!oldValueType.equals(new RefType(valueType))) {
            throw new StatementException("Cannot assign value of type '" + new RefType(valueType) +
                    "' to variable of type '" + oldValueType + "'.");
        }

        int address = heap.allocate(value);
        symbols.put(this.variableName, new RefValue(address, valueType));

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
        return new NewStatement(this.variableName, this.expression.copy());
    }

    @Override
    public String toString() {
        return String.format("new(%s, %s)", this.variableName, this.expression);
    }
}
