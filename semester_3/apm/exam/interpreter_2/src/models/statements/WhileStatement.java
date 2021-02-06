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

public class WhileStatement implements IStatement {
    private final IExpression condition;
    private final IStatement instructions;

    public WhileStatement(IExpression condition, IStatement instructions) {
        this.condition = condition;
        this.instructions = instructions;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IValue conditionValue = this.condition.evaluate(state.getSymbols(), state.getHeap());

        if (!conditionValue.getType().equals(new BooleanType())) {
            throw new StatementException("Condition is not a boolean.");
        }

        boolean conditionBool = ((BooleanValue)conditionValue).into();

        if (conditionBool) {
            IStack<IStatement> execution = state.getExecution();

            execution.push(this.copy());
            execution.push(this.instructions.copy());
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

        this.instructions.typeCheck(typeEnvCopy);

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new WhileStatement(this.condition.copy(), this.instructions.copy());
    }

    @Override
    public String toString() {
        return String.format("while (%s) {%s}", this.condition, this.instructions);
    }
}
