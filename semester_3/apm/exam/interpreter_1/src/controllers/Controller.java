package controllers;

import exceptions.CollectionException;
import exceptions.ExpressionException;
import exceptions.InterpreterException;
import exceptions.StatementException;
import models.ProgramState;
import models.collections.*;
import models.statements.IStatement;
import models.types.IType;
import models.values.IValue;
import models.values.RefValue;
import repositories.IRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository repository;
    private boolean display;
    private ExecutorService executor;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public IRepository getRepository() {
        return this.repository;
    }

    public ProgramState step(ProgramState state) throws CollectionException, StatementException, ExpressionException {
        IStack<IStatement> execution = state.getExecution();
        IStatement currentStatement = execution.pop();

        return currentStatement.execute(state);
    }

    public List<Exception> stepAll(List<ProgramState> states) throws InterpreterException {
        //states.forEach(this.repository::logExecution);

        List<Callable<ProgramState>> callList = states.stream()
                .map(state -> (Callable<ProgramState>)(() -> this.step(state)))
                .collect(Collectors.toList());

        List<Exception> exceptions = new ArrayList<>();

        List<ProgramState> newStates;
        try {
            newStates = this.executor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        }
                        catch (Exception e) {
                            exceptions.add(e);
                            return null;
                        }
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());
        }
        catch (InterruptedException e) {
            throw new InterpreterException(e.getMessage());
        }

        states.addAll(newStates);
        //states.forEach(this.repository::logExecution);
        this.repository.setStates(states);

        return exceptions;
    }

    public List<Exception> oneStepAll(List<ProgramState> states) {
        this.executor = Executors.newFixedThreadPool(2);
        states.forEach(this.repository::logExecution);

        this.collectGarbageAll(states);
        List<Exception> exceptions = this.stepAll(states);
        states.forEach(this.repository::logExecution);

        this.executor.shutdownNow();
        return exceptions;
    }

    public void run() throws InterpreterException {
        this.typeCheck();

        this.executor = Executors.newFixedThreadPool(2);
        List<ProgramState> states = this.removeCompleted(this.repository.getStates());
        states.forEach(this.repository::logExecution);

        while (states.size() > 0) {
            this.collectGarbageAll(states);
            this.stepAll(states);
            states.forEach(this.repository::logExecution);
            states = this.removeCompleted(this.repository.getStates());
        }

        this.executor.shutdownNow();
        this.repository.setStates(states);
    }

    public void typeCheck() throws InterpreterException {
        IDictionary<String, IType> typeEnv = new Dictionary<>();

        this.repository.getStates().get(0).getOriginalProgram().typeCheck(typeEnv);
    }

    public List<ProgramState> removeCompleted(List<ProgramState> states) {
        return states.stream()
                .filter(state -> !state.isCompleted())
                .collect(Collectors.toList());
    }

    private void getAddressesUsedRecursive(IValue value, IHeap<IValue> heap, List<Integer> addresses) {
        if (!(value instanceof RefValue)) {
            return;
        }

        RefValue ref = (RefValue)value;
        int address = ref.getAddress();
        addresses.add(address);

        IValue innerValue = heap.get(address);

        this.getAddressesUsedRecursive(innerValue, heap, addresses);
    }

    private List<Integer> getAddressesUsed(IDictionary<String, IValue> symbols, IHeap<IValue> heap) {

        return symbols.getValues().stream()
                      .filter(v -> v instanceof RefValue)
                      .map(v -> {
                          List<Integer> addresses = new ArrayList<>();
                          this.getAddressesUsedRecursive(v, heap, addresses);
                          return addresses;
                      })
                      .flatMap(List::stream)
                      .collect(Collectors.toList());
    }

    private List<Integer> getAddressesUsedAll(List<ProgramState> states) {
        return states.stream()
                     .map(state -> this.getAddressesUsed(state.getSymbols(), state.getHeap()))
                     .flatMap(List::stream)
                     .collect(Collectors.toList());
    }

    private void collectGarbageAll(List<ProgramState> states) {
        List<Integer> addressesUsed =  this.getAddressesUsedAll(states);
        this.collectGarbage(states.get(0).getHeap(), addressesUsed);
    }

    private void collectGarbage(IHeap<IValue> heap, List<Integer> addressesUsed) {
        heap.getAll().stream()
            .filter(entry -> !addressesUsed.contains(entry.getKey()))
            .forEach(entry -> heap.free(entry.getKey()));
    }

    public void setDisplay(boolean display) {
        this.display = display;
    }

    @Override
    public String toString() {
        String execution = this.repository.getStates().get(0).getExecution().toString();
        return execution.substring(0, execution.length() - 1);
    }
}
