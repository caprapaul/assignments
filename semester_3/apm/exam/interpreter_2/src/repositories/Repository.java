package repositories;

import exceptions.InterpreterException;
import models.ProgramState;
import models.collections.IList;
import models.collections.List;

import java.io.*;

public class Repository implements IRepository {
    private IList<ProgramState> states;
    private String logFilePath;

    public Repository() {
        this.states = new List<>();
        this.logFilePath = "";
    }

    public Repository(String logFilePath) {
        this.states = new List<>();
        this.logFilePath = logFilePath;
        this.clearLog();
    }

    @Override
    public java.util.List<ProgramState> getStates() {
        return this.states.getAll();
    }

    @Override
    public void setStates(java.util.List<ProgramState> states) {
        this.states.setAll(states);
    }

    @Override
    public void addState(ProgramState state) {
        this.states.add(state);
    }

    @Override
    public void logExecution(ProgramState state) throws InterpreterException {
        if (this.logFilePath.isEmpty()) {
            throw new InterpreterException("Log file path not specified.");
        }

        try {
            PrintWriter logWriter = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));

            logWriter.write(state.toString() + "\n");
            logWriter.flush();
            logWriter.close();
        }
        catch (IOException e) {
            throw new InterpreterException("Cannot write to log file.");
        }
    }

    @Override
    public void clearLog() {
        File logFile = new File(this.logFilePath);
        logFile.delete();
    }

    public String getLogFilePath() {
        return this.logFilePath;
    }

    public void setLogFilePath(String logFilePath) {
        this.logFilePath = logFilePath;
    }
}
