package Model.Stmt;

import Model.ADT.IDict;
import Model.ADT.IStack;
import Model.PrgState;
import Model.Types.IType;

public class CompStmt implements IStmt {
    private final IStmt first;
    private final IStmt second;

    public CompStmt(IStmt f, IStmt s) {
        this.first = f;
        this.second = s;
    }

    @Override
    public String toString() {
        return "(" + first.toString() + " " + second.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) {
        IStack<IStmt> stk = state.getStack();
        stk.push(second);
        stk.push(first);
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        return second.typeCheck(first.typeCheck(typeEnv));
    }

    public IStmt getFirst() {
        return this.first;
    }

    public IStmt getSecond() {
        return this.second;
    }
}

