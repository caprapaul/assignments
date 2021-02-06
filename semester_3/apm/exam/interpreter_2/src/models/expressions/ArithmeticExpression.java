package models.expressions;

import exceptions.ExpressionException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.operations.ArithmeticOperation;
import models.types.IType;
import models.types.IntegerType;
import models.values.IntegerValue;
import models.values.IValue;

public class ArithmeticExpression implements IExpression {
    private final IExpression left;
    private final IExpression right;
    private final ArithmeticOperation operation;

    public ArithmeticExpression(IExpression left, IExpression right, ArithmeticOperation operation) {
        this.left = left;
        this.right = right;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) throws ExpressionException {
        IValue leftValue = this.left.evaluate(symbols, heap);

        if (!leftValue.getType().equals(new IntegerType())) {
            throw new ExpressionException("Left operand is not an integer.");
        }

        IValue rightValue = this.right.evaluate(symbols, heap);

        if (!rightValue.getType().equals(new IntegerType())) {
            throw new ExpressionException("Right operand is not an integer.");
        }

        int leftInt = ((IntegerValue)leftValue).into();
        int rightInt = ((IntegerValue)rightValue).into();

        switch (this.operation) {
            case ADD -> {
                return new IntegerValue(leftInt + rightInt);
            }
            case SUBTRACT -> {
                return new IntegerValue(leftInt - rightInt);
            }
            case MULTIPLY -> {
                return new IntegerValue(leftInt * rightInt);
            }
            case DIVIDE -> {
                if (rightInt == 0) {
                    throw new ExpressionException("Division by zero.");
                }

                return new IntegerValue(leftInt / rightInt);
            }
            default -> {
                throw new ExpressionException("Unexpected operation: " + this.operation);
            }
        }
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException {
        IType leftType = this.left.typeCheck(typeEnv);
        IType rightType = this.right.typeCheck(typeEnv);

        if (!leftType.equals(new IntegerType())) {
            throw new ExpressionException("The left operand is not an integer.");
        }

        if (!rightType.equals(new IntegerType())) {
            throw new ExpressionException("The right operand is not an integer.");
        }

        return new IntegerType();
    }

    @Override
    public String toString() {
        return String.format("%s %s %s", this.left, this.operation, this.right);
    }

    @Override
    public IExpression copy() {
        return new ArithmeticExpression(this.left.copy(), this.right.copy(), this.operation);
    }
}
