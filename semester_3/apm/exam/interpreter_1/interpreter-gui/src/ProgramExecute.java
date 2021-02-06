import controllers.Controller;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import models.HeapRow;
import models.ProgramState;
import models.SymbolsRow;
import models.collections.IDictionary;
import models.collections.IStack;
import models.statements.IStatement;
import models.values.IValue;
import models.values.StringValue;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class ProgramExecute {
    private Controller programController;
    @FXML
    private TextField statesCount;
    @FXML
    private TableView<HeapRow> heap;
    @FXML
    private TableColumn<HeapRow, Integer> heapAddress;
    @FXML
    private TableColumn<HeapRow, String> heapValue;
    @FXML
    private TableView<SymbolsRow> symbols;
    @FXML
    private TableColumn<SymbolsRow, String> symbolsName;
    @FXML
    private TableColumn<SymbolsRow, String> symbolsValue;
    @FXML
    private ListView<Integer> states;
    @FXML
    private ListView<StringValue> files;
    @FXML
    private ListView<IStatement> execution;
    @FXML
    private ListView<IValue> output;
    @FXML
    private Button stepButton;
    @FXML
    private Button runButton;

    private ProgramState selectedState;

    public ProgramExecute(Controller programController) {
        this.programController = programController;
    }

    @FXML
    private void initialize() {
        this.heapAddress.setCellValueFactory(new PropertyValueFactory<>("address"));
        this.heapValue.setCellValueFactory(new PropertyValueFactory<>("value"));
        this.symbolsName.setCellValueFactory(new PropertyValueFactory<>("name"));
        this.symbolsValue.setCellValueFactory(new PropertyValueFactory<>("value"));
        this.states.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        this.stepButton.setOnMouseClicked(this::stepClickHandler);
        this.runButton.setOnMouseClicked(this::runClickHandler);
        this.states.setOnMouseClicked(this::statesClickHandler);

        this.selectedState = this.programController.getRepository().getStates().get(0);

        this.refresh();
    }

    private void statesClickHandler(MouseEvent mouseEvent) {
        Integer selectedStateId = this.states.getSelectionModel().getSelectedItem();

        if (selectedStateId == null) {
            this.stepButton.setDisable(true);
            this.runButton.setDisable(true);

            return;
        }
        else {
            this.stepButton.setDisable(false);
            this.runButton.setDisable(false);
        }

        for (ProgramState state: this.programController.getRepository().getStates()) {
            if (state.getId() == selectedStateId) {
                this.selectedState = state;
                this.refresh();
            }
        }
    }

    private void refresh() {
        List<ProgramState> states = this.programController.getRepository().getStates();
        this.statesCount.setText(String.valueOf(states.size()));
        this.populateStates(states);

        if (states.size() == 0) {
            this.stepButton.setDisable(true);
            this.runButton.setDisable(true);

            return;
        }
        else {
            this.stepButton.setDisable(false);
            this.runButton.setDisable(false);
        }

        this.populateHeap(states.get(0));
        this.populateOutput(states.get(0));
        this.populateFiles(states.get(0));

        //this.selectedState = null;

        if (this.selectedState == null) {
            this.stepButton.setDisable(true);
            this.runButton.setDisable(true);

            return;
        }
        else {
            this.stepButton.setDisable(false);
            this.runButton.setDisable(false);
        }

        this.populateExecution(this.selectedState);
        this.populateSymbols(this.selectedState);
    }

    private void populateStates(List<ProgramState> states) {
        List<Integer> stateIDs = states.stream()
                                       .map(ProgramState::getId)
                                       .collect(Collectors.toList());

        this.states.setItems(FXCollections.observableArrayList(stateIDs));
    }

    private void populateOutput(ProgramState state) {
        this.output.setItems(FXCollections.observableArrayList(state.getOutput().getAll()));
    }

    private void populateFiles(ProgramState state) {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFiles();
        List<StringValue> fileNames = new ArrayList<>(fileTable.getKeys());

        this.files.setItems(FXCollections.observableArrayList(fileNames));
    }

    private void populateHeap(ProgramState state) {
        List<HeapRow> rows = state.getHeap()
                                  .getAll()
                                  .stream()
                                  .map(entry -> new HeapRow(entry.getKey(), entry.getValue()))
                                  .collect(Collectors.toList());

        this.heap.setItems(FXCollections.observableArrayList(rows));
    }

    private void populateExecution(ProgramState state) {
        IStack<IStatement> execution = state.getExecution();

        this.execution.setItems(FXCollections.observableArrayList(execution.toList()));
    }

    private void populateSymbols(ProgramState state) {
        List<SymbolsRow> rows = state.getSymbols()
                                     .getAll()
                                     .stream()
                                     .map(entry -> new SymbolsRow(entry.getKey(), entry.getValue()))
                                     .collect(Collectors.toList());

        this.symbols.setItems(FXCollections.observableArrayList(rows));
    }

    private List<ProgramState> step(List<ProgramState> states) {
        List<Exception> exceptions = this.programController.oneStepAll(states);
        if (!exceptions.isEmpty())
        {
            Alert errorAlert = new Alert(Alert.AlertType.ERROR);
            errorAlert.setHeaderText("IOException Error");
            String content = exceptions.stream()
                                       .map(Throwable::getMessage)
                                       .reduce("", (a, b) -> a + "\n" + b);
            errorAlert.setContentText(content);
            errorAlert.showAndWait();
        }

        states = this.programController.removeCompleted(states);

        return states;
    }

    @FXML
    private void stepClickHandler(MouseEvent mouseEvent) {
        List<ProgramState> states = this.programController.getRepository().getStates();
        states = this.step(states);
        this.refresh();
        this.programController.getRepository().setStates(states);
        this.refresh();
    }

    @FXML
    private void runClickHandler(MouseEvent mouseEvent) {
        List<ProgramState> states = this.programController.getRepository().getStates();

        while (!states.isEmpty()) {
            states = this.step(states);
        }

        this.refresh();
        this.programController.getRepository().setStates(states);
        this.refresh();
    }
}
