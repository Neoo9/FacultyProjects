package Model.Stmt;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.Heap;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Types.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class NewStmt implements IStmt {
    private final String varName;
    private final Exp exp;

    public NewStmt(String name, Exp e) {
        this.varName = name;
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            IHeap<Integer, IValue> heap = state.getHeap();
            if (!symT.isDefined(varName)) {
                throw new UndefVarExcep("NewStmt: Undefined variable");
            }
            IValue varValue = symT.lookup(varName);
            IValue expValue = exp.eval(symT, heap);
            int heapPosition = ((Heap<Integer, IValue>) heap).getAvailable();
            heap.add(heapPosition, expValue);
            symT.update(varName, new RefValue(heapPosition, ((RefValue) varValue).getLocationType()));
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = typeEnv.lookup(varName);
        IType t2 = exp.typeCheck(typeEnv);
        if (!t1.equals(new RefType(t2))) {
            throw new InvalidTypeExcep("NewStmt: LHS and RHS have different types");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "new(" + varName + ", " + exp.toString() + ")";
    }
}
