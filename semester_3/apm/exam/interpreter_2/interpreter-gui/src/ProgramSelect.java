import controllers.Controller;
import exceptions.InterpreterException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import models.ProgramState;
import models.collections.*;
import models.expressions.*;
import models.operations.ArithmeticOperation;
import models.operations.LogicalOperation;
import models.statements.*;
import models.types.BooleanType;
import models.types.IntegerType;
import models.types.RefType;
import models.types.StringType;
import models.values.BooleanValue;
import models.values.IValue;
import models.values.IntegerValue;
import models.values.StringValue;
import repositories.IRepository;
import repositories.Repository;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.function.Supplier;

public class ProgramSelect {
    @FXML
    private ListView<Controller> programList;
    private java.util.List<Supplier<Controller>> programs;

    @FXML
    private void initialize() {
        this.programs = new ArrayList<>();
        this.programList.setItems(this.getPrograms());
        this.programList.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void listClickHandler(MouseEvent mouseEvent) {
        if (mouseEvent.getClickCount() == 2) {
            int index = this.programList.getSelectionModel().getSelectedIndex();
            ProgramState.resetId();
            Controller selectedProgram = this.programs.get(index).get();

            try {
                selectedProgram.typeCheck();
            }
            catch (InterpreterException e) {
                Alert errorAlert = new Alert(Alert.AlertType.ERROR);
                errorAlert.setHeaderText("TypeCheck Error");
                errorAlert.setContentText(e.getMessage());
                errorAlert.showAndWait();

                return;
            }

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(this.getClass().getResource("ProgramExecute.fxml"));
            ProgramExecute executeController = new ProgramExecute(selectedProgram);
            loader.setController(executeController);

            try {
                Parent root = loader.load();
                Scene scene = new Scene(root, 600, 400);
                Stage stage = new Stage();

                stage.setScene(scene);
                stage.setTitle("Interpreter");
                stage.show();
                Stage thisStage = (Stage) this.programList.getScene().getWindow();
                //thisStage.close();
            }
            catch (IOException e) {
                Alert errorAlert = new Alert(Alert.AlertType.ERROR);
                errorAlert.setHeaderText("IOException Error");
                errorAlert.setContentText(e.getMessage());
                errorAlert.showAndWait();
            }
        }
    }

    private ObservableList<Controller> getPrograms() {
        java.util.List<Controller> programs = new ArrayList<>();

        this.programs.add(this::exampleE2);

        for (Supplier<Controller> controllerSupplier: this.programs) {
            programs.add(controllerSupplier.get());
        }

        return FXCollections.observableList(programs);
    }

//    //region Examples
//
//    // int v; v = 2; print(v)
//    private Controller exampleOne() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "v",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new AssignStatement(
//                                "v",
//                                new ValueExpression(
//                                        new IntegerValue(2)
//                                )
//                        ),
//                        new PrintStatement(
//                                new VariableExpression("v")
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log1.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    // int a; int b; a = 2 + 3 * 5; b = a + 1; print(b)
//    private Controller exampleTwo() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new VariableDeclarationStatement(
//                                "b",
//                                new IntegerType()
//                        ),
//                        new CompoundStatement(
//                                new AssignStatement(
//                                        "a",
//                                        new ArithmeticExpression(
//                                                new ValueExpression(
//                                                        new IntegerValue(2)
//                                                ),
//                                                new ArithmeticExpression(
//                                                        new ValueExpression(
//                                                                new IntegerValue(3)
//                                                        ),
//                                                        new ValueExpression(
//                                                                new IntegerValue(5)
//                                                        ),
//                                                        ArithmeticOperation.MULTIPLY
//                                                ),
//                                                ArithmeticOperation.ADD
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new AssignStatement(
//                                                "b",
//                                                new ArithmeticExpression(
//                                                        new VariableExpression("a"),
//                                                        new ValueExpression(
//                                                                new IntegerValue(1)
//                                                        ),
//                                                        ArithmeticOperation.ADD
//                                                )
//                                        ),
//                                        new PrintStatement(
//                                                new VariableExpression("b")
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log2.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    // bool a; int v; b = true; if (a) then (v = 2) else (v = 3); print(v)
//    private Controller exampleThree() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new BooleanType()
//                ),
//                new CompoundStatement(
//                        new VariableDeclarationStatement(
//                                "v",
//                                new IntegerType()
//                        ),
//                        new CompoundStatement(
//                                new AssignStatement(
//                                        "b",
//                                        new ValueExpression(
//                                                new BooleanValue(true)
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new IfStatement(
//                                                new VariableExpression("a"),
//                                                new AssignStatement(
//                                                        "v",
//                                                        new ValueExpression(
//                                                                new IntegerValue(2)
//                                                        )
//                                                ),
//                                                new AssignStatement(
//                                                        "v",
//                                                        new ValueExpression(
//                                                                new IntegerValue(3)
//                                                        )
//                                                )
//                                        ),
//                                        new PrintStatement(
//                                                new VariableExpression("v")
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log3.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    // string varf; varf = "test.in"; openRFile(varf); int x; readFile(varf, x); print(x); readFile(varf, x); print(x); closeRFile(varf)
//    private Controller exampleFour() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "varf",
//                        new StringType()
//                ),
//                new CompoundStatement(
//                        new AssignStatement(
//                                "varf",
//                                new ValueExpression(
//                                        new StringValue("test.in")
//                                )
//                        ),
//                        new CompoundStatement(
//                                new OpenRFileStatement(
//                                        new VariableExpression(
//                                                "varf"
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new VariableDeclarationStatement(
//                                                "x",
//                                                new IntegerType()
//                                        ),
//                                        new CompoundStatement(
//                                                new ReadFileStatement(
//                                                        new VariableExpression(
//                                                                "varf"
//                                                        ),
//                                                        "x"
//                                                ),
//                                                new CompoundStatement(
//                                                        new PrintStatement(
//                                                                new VariableExpression("x")
//                                                        ),
//                                                        new CompoundStatement(
//                                                                new ReadFileStatement(
//                                                                        new VariableExpression("varf"),
//                                                                        "x"
//                                                                ),
//                                                                new CompoundStatement(
//                                                                        new PrintStatement(
//                                                                                new VariableExpression("x")
//                                                                        ),
//                                                                        new CloseRFileStatement(
//                                                                                new VariableExpression(
//                                                                                        "varf"
//                                                                                )
//                                                                        )
//                                                                )
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log4.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleFive() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new AssignStatement(
//                                "a",
//                                new ValueExpression(
//                                        new IntegerValue(5)
//                                )
//                        ),
//                        new PrintStatement(
//                                new LogicalExpression(
//                                        new VariableExpression("a"),
//                                        new ValueExpression(
//                                                new IntegerValue(10)
//                                        ),
//                                        LogicalOperation.GREATER
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log5.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    //
//    private Controller exampleSix() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new RefType(
//                                new IntegerType()
//                        )
//                ),
//                new CompoundStatement(
//                        new NewStatement(
//                                "a",
//                                new ValueExpression(
//                                        new IntegerValue(20)
//                                )
//                        ),
//                        new CompoundStatement(
//                                new VariableDeclarationStatement(
//                                        "b",
//                                        new RefType(
//                                                new RefType(
//                                                        new IntegerType()
//                                                )
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new NewStatement(
//                                                "b",
//                                                new VariableExpression("a")
//                                        ),
//                                        new CompoundStatement(
//                                                new PrintStatement(
//                                                        new ReadHeapExpression(
//                                                                new VariableExpression("a")
//                                                        )
//                                                ),
//                                                new CompoundStatement(
//                                                        new PrintStatement(
//                                                                new ReadHeapExpression(
//                                                                        new ReadHeapExpression(
//                                                                                new VariableExpression("b")
//                                                                        )
//                                                                )
//                                                        ),
//                                                        new CompoundStatement(
//                                                                new WriteHeapStatement(
//                                                                        "a",
//                                                                        new ValueExpression(
//                                                                                new IntegerValue(30)
//                                                                        )
//                                                                ),
//                                                                new PrintStatement(
//                                                                        new ReadHeapExpression(
//                                                                                new ReadHeapExpression(
//                                                                                        new VariableExpression("b")
//                                                                                )
//                                                                        )
//                                                                )
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log6.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleSeven() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new RefType(
//                                new IntegerType()
//                        )
//                ),
//                new CompoundStatement(
//                        new NewStatement(
//                                "a",
//                                new ValueExpression(
//                                        new IntegerValue(20)
//                                )
//                        ),
//                        new CompoundStatement(
//                                new VariableDeclarationStatement(
//                                        "b",
//                                        new RefType(
//                                                new RefType(
//                                                        new IntegerType()
//                                                )
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new NewStatement(
//                                                "b",
//                                                new VariableExpression("a")
//                                        ),
//                                        new CompoundStatement(
//                                                new PrintStatement(
//                                                        new ReadHeapExpression(
//                                                                new VariableExpression("a")
//                                                        )
//                                                ),
//                                                new CompoundStatement(
//                                                        new PrintStatement(
//                                                                new ReadHeapExpression(
//                                                                        new ReadHeapExpression(
//                                                                                new VariableExpression("b")
//                                                                        )
//                                                                )
//                                                        ),
//                                                        new CompoundStatement(
//                                                                new NewStatement(
//                                                                        "a",
//                                                                        new ValueExpression(
//                                                                                new IntegerValue(30)
//                                                                        )
//                                                                ),
//                                                                new CompoundStatement(
//                                                                        new PrintStatement(
//                                                                                new ReadHeapExpression(
//                                                                                        new ReadHeapExpression(
//                                                                                                new VariableExpression("b")
//                                                                                        )
//                                                                                )
//                                                                        ),
//                                                                        new CompoundStatement(
//                                                                                new NewStatement(
//                                                                                        "b",
//                                                                                        new VariableExpression("a")
//                                                                                ),
//                                                                                new CompoundStatement(
//                                                                                        new PrintStatement(
//                                                                                                new ReadHeapExpression(
//                                                                                                        new ReadHeapExpression(
//                                                                                                                new VariableExpression("b")
//                                                                                                        )
//                                                                                                )
//                                                                                        ),
//                                                                                        new CompoundStatement(
//                                                                                                new NewStatement(
//                                                                                                        "a",
//                                                                                                        new ValueExpression(
//                                                                                                                new IntegerValue(10)
//                                                                                                        )
//                                                                                                ),
//                                                                                                new CompoundStatement(
//                                                                                                        new NewStatement(
//                                                                                                                "b",
//                                                                                                                new VariableExpression("a")
//                                                                                                        ),
//                                                                                                        new NopStatement()
//                                                                                                )
//                                                                                        )
//                                                                                )
//                                                                        )
//                                                                )
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log7.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleEight() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new AssignStatement(
//                                "a",
//                                new ValueExpression(
//                                        new IntegerValue(4)
//                                )
//                        ),
//                        new WhileStatement(
//                                new LogicalExpression(
//                                        new VariableExpression("a"),
//                                        new ValueExpression(
//                                                new IntegerValue(0)
//                                        ),
//                                        LogicalOperation.GREATER
//                                ),
//                                new CompoundStatement(
//                                        new PrintStatement(
//                                                new VariableExpression("a")
//                                        ),
//                                        new AssignStatement(
//                                                "a",
//                                                new ArithmeticExpression(
//                                                        new VariableExpression("a"),
//                                                        new ValueExpression(
//                                                                new IntegerValue(1)
//                                                        ),
//                                                        ArithmeticOperation.SUBTRACT
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log8.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleNine() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new NewStatement(
//                                "a",
//                                new ValueExpression(
//                                        new IntegerValue(20)
//                                )
//                        ),
//                        new CompoundStatement(
//                                new VariableDeclarationStatement(
//                                        "b",
//                                        new RefType(
//                                                new RefType(
//                                                        new IntegerType()
//                                                )
//                                        )
//                                ),
//                                new NewStatement(
//                                        "b",
//                                        new VariableExpression("a")
//                                )
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log9.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleTen() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "v",
//                        new IntegerType()
//                ),
//                new CompoundStatement(
//                        new VariableDeclarationStatement(
//                                "a",
//                                new RefType(new IntegerType())
//                        ),
//                        new CompoundStatement(
//                                new AssignStatement(
//                                        "v",
//                                        new ValueExpression(
//                                                new IntegerValue(10)
//                                        )
//                                ),
//                                new CompoundStatement(
//                                        new NewStatement(
//                                                "a",
//                                                new ValueExpression(
//                                                        new IntegerValue(22)
//                                                )
//                                        ),
//                                        new CompoundStatement(
//                                                new ForkStatement(
//                                                        new CompoundStatement(
//                                                                new WriteHeapStatement(
//                                                                        "a",
//                                                                        new ValueExpression(
//                                                                                new IntegerValue(30)
//                                                                        )
//                                                                ),
//                                                                new CompoundStatement(
//                                                                        new AssignStatement(
//                                                                                "v",
//                                                                                new ValueExpression(
//                                                                                        new IntegerValue(32)
//                                                                                )
//                                                                        ),
//                                                                        new CompoundStatement(
//                                                                                new PrintStatement(
//                                                                                        new VariableExpression("v")
//                                                                                ),
//                                                                                new PrintStatement(
//                                                                                        new ReadHeapExpression(
//                                                                                                new VariableExpression("a")
//                                                                                        )
//                                                                                )
//                                                                        )
//                                                                )
//                                                        )
//                                                ),
//                                                new CompoundStatement(
//                                                        new PrintStatement(
//                                                                new VariableExpression("v")
//                                                        ),
//                                                        new PrintStatement(
//                                                                new ReadHeapExpression(
//                                                                        new VariableExpression("a")
//                                                                )
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log10.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
//    private Controller exampleEleven() {
//        IStack<IStatement> execution = new Stack<>();
//        IDictionary<String, IValue> symbols = new Dictionary<>();
//        IList<IValue> output = new List<>();
//        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
//        IHeap<IValue> heap = new Heap<>();
//
//        IStatement statement = new CompoundStatement(
//                new VariableDeclarationStatement(
//                        "a",
//                        new IntegerType()
//                ),
//                new AssignStatement(
//                        "a",
//                        new ArithmeticExpression(
//                                new ValueExpression(
//                                        new IntegerValue(2)
//                                ),
//                                new ValueExpression(
//                                        new StringValue("value")
//                                ),
//                                ArithmeticOperation.ADD
//                        )
//                )
//        );
//
//        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);
//
//        IRepository repository = new Repository("log11.txt");
//        repository.addState(program);
//
//        return new Controller(repository);
//    }
//
    private Controller exampleE2() {
        IStack<IStatement> execution = new Stack<>();
        IDictionary<String, IValue> symbols = new Dictionary<>();
        IList<IValue> output = new List<>();
        IDictionary<StringValue, BufferedReader> files = new Dictionary<>();
        IHeap<IValue> heap = new Heap<>();
        ILatchTable latches = new LatchTable();

        IStatement statement = new CompoundStatement(
                new VariableDeclarationStatement(
                        "v1",
                        new RefType(new IntegerType())
                ),
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v2",
                                new RefType(new IntegerType())
                        ),
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "v3",
                                        new RefType(new IntegerType())
                                ),
                                new CompoundStatement(
                                        new VariableDeclarationStatement(
                                                "cnt",
                                                new IntegerType()
                                        ),
                                        new CompoundStatement(
                                                new NewStatement(
                                                        "v1",
                                                        new ValueExpression(
                                                                new IntegerValue(2)
                                                        )
                                                ),
                                                new CompoundStatement(
                                                        new NewStatement(
                                                                "v2",
                                                                new ValueExpression(
                                                                        new IntegerValue(3)
                                                                )
                                                        ),
                                                        new CompoundStatement(
                                                                new NewStatement(
                                                                        "v3",
                                                                        new ValueExpression(
                                                                                new IntegerValue(4)
                                                                        )
                                                                ),
                                                                new CompoundStatement(
                                                                        new NewLatchStatement(
                                                                                "cnt",
                                                                                new ReadHeapExpression(
                                                                                        new VariableExpression("v2")
                                                                                )
                                                                        ),
                                                                        new CompoundStatement(
                                                                                new ForkStatement(
                                                                                        new CompoundStatement(
                                                                                                new WriteHeapStatement(
                                                                                                        "v1",
                                                                                                        new ArithmeticExpression(
                                                                                                                new ReadHeapExpression(
                                                                                                                        new VariableExpression("v1")
                                                                                                                ),
                                                                                                                new ValueExpression(new IntegerValue(10)),
                                                                                                                ArithmeticOperation.MULTIPLY
                                                                                                        )
                                                                                                ),
                                                                                                new CompoundStatement(
                                                                                                        new PrintStatement(
                                                                                                                new ReadHeapExpression(
                                                                                                                        new VariableExpression("v1")
                                                                                                                )
                                                                                                        ),
                                                                                                        new CountDownStatement("cnt")
                                                                                                )
                                                                                        )
                                                                                ),
                                                                                new CompoundStatement(
                                                                                        new ForkStatement(
                                                                                                new CompoundStatement(
                                                                                                        new WriteHeapStatement(
                                                                                                                "v2",
                                                                                                                new ArithmeticExpression(
                                                                                                                        new ReadHeapExpression(
                                                                                                                                new VariableExpression("v2")
                                                                                                                        ),
                                                                                                                        new ValueExpression(new IntegerValue(10)),
                                                                                                                        ArithmeticOperation.MULTIPLY
                                                                                                                )
                                                                                                        ),
                                                                                                        new CompoundStatement(
                                                                                                                new PrintStatement(
                                                                                                                        new ReadHeapExpression(
                                                                                                                                new VariableExpression("v2")
                                                                                                                        )
                                                                                                                ),
                                                                                                                new CountDownStatement("cnt")
                                                                                                        )
                                                                                                )
                                                                                        ),
                                                                                        new CompoundStatement(
                                                                                                new ForkStatement(
                                                                                                        new CompoundStatement(
                                                                                                                new WriteHeapStatement(
                                                                                                                        "v3",
                                                                                                                        new ArithmeticExpression(
                                                                                                                                new ReadHeapExpression(
                                                                                                                                        new VariableExpression("v3")
                                                                                                                                ),
                                                                                                                                new ValueExpression(new IntegerValue(10)),
                                                                                                                                ArithmeticOperation.MULTIPLY
                                                                                                                        )
                                                                                                                ),
                                                                                                                new CompoundStatement(
                                                                                                                        new PrintStatement(
                                                                                                                                new ReadHeapExpression(
                                                                                                                                        new VariableExpression("v3")
                                                                                                                                )
                                                                                                                        ),
                                                                                                                        new CountDownStatement("cnt")
                                                                                                                )
                                                                                                        )
                                                                                                ),
                                                                                                new CompoundStatement(
                                                                                                        new AwaitStatement("cnt"),
                                                                                                        new CompoundStatement(
                                                                                                                new PrintStatement(
                                                                                                                        new ValueExpression(
                                                                                                                                new IntegerValue(100)
                                                                                                                        )
                                                                                                                ),
                                                                                                                new CompoundStatement(
                                                                                                                        new CountDownStatement("cnt"),
                                                                                                                        new PrintStatement(
                                                                                                                                new ValueExpression(
                                                                                                                                        new IntegerValue(100)
                                                                                                                                )
                                                                                                                        )
                                                                                                                )
                                                                                                        )
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        ProgramState program = new ProgramState(execution, symbols, output, files, heap, latches, statement);

        IRepository repository = new Repository("loge2.txt");
        repository.addState(program);

        return new Controller(repository);
    }
//
//    //endregion
}
