package repositories;

import exceptions.InterpreterException;
import models.ProgramState;
import java.util.List;

public interface IRepository {
    List<ProgramState> getStates();
    void setStates(List<ProgramState> states);
    void addState(ProgramState state);
    void logExecution(ProgramState state) throws InterpreterException;
    void clearLog();
}
