package models.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.IDictionary;
import models.types.IType;
import utils.ICopy;

public interface IStatement extends ICopy<IStatement> {
    ProgramState execute(ProgramState state) throws StatementException, ExpressionException;
    IDictionary<String, IType> typeCheck(IDictionary<String, IType> typeEnv) throws StatementException;
}
