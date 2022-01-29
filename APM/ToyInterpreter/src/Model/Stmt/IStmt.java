package Model.Stmt;

import Model.ADT.IDict;
import Model.PrgState;
import Model.Types.IType;

public interface IStmt {
    PrgState execute(PrgState state) throws Exception;
    IDict<String, IType> typeCheck(IDict<String,IType> typeEnv) throws Exception;
    String toString();
}
