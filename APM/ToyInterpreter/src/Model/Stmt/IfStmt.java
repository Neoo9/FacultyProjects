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

import java.util.Objects;

public class IfStmt implements IStmt {
    private final IStmt st1;
    private final IStmt st2;
    private final Exp ex;

    public IfStmt(Exp exp, IStmt stat1, IStmt stat2) {
        this.ex = exp;
        this.st1 = stat1;
        this.st2 = stat2;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IStack<IStmt> stk = state.getStack();
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            IHeap<Integer, IValue> heap = state.getHeap();
            IValue cond = ex.eval(symT, heap);
            if (((BoolValue) cond).getValue()) {
                stk.push(st1);
            } else {
                stk.push(st2);
            }
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = ex.typeCheck(typeEnv);
        if (!t1.equals(new BoolType())) {
            throw new InvalidTypeExcep("IfStmt: Condition is not a bool");
        }
        st1.typeCheck(typeEnv.clone());
        st2.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "if " + this.ex.toString() + " then " + this.st1.toString() + " else " + this.st2.toString();
    }
}
