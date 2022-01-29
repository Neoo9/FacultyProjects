package Model;

import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.ADT.IList;
import Model.ADT.IStack;
import Model.Stmt.IStmt;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.util.concurrent.atomic.AtomicInteger;

import Exception.*;

public class PrgState {

    private final IStack<IStmt> exeStack;
    private final IDict<String, IValue> symTable;
    private final IList<IValue> out;
    private final IDict<StringValue, BufferedReader> fileTable;
    private final IHeap<Integer, IValue> heap;
    private final IStmt originalProgram;
    private static final AtomicInteger threadCount = new AtomicInteger(1);
    private final int id;

    public PrgState(IStack<IStmt> stk,
                    IDict<String, IValue> symT,
                    IList<IValue> output,
                    IDict<StringValue, BufferedReader> fileTable,
                    IHeap<Integer, IValue> heap,
                    IStmt prog) {
        this.exeStack = stk;
        this.symTable = symT;
        this.out = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.originalProgram = prog;
        stk.push(originalProgram);
        this.id = PrgState.manageThreadID();
    }

    public static synchronized int manageThreadID(){
        return threadCount.getAndAdd(1);
    }

    public int getId(){return this.id;}

    public IList<IValue> getOut() {
        return this.out;
    }

    public IStack<IStmt> getStack() {
        return this.exeStack;
    }

    public IDict<String, IValue> getSymTable() {
        return this.symTable;
    }

    public IDict<StringValue, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public IHeap<Integer, IValue> getHeap() {
        return this.heap;
    }

    public String getOriginalProgramString(){
        return this.originalProgram.toString();
    }

    public Boolean isNotCompleted(){
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws Exception {
        if (this.exeStack.isEmpty()) {
            throw new EmptyADTEXcep("PrgState: Execution stack is empty");
        }
        IStmt stmt = this.exeStack.pop();
        return stmt.execute(this);
    }

    public String toString() {
        return  "Thread ID: " + this.id + "\n"
                + "ExeStack:\n" + exeStack.toString() + "\n"
                + "SymbolTable:\n" + symTable.toString() + "\n"
                + "Output:\n" + out.toString() + "\n"
                + "FileTable:\n" + fileTable.toString() + "\n"
                + "Heap:\n" + heap.toString() + "\n"
                + "\n#################\n";
    }
}