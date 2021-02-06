import controllers.Controller;
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
import views.TextMenu;
import views.commands.ExitCommand;
import views.commands.RunExampleCommand;

import java.io.BufferedReader;

public class Main {
    public static void main(String[] args) {
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
//        Controller ex1 = exampleOne();
//        menu.addCommand(new RunExampleCommand("1", ex1.toString(), ex1));
//        Controller ex2 = exampleTwo();
//        menu.addCommand(new RunExampleCommand("2", ex2.toString(), ex2));
//        Controller ex3 = exampleThree();
//        menu.addCommand(new RunExampleCommand("3", ex3.toString(), ex3));
//        Controller ex4 = exampleFour();
//        menu.addCommand(new RunExampleCommand("4", ex4.toString(), ex4));
//        Controller ex5 = exampleFive();
//        menu.addCommand(new RunExampleCommand("5", ex5.toString(), ex5));
//        Controller ex6 = exampleSix();
//        menu.addCommand(new RunExampleCommand("6", ex6.toString(), ex6));
//        Controller ex7 = exampleSeven();
//        menu.addCommand(new RunExampleCommand("7", ex7.toString(), ex7));
//        Controller ex8 = exampleEight();
//        menu.addCommand(new RunExampleCommand("8", ex8.toString(), ex8));
//        Controller ex9 = exampleNine();
//        menu.addCommand(new RunExampleCommand("9", ex9.toString(), ex9));
//        Controller ex10 = exampleTen();
//        menu.addCommand(new RunExampleCommand("10", ex10.toString(), ex10));
//        Controller ex11 = exampleEleven();
//        menu.addCommand(new RunExampleCommand("11", ex11.toString(), ex11));

        menu.show();
    }


//    //region Examples
//
//    // int v; v = 2; print(v)
//    private static Controller exampleOne() {
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
//    private static Controller exampleTwo() {
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
//    private static Controller exampleThree() {
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
//    private static Controller exampleFour() {
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
//    private static Controller exampleFive() {
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
//    private static Controller exampleSix() {
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
//    private static Controller exampleSeven() {
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
//    private static Controller exampleEight() {
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
//    private static Controller exampleNine() {
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
//    private static Controller exampleTen() {
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
//    private static Controller exampleEleven() {
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
//    //endregion
}
