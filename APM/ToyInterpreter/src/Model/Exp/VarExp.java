package Model.Exp;

import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.IType;
import Model.Values.IValue;

public class VarExp implements Exp {
    private final String id;

    public VarExp(String id) {
        this.id = id;
    }

    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) throws Exception {
        if (!symTable.isDefined(this.id))
            throw new UndefVarExcep("VarExp: Undefined variable");
        return symTable.lookup(id);
    }

    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        return typeEnv.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }

}
