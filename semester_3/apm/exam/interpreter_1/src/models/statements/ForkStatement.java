package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.Dictionary;
import models.collections.IDictionary;
import models.collections.Stack;
import models.types.IType;
import models.values.IValue;

import java.util.Map;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        IDictionary<String, IValue> symbolsCopy = new Dictionary<>();

        for (Map.Entry<String, IValue> entry : symbols.getAll()) {
            IValue copy = entry.getValue().copy();
            symbolsCopy.put(entry.getKey(), copy);
        }

        ProgramState programState = new ProgramState(
                new Stack<>(),
                symbolsCopy,
                state.getOutput(),
                state.getFiles(),
                state.getHeap(),
                this.statement
        );
        return programState;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IDictionary<String, IType> typeEnvCopy = new Dictionary<>();

        for (Map.Entry<String, IType> entry : typeEnv.getAll()) {
            typeEnvCopy.put(entry.getKey(), entry.getValue());
        }

        this.statement.typeCheck(typeEnvCopy);

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new ForkStatement(this.statement.copy());
    }

    @Override
    public String toString() {
        return String.format("fork { %s }", this.statement);
    }
}
