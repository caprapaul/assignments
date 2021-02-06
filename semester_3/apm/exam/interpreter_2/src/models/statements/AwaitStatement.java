package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.collections.ILatchTable;
import models.types.IType;
import models.types.IntegerType;
import models.values.IValue;
import models.values.IntegerValue;

public class AwaitStatement implements IStatement {
    private final String variableName;

    public AwaitStatement(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        ILatchTable latches = state.getLatches();
        IntegerValue variableValue = (IntegerValue) symbols.get(this.variableName);

        int count = latches.get(variableValue.into());

        if (count == -1) {
            throw new StatementException(String.format(
                    "Id %s does not exist in the latch table'.",
                    variableValue.into()
            ));
        }

        if (count != 0) {
            state.getExecution().push(this.copy());
        }

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType variableType = typeEnv.get(this.variableName);

        if (variableType == null) {
            throw new StatementException(String.format(
                    "Variable '%s' not declared.",
                    this.variableName
            ));
        }

        if (!variableType.equals(new IntegerType())) {
            throw new StatementException(String.format(
                    "Variable must be of type '%s'.",
                    new IntegerType()
            ));
        }

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new AwaitStatement(this.variableName);
    }

    @Override
    public String
    toString() {
        return String.format("await(%s)", this.variableName);
    }
}
