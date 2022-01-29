package View.Console;

import Controller.Controller;
import Model.ADT.*;
import Model.Exp.*;
import Model.PrgState;
import Model.Stmt.*;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.IRepo;
import Repository.Repo;

import java.io.BufferedReader;
import java.util.ArrayDeque;
import java.util.Deque;

public class Interpreter {
    public static void main(String[] args) {

        View.TextMenu menu = new View.TextMenu();/*
        menu.addCommand(new View.ExitCommand("0", "exit"));
        menu.addCommand(Interpreter.getExample(1));
        menu.addCommand(Interpreter.getExample(2));
        menu.addCommand(Interpreter.getExample(3));
        menu.addCommand(Interpreter.getExample(4));
        menu.addCommand(Interpreter.getExample(5));
        menu.addCommand(Interpreter.getExample(6));
        menu.addCommand(Interpreter.getExample(7));
        menu.addCommand(Interpreter.getExample(8));
        menu.addCommand(Interpreter.getExample(9));
        menu.addCommand(Interpreter.getExample(10));*/
        menu.show();
    }

    private static IStmt composeStatement(Deque<IStmt> deq) {
        switch (deq.size()) {
            case 0:
                return new NopStmt();
            case 1:
                return deq.pollLast();
            default:
                IStmt first = deq.pollLast();
                return new CompStmt(first, composeStatement(deq));
        }
    }

    public static Controller getExample(int nr) throws Exception {
        IStack<IStmt> stk = new MyStack<>();
        IDict<String, IValue> symT = new Dict<>();
        IList<IValue> out = new MyList<>();
        IDict<StringValue, BufferedReader> fileTable = new Dict<>();
        IHeap<Integer, IValue> heap = new Heap<>();
        String logFileName = "log" + nr + ".txt";
        Deque<IStmt> statements = new ArrayDeque<>();
        switch (nr) {
            case 1 -> {
                statements.push(new VarDeclStmt("v", new IntType()));
                statements.push(new AssignStmt("v", new ValueExp(new IntValue(200))));
                statements.push(new PrintStmt(new VarExp("v")));
            }
            case 2 -> {
                statements.push(new VarDeclStmt("a", new IntType()));
                statements.push(new VarDeclStmt("b", new IntType()));
                statements.push(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)),
                        new ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))));
                statements.push(new AssignStmt("b", new ArithExp('+', new VarExp("a"),
                        new ValueExp(new IntValue(1)))));
                statements.push(new PrintStmt(new VarExp("b")));
            }
            case 3 -> {
                statements.push(new VarDeclStmt("a", new BoolType()));
                statements.push(new VarDeclStmt("v", new IntType()));
                statements.push(new AssignStmt("a", new ValueExp(new BoolValue(true))));
                statements.push(new IfStmt(new VarExp("a"),
                        new AssignStmt("v", new ValueExp(new IntValue(100))),
                        new AssignStmt("v", new ValueExp(new IntValue(1000)))));
                statements.push(new PrintStmt(new VarExp("v")));
            }
            case 4 -> {
                statements.push(new VarDeclStmt("varf", new StringType()));
                statements.push(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))));
                statements.push(new OpenRFileStmt(new VarExp("varf")));
                statements.push(new VarDeclStmt("varc", new IntType()));
                statements.push(new ReadFileStmt(new VarExp("varf"), "varc"));
                statements.push(new PrintStmt(new VarExp("varc")));
                statements.push(new ReadFileStmt(new VarExp("varf"), "varc"));
                statements.push(new PrintStmt(new VarExp("varc")));
                statements.push(new CloseRFileStmt(new VarExp("varf")));
            }
            case 5 -> {
                statements.push(new VarDeclStmt("v", new RefType(new IntType())));
                statements.push(new NewStmt("v", new ValueExp(new IntValue(20))));
                statements.push(new VarDeclStmt("a", new RefType(new RefType(new IntType()))));
                statements.push(new NewStmt("a", new VarExp("v")));
                statements.push(new PrintStmt(new VarExp("v")));
                statements.push(new PrintStmt(new VarExp("a")));
            }
            case 6 -> {
                statements.push(new VarDeclStmt("v", new RefType(new IntType())));
                statements.push(new NewStmt("v", new ValueExp(new IntValue(20))));
                statements.push(new VarDeclStmt("a", new RefType(new RefType(new IntType()))));
                statements.push(new NewStmt("a", new VarExp("v")));
                statements.push(new PrintStmt(new rHExp(new VarExp("v"))));
                statements.push(new PrintStmt(new ArithExp('+', new rHExp(new rHExp(new VarExp("a"))),
                        new ValueExp(new IntValue(5)))));
            }
            case 7 -> {
                statements.push(new VarDeclStmt("v", new RefType(new IntType())));
                statements.push(new NewStmt("v", new ValueExp(new IntValue(20))));
                statements.push(new PrintStmt(new rHExp(new VarExp("v"))));
                statements.push(new WHStmt("v", new ValueExp(new IntValue(30))));
                statements.push(new PrintStmt(new ArithExp('+', new rHExp(new VarExp("v")),
                        new ValueExp(new IntValue(5)))));
            }
            case 8 -> {
                statements.push(new VarDeclStmt("v", new RefType(new IntType())));
                statements.push(new NewStmt("v", new ValueExp(new IntValue(20))));
                statements.push(new VarDeclStmt("a", new RefType(new RefType(new IntType()))));
                statements.push(new NewStmt("a", new VarExp("v")));
                statements.push(new NewStmt("v", new ValueExp(new IntValue(30))));
                statements.push(new PrintStmt(new rHExp(new rHExp(new VarExp("a")))));
            }
            case 9 -> {
                statements.push(new VarDeclStmt("v", new IntType()));
                statements.push(new AssignStmt("v", new ValueExp(new IntValue(4))));
                Deque<IStmt> inner = new ArrayDeque<>();
                inner.push(new PrintStmt(new VarExp("v")));
                inner.push(new AssignStmt("v", new ArithExp('-', new VarExp("v"),
                        new ValueExp(new IntValue(1)))));
                statements.push(new WhileStmt(new RelExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                        Interpreter.composeStatement(inner)));
                statements.push(new PrintStmt(new VarExp("v")));
            }
            case 10 -> {
                statements.push(new VarDeclStmt("v", new IntType()));
                statements.push(new VarDeclStmt("a", new RefType(new IntType())));
                statements.push(new AssignStmt("v", new ValueExp(new IntValue(10))));
                statements.push(new NewStmt("a", new ValueExp(new IntValue(22))));
                Deque<IStmt> inner = new ArrayDeque<>();
                inner.push(new WHStmt("a", new ValueExp(new IntValue(30))));
                inner.push(new AssignStmt("v", new ValueExp(new IntValue(32))));
                inner.push(new PrintStmt(new VarExp("v")));
                inner.push(new PrintStmt(new rHExp(new VarExp("a"))));
                statements.push(new ForkStmt(Interpreter.composeStatement(inner)));
                statements.push(new PrintStmt(new VarExp("v")));
                statements.push(new PrintStmt(new rHExp(new VarExp("a"))));
                /*
                symtable checking
                statements.push(new NopStmt());
                statements.push(new NopStmt());
                */
            }
            default -> {
            }
        }
        IStmt ex = Interpreter.composeStatement(statements);
        IDict<String, IType> typeEnv = new Dict<>();
        ex.typeCheck(typeEnv);
        PrgState prg = new PrgState(stk, symT, out, fileTable, heap, ex);
        IRepo repo = new Repo(logFileName);
        Controller cont = new Controller(repo);
        cont.addProgram(prg);
        return cont;
        //return new View.RunCommand(Integer.toString(nr), ex.toString(), cont);
    }
}
