package sample;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import java.io.IOException;
import javafx.application.Application;

// Date: April 2021
// Author: Shaharyar Choudhry
// Desc: Opens a GUI that displays a live graph with moisture values of the sensor. Also allows user to turn on
// watering pump using a button

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        var sp = SerialPortService.getSerialPort("COM3");
        var outputStream = sp.getOutputStream();
        var controller = new DataController();
        sp.addDataListener(controller);
        var slider = new Slider();
        var label = new Label();
        var pane = new BorderPane();
        var button = new Button("pump");

        slider.setMin(0.0);
        slider.setMax(100);

        slider.valueProperty().addListener(((observableValue, oldValue, newValue) -> {

            try {
                outputStream.write(newValue.byteValue());
            } catch (IOException e) {
                e.printStackTrace();
            }
            label.setText(String.valueOf(newValue.intValue()));
        }));


        button.setOnMouseReleased(value-> {
            try {
                outputStream.write(0);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        button.setOnMousePressed(value-> {
            try {
                outputStream.write(255);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });


        var now = System.currentTimeMillis();


        var xAxis = new NumberAxis("time", now, now + 50000, 10000); // creates the x-axis (which automatically updates)
        var yAxis = new NumberAxis("moisture value", 400, 800, 5); // creates the y-axis

        var series = new XYChart.Series<>(controller.getDataPoints()); // creates the series (all the data)
        var lineChart = new LineChart<>(xAxis, yAxis, FXCollections.singletonObservableList(series)); // creates the chart
        lineChart.setTitle("Plant Watering System");


        pane.setTop(slider);
        pane.setCenter(lineChart);
        pane.setRight(label);
        pane.setBottom(button);
        pane.setPadding(new Insets(0, 5, 0, 5));

        var scene = new Scene(pane, 800, 600);

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
