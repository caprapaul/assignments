package models.statements;

import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.collections.IStack;
import models.types.IType;

public class CompoundStatement implements IStatement {
    private final IStatement first;
    private final IStatement second;

    public CompoundStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IStack<IStatement> execution = state.getExecution();
        execution.push(this.second);
        execution.push(this.first);

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        return this.second.typeCheck(this.first.typeCheck(typeEnv));
    }

    @Override
    public String toString() {
        return String.format("%s; %s", this.first, this.second);
    }

    @Override
    public IStatement copy() {
        return new CompoundStatement(this.first.copy(), this.second.copy());
    }
}
