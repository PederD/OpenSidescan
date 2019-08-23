#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTabWidget>
#include <string>
#include <iostream>
#include "imagetab.h"
#include "aboutdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tabs(new QTabWidget),
    images(NULL)
{
    ui->setupUi(this);
    buildUI();

    statusBar()->showMessage("Load a sidescan file using File->Open menu");
}

void MainWindow::buildUI(){
    this->setCentralWidget(tabs);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scrollArea;
    delete imageLabel;
}

void MainWindow::actionOpen(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::homePath(), tr("Sidescan Files (*.xtf)"));
    std::string sFileName= fileName.toStdString();

    if(fileName.size() > 0){
        try{
            statusBar()->showMessage("Loading sidescan data...");
            if(images != NULL){
                //FIXME: clear tabs
                for(auto i=images->begin();i!= images->end();i++){
                    delete *i;
                }

                tabs->clear(); //Does this leak?

                images->clear();
            }

            //TODO: Add progress bar
            SidescanImager imager;
            DatagramParser * parser = DatagramParserFactory::build(sFileName,imager);
            parser->parse(sFileName);
            images = imager.generateImages();

            int n = 0;
            for(auto i= images->begin();i!=images->end();i++){

                std::stringstream ss;

                ss << "Channel " << n;

                ImageTab* newTab = new ImageTab(*i);

                tabs->addTab(newTab,ss.str().c_str());
                n++;
            }

            delete parser;

            statusBar()->showMessage("Sidescan data loaded");
        }
        catch(std::exception * e){
            //TODO: whine message box
            std::cerr << e->what() << std::endl;
        }
    }
}



void MainWindow::actionQuit(){
    this->close();
}

void MainWindow::actionAbout(){
    AboutDialog about(this);

    about.exec();
}

