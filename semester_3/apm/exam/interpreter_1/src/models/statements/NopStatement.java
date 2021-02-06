package models.statements;

import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.types.IType;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "Nop";
    }

    @Override
    public IStatement copy() {
        return new NopStatement();
    }
}
