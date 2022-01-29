package Model.Stmt;

import Exception.InvalidTypeExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.ADT.IStack;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class WhileStmt implements IStmt {
    private final Exp exp;
    private final IStmt stmt;
    private final boolean val;

    public WhileStmt(Exp e, IStmt s) {
        this.exp = e;
        this.stmt = s;
        this.val = true;
    }

    public WhileStmt(Exp e, IStmt s, boolean v) {
        this.exp = e;
        this.stmt = s;
        this.val = v;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IStack<IStmt> stk = state.getStack();
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            IHeap<Integer, IValue> heap = state.getHeap();
            IValue expValue = exp.eval(symT, heap);
            if (((BoolValue) expValue).getValue() == this.val) {
                stk.push(this);
                stk.push(stmt);
            }
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = exp.typeCheck(typeEnv);
        if (!t1.equals(new BoolType())) {
            throw new InvalidTypeExcep("WhileStmt: Condition is not a bool");
        }
        stmt.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        String str = !val ? "!" : "";
        return "while(" + str + exp.toString() + ") {" + stmt.toString() + "}";
    }
}
