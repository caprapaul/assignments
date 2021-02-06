package models.statements;

import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.types.IType;
import models.values.IValue;

public class VariableDeclarationStatement implements IStatement {
    private final String name;
    private final IType type;

    public VariableDeclarationStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IDictionary<String, IValue> symbols = state.getSymbols();

        if (symbols.get(this.name) != null) {
            throw new StatementException("Variable '" + this.name + "' already declared.");
        }

        symbols.put(this.name, this.type.getDefaultValue());

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        typeEnv.put(this.name, this.type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return String.format("%s %s", this.type, this.name);
    }

    @Override
    public IStatement copy() {
        return new VariableDeclarationStatement(this.name, this.type);
    }
}
