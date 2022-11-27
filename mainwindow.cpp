#include "mainwindow.h"
#include <QVector>
#include "qcustomplot.h"
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LayoutSettings();
    darkTheme();
    this->algorithm = 0;
    this->currentGraph = -1;
    this->cbIsSmooth->setChecked(true);
    connect(this->pbDraw,SIGNAL(clicked()),SLOT(DrawPlot()));
    connect(this->pbClear,SIGNAL(clicked()),SLOT(ClearPlots()));
    connect(this->cbAlgoth,SIGNAL(activated(int)),SLOT(ChooseAlgorithm(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::LayoutSettings()
{
    QWidget* wgt = new QWidget;
    plot = new QCustomPlot;
    this->plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->plot->setInteraction(QCP::iRangeDrag,true);
    this->plot->setInteraction(QCP::iRangeZoom,true);
    this->plot->xAxis->setRange(-1000, 1000);
    this->plot->yAxis->setRange(-1000, 1000);
    this->plot->xAxis->setLabel("x");
    this->plot->yAxis->setLabel("y");
    this->plot->replot();
    this->Left->addWidget(this->plot);
    QHBoxLayout* buttons = new QHBoxLayout(this);
    QHBoxLayout* smooth = new QHBoxLayout(this);
    buttons->addWidget(this->pbDraw);
    buttons->addWidget(this->pbClear);
     smooth->addWidget(new QLabel("Сглаживание:",this));
    smooth->addWidget(this->cbIsSmooth);
    smooth->setAlignment(Qt::AlignmentFlag::AlignRight);
    buttons->addLayout(smooth);
    this->Left->addLayout(buttons);
    this->Box->addLayout(this->Left);

    QStringList strl;
            strl <<" Пошаговый алгоритм"<<" Алгоритм ЦДА"<<" Алгоритм Брезенхема(Линия)"<<" Алгоритм Брезенхема (окружность)";
    this->cbAlgoth->addItems(strl);
    this->gbLine->setTitle("Линия");
    for (int i = 0; i < 7; i++)
        this->leMass[i]->setFixedWidth(70);
    QVBoxLayout* Vbox = new QVBoxLayout(this);
    QHBoxLayout* lbox1 = new QHBoxLayout(this);
    QHBoxLayout* lbox2 = new QHBoxLayout(this);
    QHBoxLayout* lbox3 = new QHBoxLayout(this);
    QHBoxLayout* lbox4 = new QHBoxLayout(this);
    lbox1->addWidget(new QLabel("X начала"));
    lbox2->addWidget(new QLabel("Y начала"));
    lbox3->addWidget(new QLabel("X конца"));
    lbox4->addWidget(new QLabel("Y Конца"));
    lbox1->addWidget(this->leMass[0]);
    lbox2->addWidget(this->leMass[1]);
    lbox3->addWidget(this->leMass[2]);
    lbox4->addWidget(this->leMass[3]);
    Vbox->addLayout(lbox1);
    Vbox->addLayout(lbox2);
    Vbox->addLayout(lbox3);
    Vbox->addLayout(lbox4);
    this->gbLine->setLayout(Vbox);
    this->gbCircle->setTitle("Окружность");
    QVBoxLayout* VboxC = new QVBoxLayout(this);
    QHBoxLayout* lbox1C = new QHBoxLayout(this);
    QHBoxLayout* lbox2C = new QHBoxLayout(this);
    QHBoxLayout* lbox3C = new QHBoxLayout(this);
    lbox1C->addWidget(new QLabel("X центра"));
    lbox2C->addWidget(new QLabel("Y цента"));
    lbox3C->addWidget(new QLabel("Радиус"));
    lbox1C->addWidget(this->leMass[4]);
    lbox2C->addWidget(this->leMass[5]);
    lbox3C->addWidget(this->leMass[6]);
    VboxC->addLayout(lbox1C);
    VboxC->addLayout(lbox2C);
    VboxC->addLayout(lbox3C);
    this->gbCircle->setLayout(VboxC);
    this->Right->addWidget(this->cbAlgoth);
    this->Right->addWidget(this->gbLine);
    this->Right->addWidget(this->gbCircle);
    this->Box->addLayout(this->Right);
    this->gbLine->setFixedWidth(150);
    this->gbCircle->setFixedWidth(150);
    this->cbAlgoth->setFixedWidth(150);
    wgt->setLayout(this->Box);
    this->setCentralWidget(wgt);
    this->setMinimumSize(700,500);
}

void MainWindow::darkTheme()
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}

void MainWindow::DrawPlot()
{
    int k = this->algorithm;
    int x0 = leMass[0]->text().toInt();
    int y0 = leMass[1]->text().toInt();
    int x1 = leMass[2]->text().toInt();
    int y1 = leMass[3]->text().toInt();
    int x = leMass[4]->text().toInt();
    int y = leMass[5]->text().toInt();
    int R = leMass[6]->text().toInt();
    switch(k)
    {
    case 0:

        DrawStepByStep(x0,y0,x1,y1);
        break;
    case 1:
        DrawByDDA(x0,y0,x1,y1);
        break;
    case 2:
        DrawByBrezenhemLine(x0,y0,x1,y1);
        break;
    case 3:
        DrawByBrezenhemCircle(x,y,R);
        break;
    }
}

void MainWindow::ClearPlots()
{
    this->plot->clearGraphs();
    this->currentGraph = -1;
    this->plot->replot();
}

void MainWindow::ChooseAlgorithm(int i)
{
    this->algorithm = i;
}

void MainWindow::DrawStepByStep(int x0,int y0,int x1,int y1)
{
    this->plot->addGraph();
        currentGraph++;
        if (this->cbIsSmooth->isChecked())
                this->plot->graph(currentGraph)->setAntialiased(true);
           else
                this->plot->graph(currentGraph)->setAntialiased(false);
    if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        if (x0 == x1)
        {
            this->plot->graph(currentGraph)->addData(x0, y0);
            this->plot->graph(currentGraph)->addData(x1, y1);
            this->plot->replot();
        }
        else
        {
            double k = (double)(y1-y0)/(double)(x1-x0);
            double b = y0 - k * x0;
            this->plot->graph(currentGraph)->addData(x0, y0);
            int x = x0;
            int y = y0;
            while(x < x1)
            {
                x++;
                y=round(k * x + b);
                 this->plot->graph(currentGraph)->addData(x, y);
                 this->plot->replot();
            }
        }
}

void MainWindow::DrawByBrezenhemLine(int x0,int y0,int x1,int y1)
{
    this->plot->addGraph();
        currentGraph++;
        this->plot->addGraph();
            currentGraph++;
            if (this->cbIsSmooth->isChecked())
                    this->plot->graph(currentGraph)->setAntialiased(true);
               else
                    this->plot->graph(currentGraph)->setAntialiased(false);
    bool steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep)
        {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dx = x1 - x0;
        int dy = abs(y1 - y0);
        int error = dx / 2;
        int ystep = (y0 < y1) ? 1 : -1;
        int y = y0;
        for (int x = x0; x <= x1; x++)
        {
            this->plot->graph(currentGraph)->addData(steep ? y : x, steep ? x : y);
            this->plot->replot();
            error -= dy;
            if (error < 0)
            {
                y += ystep;
                error += dx;
            }
        }
}

void MainWindow::DrawByDDA(int x0,int y0,int x1,int y1)
{
    this->plot->addGraph();
        currentGraph++;
        this->plot->addGraph();
            currentGraph++;
            if (this->cbIsSmooth->isChecked())
                    this->plot->graph(currentGraph)->setAntialiased(true);
               else
                    this->plot->graph(currentGraph)->setAntialiased(false);
    if (x0 > x1)
       {
           std::swap(x0, x1);
           std::swap(y0, y1);
       }

       float x = x0;
       float y = y0;
       float dx = x1 - x0;
       float dy = y1 - y0;
       float l = std::max(dx, dy);
       this->plot->graph(currentGraph)->addData(x0, y0);
       int i = 0;
       while (i < l)
       {
           y += dy/l;
           x += dx/l;
           this->plot->graph(currentGraph)->addData(trunc(x), trunc(y));
           this->plot->replot();
           ++i;
       }
}

void MainWindow::DrawByBrezenhemCircle(int x,int y,int R)
{
    this->plot->addGraph();
        currentGraph++;
        this->plot->addGraph();
            currentGraph++;
            if (this->cbIsSmooth->isChecked())
                    this->plot->graph(currentGraph)->setAntialiased(true);
               else
                    this->plot->graph(currentGraph)->setAntialiased(false);
    if (R == 1)
        {
            this->plot->addGraph();
            this->plot->addGraph();
            this->plot->addGraph();

            this->plot->graph(currentGraph)->addData (x + 1, y);
            this->plot->graph(currentGraph)->addData (x, y + 1);
            this->plot->graph(currentGraph+1)->addData (x, y + 1);
            this->plot->graph(currentGraph+1)->addData (x - 1, y);
            this->plot->graph(currentGraph+2)->addData (x - 1, y);
            this->plot->graph(currentGraph+2)->addData (x, y - 1);
            this->plot->graph(currentGraph+3)->addData (x, y - 1);
            this->plot->graph(currentGraph+3)->addData (x + 1, y);
            this->plot->replot();
            this->currentGraph += 3;
            return;
        }

        this->plot->addGraph();
        this->plot->addGraph();
        this->plot->addGraph();
        this->plot->addGraph();
        this->plot->addGraph();
        this->plot->addGraph();
        this->plot->addGraph();

        int x2 = R;
        int y2 = 0;
        int radiusError = 1 - x2;

        this->plot->graph(currentGraph+1)->addData(y2 + x, x2 + y);
        this->plot->graph(currentGraph+2)->addData(-x2 + x, y2 + y);
        this->plot->graph(currentGraph+4)->addData(-x2 + x, -y2 + y);
        this->plot->graph(currentGraph+7)->addData(y2 + x, -x2 + y);

        coordX.push_back(x2);
        coordY.push_back(y2);

        while (x2 >= y2)
        {
            y2++;
            if (radiusError < 0)
            {
                radiusError += 2 * y2 + 1;
            }
            else
            {
                x2--;
                radiusError += 2 * (y2 - x2 + 1);
            }
            this->plot->graph(currentGraph+1)->addData(y2 + x, x2 + y);
            this->plot->graph(currentGraph+2)->addData(-x2 + x, y2 + y);
            this->plot->graph(currentGraph+4)->addData(-x2 + x, -y2 + y);
            this->plot->graph(currentGraph+7)->addData(y2 + x, -x2 + y);
            this->plot->replot();

            coordX.push_back(x2);
            coordY.push_back(y2);
        }

        for(int i = coordX.size() - 1; i >= 0; i--)
        {
            this->plot->graph(currentGraph)->addData(coordX[i] + x, coordY[i] + y);
            this->plot->graph(currentGraph+3)->addData(-coordY[i] + x, coordX[i]  + y);
            this->plot->graph(currentGraph+5)->addData(-coordY[i] + x, -coordX[i]  + y);
            this->plot->graph(currentGraph+6)->addData(coordX[i]  + x, -coordY[i] + y);
            this->plot->replot();
        }

        currentGraph+=7;
        this->plot->replot();
        coordX.clear();
        coordY.clear();
}
