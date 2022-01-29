package Model.Stmt;

import Exception.AlreadyDefVarExcep;
import Exception.IOException;
import Exception.InvalidTypeExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Types.RefType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;

public class OpenRFileStmt implements IStmt {
    private final Exp path;

    public OpenRFileStmt(Exp fp) {
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
                if (fileT.isDefined((StringValue) pathValue)) {
                    throw new AlreadyDefVarExcep("OpenRFileStmt: File path already defined in file table");
                }
                String pathString = ((StringValue) pathValue).getValue();
                try {
                    BufferedReader buf = new BufferedReader(new FileReader(pathString));
                    fileT.add((StringValue) pathValue, buf);
                    return null;
                } catch (Exception e) {
                    throw new IOException("OpenRFile: Error when opening file");
                }
            }
        }
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = path.typeCheck(typeEnv);
        if (!t1.equals(new StringType())) {
            throw new InvalidTypeExcep("OpenRFileStmt: Path must be a string");
        }
        return typeEnv;

    }

    @Override
    public String toString() {
        return "openRFile(" + this.path + ");";
    }
}
