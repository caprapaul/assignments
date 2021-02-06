package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.collections.ILatchTable;
import models.expressions.IExpression;
import models.types.IType;
import models.types.IntegerType;
import models.types.RefType;
import models.values.IValue;
import models.values.IntegerValue;

public class NewLatchStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public NewLatchStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();
        IHeap<IValue> heap = state.getHeap();
        ILatchTable latches = state.getLatches();
        IntegerValue expressionValue = (IntegerValue) this.expression.evaluate(symbols, heap);

        int id = latches.add(expressionValue.into());
        symbols.put(this.variableName, new IntegerValue(id));

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType expressionType = this.expression.typeCheck(typeEnv);

        if (!expressionType.equals(new IntegerType())) {
            throw new StatementException(String.format(
                    "Expression must be of type '%s'.",
                    new IntegerType()
            ));
        }

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
        return new NewLatchStatement(this.variableName, this.expression.copy());
    }

    @Override
    public String toString() {
        return String.format("newLatch(%s, %s)", this.variableName, this.expression);
    }
}
