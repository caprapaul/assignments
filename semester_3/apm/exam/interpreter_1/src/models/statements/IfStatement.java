package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.Dictionary;
import models.collections.IDictionary;
import models.collections.IStack;
import models.expressions.IExpression;
import models.types.BooleanType;
import models.types.IType;
import models.values.BooleanValue;
import models.values.IValue;

import java.util.Map;

public class IfStatement implements IStatement {
    private final IExpression condition;
    private final IStatement thenStatement;
    private final IStatement elseStatement;

    public IfStatement(IExpression condition, IStatement thenStatement, IStatement elseStatement) {
        this.condition = condition;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ExpressionException, StatementException {
        IStack<IStatement> execution = state.getExecution();
        IValue conditionValue = this.condition.evaluate(state.getSymbols(), state.getHeap());

        if (!conditionValue.getType().equals(new BooleanType())) {
            throw new StatementException("Condition is not a boolean.");
        }

        boolean conditionBool = ((BooleanValue)conditionValue).into();

        if (conditionBool) {
            execution.push(this.thenStatement.copy());
        }
        else {
            execution.push(this.elseStatement.copy());
        }

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType conditionType = this.condition.typeCheck(typeEnv);

        if (!conditionType.equals(new BooleanType())) {
            throw new StatementException("Condition is not a boolean.");
        }

        IDictionary<String, IType> typeEnvCopy = new Dictionary<>();

        for (Map.Entry<String, IType> entry : typeEnv.getAll()) {
            typeEnvCopy.put(entry.getKey(), entry.getValue());
        }

        this.thenStatement.typeCheck(typeEnvCopy);
        this.elseStatement.typeCheck(typeEnvCopy);

        return typeEnv;
    }

    @Override
    public String toString() {
        return String.format("if (%s) then (%s) else (%s)", this.condition, this.thenStatement, this.elseStatement);
    }

    @Override
    public IStatement copy() {
        return new IfStatement(this.condition.copy(), this.thenStatement.copy(), this.elseStatement.copy());
    }
}
