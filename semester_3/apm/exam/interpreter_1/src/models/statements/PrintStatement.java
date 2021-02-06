package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.expressions.IExpression;
import models.types.IType;
import models.values.IValue;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ExpressionException {
        IValue value = this.expression.evaluate(state.getSymbols(), state.getHeap());
        state.getOutput().add(value);

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        this.expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return String.format("print(%s)", this.expression);
    }

    @Override
    public IStatement copy() {
        return new PrintStatement(this.expression.copy());
    }
}
