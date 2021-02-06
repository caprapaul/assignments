package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.expressions.IExpression;
import models.types.IType;
import models.types.StringType;
import models.values.IValue;
import models.values.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements IStatement {
    private final IExpression expression;

    public OpenRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IValue value = this.expression.evaluate(state.getSymbols(), state.getHeap());

        if (!value.getType().equals(new StringType())) {
            throw new StatementException("Parameter must be of type " + new StringType() + ".");
        }

        StringValue stringValue = (StringValue) value;

        IDictionary<StringValue, BufferedReader> files = state.getFiles();
        BufferedReader file = files.get(stringValue);

        if (file != null) {
            throw new StatementException("File '" + stringValue + "' is already open.");
        }

        try {
            file = new BufferedReader(new FileReader(stringValue.into()));
        }
        catch (FileNotFoundException e) {
            throw new StatementException("Error while opening file '" + stringValue + "': " + e.getMessage());
        }

        files.put(stringValue, file);

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType expressionType = this.expression.typeCheck(typeEnv);

        if (!expressionType.equals(new StringType())) {
            throw new StatementException(String.format("Parameter must be of type %s.", new StringType()));
        }

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new OpenRFileStatement(this.expression.copy());
    }

    @Override
    public String toString() {
        return String.format("openRFile(%s)", this.expression.toString());
    }
}
