package View.GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.net.URL;

public class MainInterpreter extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage mainStage) throws Exception {
        URL url = new File("MainLayout.fxml").toURI().toURL();
        Parent root = FXMLLoader.load(url);
        Scene scene = new Scene(root, 550, 250);
        mainStage.setTitle("Time to choose, Mr. Freeman...");
        mainStage.setResizable(false);
        mainStage.setScene(scene);
        mainStage.show();
    }
}
