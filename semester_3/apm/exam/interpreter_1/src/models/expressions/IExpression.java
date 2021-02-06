package models.expressions;

import exceptions.ExpressionException;
import models.collections.IDictionary;
import models.collections.IHeap;
import models.types.IType;
import models.values.IValue;
import utils.ICopy;

public interface IExpression extends ICopy<IExpression> {
    IValue evaluate(IDictionary<String, IValue> symbols, IHeap<IValue> heap) throws ExpressionException;
    IType typeCheck(IDictionary<String, IType> typeEnv) throws ExpressionException;
}
