package Model.Exp;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.IType;
import Model.Types.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class rHExp implements Exp {
    private final Exp exp;

    public rHExp(Exp e) {
        this.exp = e;
    }

    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) throws Exception {
        IValue expValue = this.exp.eval(symTable, heap);
        int addr = ((RefValue) expValue).getAddress();
        if (!heap.isDefined(addr)) {
            throw new UndefVarExcep("rHExp: Undefined variable in heap");
        }
        return heap.lookup(addr);

    }

    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t = exp.typeCheck(typeEnv);
        if (!(t instanceof RefType r)) {
            throw new InvalidTypeExcep("rHExp: TypeCheck - Operand is not a reference");
        }
        return r.getInner();
    }

    @Override
    public String toString() {
        return "rH(" + exp.toString() + ")";
    }
}
