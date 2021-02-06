package models.expressions;

import exceptions.ExpressionException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.operations.LogicalOperation;
import models.types.BooleanType;
import models.types.IType;
import models.types.IntegerType;
import models.values.BooleanValue;
import models.values.IValue;
import models.values.IntegerValue;

public class LogicalExpression implements IExpression {
    private final IExpression left;
    private final IExpression right;
    private final LogicalOperation operation;

    public LogicalExpression(IExpression left, IExpression right, LogicalOperation operation) {
        this.left = left;
        this.right = right;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) throws ExpressionException {
        IValue leftValue = this.left.evaluate(symbols, heap);
        IValue rightValue = this.right.evaluate(symbols, heap);

        if (this.operation == LogicalOperation.AND || this.operation == LogicalOperation.OR) {
            if (!leftValue.getType().equals(new BooleanType())) {
                throw new ExpressionException("Left operand is not a boolean.");
            }

            if (!rightValue.getType().equals(new BooleanType())) {
                throw new ExpressionException("Right operand is not a boolean.");
            }

            boolean leftBool = ((BooleanValue) leftValue).into();
            boolean rightBool = ((BooleanValue) rightValue).into();

            switch (this.operation) {
                case AND -> {
                    return new BooleanValue(leftBool && rightBool);
                }
                case OR -> {
                    return new BooleanValue(leftBool || rightBool);
                }
                default -> {
                    throw new ExpressionException("Unexpected operation: " + this.operation);
                }
            }
        }
        else {
            if (!leftValue.getType().equals(new IntegerType())) {
                throw new ExpressionException("Left operand is not an integer.");
            }

            if (!rightValue.getType().equals(new IntegerType())) {
                throw new ExpressionException("Right operand is not an integer.");
            }

            int leftInt = ((IntegerValue) leftValue).into();
            int rightInt = ((IntegerValue) rightValue).into();

            switch (this.operation) {
                case LESS -> {
                    return new BooleanValue(leftInt < rightInt);
                }
                case LESS_EQUAL -> {
                    return new BooleanValue(leftInt <= rightInt);
                }
                case GREATER -> {
                    return new BooleanValue(leftInt > rightInt);
                }
                case GREATER_EQUAL -> {
                    return new BooleanValue(leftInt >= rightInt);
                }
                case EQUAL -> {
                    return new BooleanValue(leftInt == rightInt);
                }
                case NOT_EQUAL -> {
                    return new BooleanValue(leftInt != rightInt);
                }
                default -> {
                    throw new ExpressionException("Unexpected operation: " + this.operation);
                }
            }
        }
    }

    @Override
    public IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException {
        IType leftType = this.left.typeCheck(typeEnv);
        IType rightType = this.right.typeCheck(typeEnv);

        if (this.operation == LogicalOperation.AND || this.operation == LogicalOperation.OR) {
            if (!leftType.equals(new BooleanType())) {
                throw new ExpressionException("The left operand is not a boolean.");
            }

            if (!rightType.equals(new BooleanType())) {
                throw new ExpressionException("The right operand is not a boolean.");
            }

            return new BooleanType();
        }

        if (!leftType.equals(new IntegerType())) {
            throw new ExpressionException("The left operand is not an integer.");
        }

        if (!rightType.equals(new IntegerType())) {
            throw new ExpressionException("The right operand is not an integer.");
        }

        return new BooleanType();
    }

    @Override
    public String toString() {
        return String.format("%s %s %s", this.left, this.operation, this.right);
    }

    @Override
    public IExpression copy() {
        return new LogicalExpression(this.left.copy(), this.right.copy(), this.operation);
    }
}
