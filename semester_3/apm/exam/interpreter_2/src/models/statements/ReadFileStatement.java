package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.expressions.IExpression;
import models.types.IType;
import models.types.IntegerType;
import models.types.StringType;
import models.values.IValue;
import models.values.IntegerValue;
import models.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement{
    private final IExpression expression;
    private final String variableName;

    public ReadFileStatement(IExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IDictionary<String, IValue> symbols = state.getSymbols();

        IValue variableValue = symbols.get(this.variableName);

        if (variableValue == null) {
            throw new StatementException("Variable '" + this.variableName + "' not declared.");
        }

        if (!variableValue.getType().equals(new IntegerType())) {
            throw new StatementException("Variable '" + this.variableName + "' must be of type " + new IntegerType() + ".");
        }

        IValue expressionValue = this.expression.evaluate(symbols, state.getHeap());

        if (!expressionValue.getType().equals(new StringType())) {
            throw new StatementException("Parameter 'expression' must be of type " + new StringType() + ".");
        }

        StringValue expressionStringValue = (StringValue) expressionValue;

        BufferedReader file = state.getFiles().get(expressionStringValue);

        if (file == null) {
            throw new StatementException("File '" + expressionStringValue + "' is not open.");
        }

        try {
            String line = file.readLine();

            IntegerValue readValue;

            if (line == null) {
                readValue = new IntegerValue(0);
            }
            else {
                readValue = new IntegerValue(Integer.parseInt(line));
            }

            symbols.put(this.variableName, readValue);
        }
        catch (IOException e) {
            throw new StatementException("Error while opening file '" + expressionStringValue + "': " + e.getMessage());
        }

        return null;
    }

    @Override
    public IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException {
        IType variableType = typeEnv.get(this.variableName);

        if (!variableType.equals(new IntegerType())) {
            throw new StatementException(String.format(
                    "Variable '%s' must be of type %s.",
                    this.variableName,
                    new IntegerType()
            ));
        }

        IType expressionType = this.expression.typeCheck(typeEnv);

        if (!expressionType.equals(new StringType())) {
            throw new StatementException(String.format("Parameter 'expression' must be of type %s.", new StringType()));
        }

        return typeEnv;
    }

    @Override
    public IStatement copy() {
        return new ReadFileStatement(this.expression.copy(), this.variableName);
    }

    @Override
    public String toString() {
        return String.format("readFile(%s, %s)", this.expression.toString(), this.variableName);
    }
}
