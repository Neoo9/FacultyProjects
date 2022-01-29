package Model.Stmt;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;

public class CloseRFileStmt implements IStmt {
    private final Exp path;

    public CloseRFileStmt(Exp fp) {
        this.path = fp;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            synchronized (state.getFileTable()) {
                IHeap<Integer, IValue> heap = state.getHeap();
                IDict<StringValue, BufferedReader> fileT = state.getFileTable();
                IValue pathValue = this.path.eval(symT, heap);
                if (!fileT.isDefined((StringValue) pathValue)) {
                    throw new UndefVarExcep("CloseRFileStmt: File path not defined");
                }
                BufferedReader buf = fileT.lookup((StringValue) pathValue);
                buf.close();
                fileT.remove((StringValue) pathValue);
            }
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t = path.typeCheck(typeEnv);
        if (!t.equals(new StringType())) {
            throw new InvalidTypeExcep("CloseRFileStmt: Path is not a string");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "closeFile(" + this.path + ");";
    }
}
