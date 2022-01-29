package Model.Stmt;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Types.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class WHStmt implements IStmt {
    private final String varName;
    private final Exp exp;

    public WHStmt(String name, Exp e) {
        this.varName = name;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            IHeap<Integer, IValue> heap = state.getHeap();
            if (!symT.isDefined(varName)) {
                throw new UndefVarExcep("WHStmt: Undefined variable");
            }
            IValue varValue = symT.lookup(varName);
            int heapPosition = ((RefValue) varValue).getAddress();
            if (!heap.isDefined(heapPosition)) {
                throw new UndefVarExcep("WHStmt: Undefined variable in heap");
            }
            IValue expValue = exp.eval(symT, heap);
            heap.update(heapPosition, expValue);
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = typeEnv.lookup(varName);
        IType t2 = exp.typeCheck(typeEnv);
        if (!t1.equals(new RefType(t2))) {
            throw new InvalidTypeExcep("WHStmt: LHS and RHS have different types");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "wH(" + varName + ", " + exp.toString() + ")";
    }
}
