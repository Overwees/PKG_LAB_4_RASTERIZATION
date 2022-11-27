#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QVector>
#include <QCheckBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void DrawPlot();
    void ClearPlots();
    void ChooseAlgorithm(int);
private:
        QHBoxLayout* Box = new QHBoxLayout(this);
        QVBoxLayout* Left = new QVBoxLayout(this);
        QVBoxLayout* Right = new QVBoxLayout(this);
        QComboBox* cbAlgoth = new QComboBox(this);
        QGroupBox* gbLine = new QGroupBox(this);
        QGroupBox* gbCircle = new QGroupBox(this);
        QPushButton* pbDraw = new QPushButton("&Нарисовать",this);
        QPushButton* pbClear = new QPushButton("&Очистить",this);
        QCheckBox* cbIsSmooth = new QCheckBox(this);
    QCustomPlot* plot;
    QLineEdit* leMass[7]{new QLineEdit,new QLineEdit,new QLineEdit,new QLineEdit,new QLineEdit,new QLineEdit,new QLineEdit};
        void LayoutSettings();
        void darkTheme();
        void DrawStepByStep(int x0,int y0,int x1,int y1);
        void DrawByBrezenhemLine(int x0,int y0,int x1,int y1);
        void DrawByDDA(int x0,int y0,int x1,int y1);
        void DrawByBrezenhemCircle(int x0,int y0,int R);
        int algorithm;
        int currentGraph;
        QVector <int> coordX;
        QVector <int> coordY;
};
#endif // MAINWINDOW_H
