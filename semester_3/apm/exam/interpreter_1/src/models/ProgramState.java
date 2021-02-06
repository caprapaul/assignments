package models;

import models.collections.IDictionary;
import models.collections.IHeap;
import models.collections.IList;
import models.collections.IStack;
import models.statements.IStatement;
import models.values.IValue;
import models.values.StringValue;

import java.io.BufferedReader;
import java.util.Objects;

public class ProgramState {
    private IStack<IStatement> execution;
    private IDictionary<String, IValue> symbols;
    private IList<IValue> output;
    private IDictionary<StringValue, BufferedReader> files;
    private IHeap<IValue> heap;
    private final int id;

    private final IStatement originalProgram;

    private static int freeId = 0;

    public ProgramState(
            IStack<IStatement> executionStack,
            IDictionary<String, IValue> symbols,
            IList<IValue> output,
            IDictionary<StringValue, BufferedReader> files,
            IHeap<IValue> heap,
            IStatement program
    ) {
        this.execution = executionStack;
        this.symbols = symbols;
        this.output = output;
        this.files = files;
        this.heap = heap;
        this.id = getNewId();

        this.originalProgram = program.copy();
        this.execution.push(program);
    }

    private static synchronized int getNewId() {
        freeId++;
        return freeId;
    }

    public static synchronized void resetId() {
        freeId = 0;
    }

    public IStack<IStatement> getExecution() {
        return this.execution;
    }

    public void setExecution(IStack<IStatement> execution) {
        this.execution = execution;
    }

    public IDictionary<String, IValue> getSymbols() {
        return this.symbols;
    }

    public void setSymbols(IDictionary<String, IValue> symbols) {
        this.symbols = symbols;
    }

    public IList<IValue> getOutput() {
        return this.output;
    }

    public void setOutput(IList<IValue> output) {
        this.output = output;
    }

    public IDictionary<StringValue, BufferedReader> getFiles() {
        return this.files;
    }

    public void setFiles(IDictionary<StringValue, BufferedReader> files) {
        this.files = files;
    }

    public boolean isCompleted() {
        return this.execution.isEmpty();
    }

    public int getId() {
        return this.id;
    }

    @Override
    public String toString() {
        String filesString = this.files.getKeys()
                                       .stream()
                                       .map(Objects::toString)
                                       .reduce("", (s1, s2) -> s1 + s2 + "\n");

        return "======== ProgramState ========" +
                "\nId: " + this.id +
                "\nExecution Stack:\n" + this.execution +
                "\nSymbols Table:\n" + this.symbols +
                "\nFiles Table:\n" + filesString +
                "\nHeap:\n" + this.heap +
                "\nOutput:\n" + this.output +
                "\n";
    }

    public IHeap<IValue> getHeap() {
        return heap;
    }

    public void setHeap(IHeap<IValue> heap) {
        this.heap = heap;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }
}
