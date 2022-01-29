package View.GUI;

import Controller.Controller;
import View.Console.Interpreter;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class PrgListController implements Initializable {
    @FXML
    ListView<Controller> myPrgList;
    @FXML
    Button runButton;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        ObservableList<Controller> myData = FXCollections.observableArrayList();
        for (int i = 1; i <= 10; i++) {
            try {
                myData.add(Interpreter.getExample(i));
            }
            catch(Exception e){
                PrgRunController.showInfo(new Alert(Alert.AlertType.ERROR), "Error on example " + i, e.getMessage());
                System.exit(1);
            }
        }
        myPrgList.setItems(myData);
        myPrgList.getSelectionModel().selectFirst();
        runButton.setOnAction(e -> {
            Stage programStage = new Stage();
            Parent programRoot;
            Callback<Class<?>, Object> controllerFactory = type -> {
                if (type == PrgRunController.class) {
                    return new PrgRunController(myPrgList.getSelectionModel().getSelectedItem());
                } else {
                    try {
                        return type.getDeclaredConstructor().newInstance();
                    } catch (Exception exc) {
                        System.err.println("Could not create controller for " + type.getName());
                        throw new RuntimeException(exc);
                    }
                }
            };
            try {
                URL url = new File("ProgramLayout.fxml").toURI().toURL();
                FXMLLoader fxmlLoader = new FXMLLoader(url);
                fxmlLoader.setControllerFactory(controllerFactory);
                programRoot = fxmlLoader.load();
                Scene programScene = new Scene(programRoot);
                programStage.setTitle("Running program");
                programStage.setScene(programScene);
                programStage.show();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        });
    }
}
