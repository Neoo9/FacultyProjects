package Model.Stmt;

import Model.ADT.IDict;
import Model.ADT.IStack;
import Model.ADT.MyStack;
import Model.PrgState;
import Model.Types.IType;
import Model.Values.IValue;

public class ForkStmt implements IStmt {
    IStmt stmt;

    public ForkStmt(IStmt s) {
        this.stmt = s;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        synchronized (state.getOut()) {
            synchronized (state.getFileTable()) {
                synchronized (state.getHeap()) {
                    IStack<IStmt> stk = new MyStack<>();
                    IDict<String, IValue> symT = state.getSymTable().clone();
                    return new PrgState(stk, symT, state.getOut(), state.getFileTable(), state.getHeap(), this.stmt);
                }
            }
        }
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        stmt.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + stmt.toString() + ")";
    }
}
