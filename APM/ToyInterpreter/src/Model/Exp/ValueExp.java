package Model.Exp;

import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.IType;
import Model.Values.IValue;

public class ValueExp implements Exp {
    private final IValue number;

    public ValueExp(IValue nr) {
        this.number = nr;
    }

    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) {
        return number;
    }

    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        return this.number.getType();
    }

    @Override
    public String toString() {
        return number.toString();
    }
}
