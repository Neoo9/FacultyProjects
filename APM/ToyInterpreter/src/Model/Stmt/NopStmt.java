package Model.Stmt;

import Model.ADT.IDict;
import Model.PrgState;
import Model.Types.IType;

public class NopStmt implements IStmt {

    @Override
    public PrgState execute(PrgState state) {
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "no_operation;";
    }
}
