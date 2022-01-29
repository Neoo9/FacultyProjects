package Model.Exp;

import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.IType;
import Model.Values.IValue;

public interface Exp {

    IValue eval(IDict<String, IValue> symTable,
                IHeap<Integer, IValue> heap) throws Exception;
    IType typeCheck(IDict<String, IType> typeEnv) throws Exception;
    String toString();
}
