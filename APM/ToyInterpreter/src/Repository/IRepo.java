package Repository;

import Model.ADT.IList;
import Model.PrgState;

public interface IRepo {
    void addPrg(PrgState newPrg);

    void logPrgStateExec(PrgState state) throws Exception;

    void clearFile() throws Exception;

    IList<PrgState> getPrgList();

    void setPrgList(IList<PrgState> li);
}
