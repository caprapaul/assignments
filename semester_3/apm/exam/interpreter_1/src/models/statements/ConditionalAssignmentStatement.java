package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.collections.IStack;
import models.expressions.IExpression;
import models.types.BooleanType;
import models.types.IType;

public class ConditionalAssignmentStatement implements IStatement {
    private final String name;
    private final IExpression condition;
    private final IExpression thenExpression;
    private final IExpression elseExpression;

    public ConditionalAssignmentStatement(
            String name,
            IExpression condition,
            IExpression thenExpression,
            IExpression elseExpression
    ) {
        this.name = name;
        this.condition = condition;
        this.thenExpression = thenExpression;
        this.elseExpression = elseExpression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IStack<IStatement> execution = state.getExecution();

        execution.push(new IfStatement(this.condition,
                new AssignStatement(this.name, this.thenExpression),
                new AssignStatement(this.name, this.elseExpression)
                )
        );

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType conditionType = this.condition.typeCheck(typeEnv);
        IType thenType = this.thenExpression.typeCheck(typeEnv);
        IType elseType = this.elseExpression.typeCheck(typeEnv);
        IType variableType = typeEnv.get(this.name);;

        if (!conditionType.equals(new BooleanType())) {
            throw new StatementException("Condition is not a boolean.");
        }

        if (!(thenType.equals(elseType) &&
                variableType.equals(thenType) &&
                variableType.equals(elseType)
        )) {
            throw new StatementException("Expression types do not match.");
        }

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new ConditionalAssignmentStatement(
                this.name,
                this.condition.copy(),
                this.thenExpression.copy(),
                this.elseExpression.copy()
        );
    }

    @Override
    public String toString() {
        return String.format("%s = %s ? %s : %s", this.name, this.condition, this.thenExpression, this.elseExpression);
    }
}
