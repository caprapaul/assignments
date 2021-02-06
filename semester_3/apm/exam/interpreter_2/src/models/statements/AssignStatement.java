package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.expressions.IExpression;
import models.types.IType;
import models.values.IValue;

public class AssignStatement implements IStatement {
    private final String name;
    private final IExpression expression;

    public AssignStatement(String name, IExpression expression) {
        this.name = name;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        IValue oldValue = symbols.get(this.name);

        if (oldValue == null) {
            throw new StatementException("Variable '" + this.name + "' not declared.");
        }

        IValue newValue = this.expression.evaluate(symbols, state.getHeap());
        IType newValueType = newValue.getType();
        IType oldValueType = oldValue.getType();

        if (!newValueType.equals(oldValueType)) {
            throw new StatementException(String.format(
                    "Cannot assign value of type '%s' to variable of type '%s'.",
                    newValueType,
                    oldValueType
            ));
        }

        symbols.put(this.name, newValue);

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType variableType = typeEnv.get(this.name);
        IType expressionType = this.expression.typeCheck(typeEnv);

        if (variableType == null) {
            throw new ExpressionException("Variable '" + this.name + "' not declared.");
        }

        if (!variableType.equals(expressionType))
        {
            throw new StatementException(String.format(
                    "Cannot assign value of type '%s' to variable of type '%s'.",
                    expressionType,
                    variableType
            ));
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return String.format("%s = %s", this.name, this.expression);
    }

    @Override
    public IStatement copy() {
        return new AssignStatement(this.name, this.expression.copy());
    }
}
