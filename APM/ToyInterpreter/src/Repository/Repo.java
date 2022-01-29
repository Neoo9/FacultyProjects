package Repository;

import Model.ADT.IList;
import Model.ADT.MyList;
import Model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

public class Repo implements IRepo {
    private IList<PrgState> myPrgStates;
    private final String logFilePath;

    public Repo(String path) {
        this.logFilePath = path;
        this.myPrgStates = new MyList<>();
    }

    @Override
    public void logPrgStateExec(PrgState state) throws Exception {
        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.append(state.toString());
        logFile.close();
    }

    @Override
    public void addPrg(PrgState newPrg) {
        myPrgStates.add(newPrg);
    }

    @Override
    public void clearFile() throws Exception {
        FileWriter fw = new FileWriter(logFilePath);
        fw.close();
    }

    @Override
    public IList<PrgState> getPrgList() {
        return this.myPrgStates;
    }

    @Override
    public void setPrgList(IList<PrgState> li) {
        this.myPrgStates = li;
    }

}
