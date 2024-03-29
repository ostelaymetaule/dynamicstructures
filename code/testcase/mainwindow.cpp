#include "mainwindow.h"
#include "ui_mainwindow.h"

//visual widgets
GraphWidget* graphForestView;
GraphWidget* graphMapView;

ForestLogic* forestGenerator;
ScenarioHandler* mapGenerator;
//Graph* forest, map;

LogWindow* mDebugLog;



//file actions
QAction* newAct;
QAction* saveAct;
QAction* loadAct;
QAction* saveResultAct;
QAction* openAct;

//edit tools
QAction* deleteItemAct;
QAction* selectItemAct;
QAction* nodeDrawModeAct;
QAction* edgeDrawModeAct;
QAction* clearProblemWidgetAct;


//view actions
QAction* viewDebugLogDialogAct;

//procedure actions
QAction* createProblemStructureAct;

LogDialog* logDebugDialog;
ProblemPresetDialog* presetDialog;


QToolBar* mDrawTools;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

   ui->setupUi(this);
   this->setWindowTitle("Map Structure Search");

    logDebugDialog= new LogDialog(0);
    presetDialog= new ProblemPresetDialog(0);
presetDialog->hide();

   mDebugLog= logDebugDialog->getLogWindow();

initActions();
//initMainToolBar();
initMenu();
//initGraphManipulationToolBar();


    //forest graph widget:

   graphForestView= new GraphWidget(ui->parent_forest_widget,ui->problemWidget);
   graphForestView->setLogWindow(mDebugLog);
   graphForestView->resize(ui->parent_forest_widget->width(),ui->parent_forest_widget->height());
   graphForestView->show();

   //pre-settings for forest:
    QString param;
   this->ui->editWidth->setText(param.setNum(500));
   this->ui->editHeight->setText(param.setNum(500));
   this->ui->editMaxNodeSpan->setText(param.setNum(100));
   this->ui->editMinNodeSpan->setText(param.setNum(50));
   this->ui->editMinConnections->setText(param.setNum(0));
   this->ui->editMaxConnections->setText(param.setNum(5));
   this->ui->editLocalNeighbourRange->setText(param.setNum(200));
   this->ui->editNodeDensity->setText(param.setNum(70));

   //pre-settings for map:
   this->ui->editSpanningPoints->setText(param.setNum(4));
   this->ui->editLocalFightPoints->setText(param.setNum(4));
   this->ui->editPathIterations->setText(param.setNum(3));

   //map graph widget
   graphMapView= new GraphWidget(ui->parent_map_widget,ui->solutionWidget);
   graphMapView->resize(ui->parent_map_widget->width(),ui->parent_map_widget->height());
   graphMapView->show();
   graphMapView->setLogWindow(mDebugLog);
   graphMapView->removeAllActionsFromToolBar();
   graphMapView->addCopyFromWidgetAction(graphForestView);

   forestGenerator = new ForestLogic();
   // forestGenerator

    mapGenerator= new ScenarioHandler(graphForestView,graphMapView);

    forestGenerator->setDebugTextBox(mDebugLog);
    mapGenerator->setDebugTextBox(mDebugLog);
    logDebugDialog->show();
}


void MainWindow::closeEvent(QCloseEvent* e)
{
 mDebugLog->log("closing");
     logDebugDialog->close();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete logDebugDialog;
	//test
}

void MainWindow::on_btnGenerateForest_clicked()
{
    createProblemStructure();
}


void MainWindow::on_btnExecuteSpanningStep_clicked()
{
  setMapParams();
  mapGenerator->findSpanningPoints();

}

void MainWindow::on_btnForestFullScreen_clicked()
{
    graphForestView->showFullScreen();
}

void MainWindow::on_btnExecutePathFinder_clicked()
{
    setMapParams();
    mapGenerator->executeMultiplePathFinder();


}

void MainWindow::on_btnLocateFightPoints_clicked()
{
   setMapParams();
   mapGenerator->executeLFPfinder();
}




void  MainWindow::initMainToolBar()
{}

void  MainWindow::initGraphManipulationToolBar()
{



     //mDrawTools->addAction(deleteItemAct);
     //select item
     //mDrawTools->addAction(selectItemAct);
    //clear canvas
     //mDrawTools->addAction(clearProblemWidgetAct);

}


  void  MainWindow::uncheckAllGraphWidgetActions()
  {
    //draw actions
    nodeDrawModeAct->setChecked(false);
    edgeDrawModeAct->setChecked(false);
    deleteItemAct->setChecked(false);
    selectItemAct->setChecked(false);
  }


void  MainWindow::addNodes()
{

    if (nodeDrawModeAct->isChecked())
    {
         mDebugLog->log("node draw tool activated");
         uncheckAllGraphWidgetActions();
         nodeDrawModeAct->setChecked(true);


    }else{
        mDebugLog->log("node draw tool deactivated",failure_msg);
    }

}
void  MainWindow::addEdges()
{


    if (edgeDrawModeAct->isChecked())
    {
         mDebugLog->log("edge draw tool activated");
         uncheckAllGraphWidgetActions();
         edgeDrawModeAct->setChecked(true);

    }else{
        mDebugLog->log("edge draw tool deactivated",failure_msg);
    }


}
void  MainWindow::deleteTool()
{
   if (deleteItemAct->isChecked())
    {
         mDebugLog->log("delete tool activated");
         uncheckAllGraphWidgetActions();
         deleteItemAct->setChecked(true);
    }else{
        mDebugLog->log("delete tool deactivated",failure_msg);
    }



}
void  MainWindow::selectTool()
{
   if (selectItemAct->isChecked())
    {
         mDebugLog->log("select tool activated");
         uncheckAllGraphWidgetActions();
         selectItemAct->setChecked(true);
    }else{
        mDebugLog->log("select tool deactivated",failure_msg);
    }

}

void MainWindow::openProblem()
{
    QString fileName;
     fileName = QFileDialog::getOpenFileName(this,
     tr("Open Problem File"), "/Saved", tr("Game Structure Problem (*.gsp)"));

}

void MainWindow::saveProblem()
{
     QString fileName;
     fileName = QFileDialog::getSaveFileName(this,
     tr("Save Problem File"), "Saved", tr("Space Structure Problem (*.ssp)"));
     mapGenerator->getForestWidget()->saveToFile(fileName);

}


void MainWindow::saveResult()
{
     QString fileName;
     fileName = QFileDialog::getSaveFileName(this,
     tr("Save Result File"), "Saved", tr("Space Structure Result(*.ssr)"));
     mapGenerator->getForestWidget()->saveToFile(fileName);

}


void MainWindow::newProblem()
{
    //QString fileName;
    // fileName = QFileDialog::getOpenFileName(this,
    // tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
}

void MainWindow::createProblemStructure()
{

    //clear both canvases

graphForestView->clearGraph();
graphMapView->clearGraph();

    mapGenerator->setForestWidget(graphForestView);
    mapGenerator->setMapWidget(graphMapView);

unsigned int width = this->ui->editWidth->text().toUInt();
unsigned int height =this->ui->editHeight->text().toUInt();

    forestParams f;
    f.density=1;
    f.layers=4;
    f.min_node_span=this->ui->editMinNodeSpan->text().toUInt();
    f.max_node_span=this->ui->editMaxNodeSpan->text().toUInt();
    f.scatterMethod=this->ui->cmbScatterMethod->currentIndex();
    f.min_connections_per_node= this->ui->editMinConnections->text().toUInt();
    f.max_connections_per_node= this->ui->editMaxConnections->text().toUInt();
    f.range_local_neighbours=this->ui->editLocalNeighbourRange->text().toUInt();
    f.node_density= this->ui->editNodeDensity->text().toUInt();
    f.area= QRect(0,0,width,height);

    forestGenerator->createForestGraph(graphForestView, f);
}

void MainWindow::initActions()
{

//new
    newAct = new QAction(QIcon("icons/new.png"), tr("&New..."), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Open an existing configuration"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newProblem()));

//open
    openAct = new QAction(QIcon("icons/open.png"), tr("&Open State..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing configuration"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openProblem()));

//save problem
    saveAct = new QAction(QIcon("icons/save.png"), tr("&Save State..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save Problem"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveProblem()));


//save result
    saveResultAct = new QAction(QIcon("icons/save.png"), tr("&Save Result..."), this);
    saveResultAct->setShortcuts(QKeySequence::Save);
    saveResultAct->setStatusTip(tr("Save Result"));
    connect(saveResultAct, SIGNAL(triggered()), this, SLOT(saveResult()));

    //add vertex
    nodeDrawModeAct = new QAction(QIcon("icons/addnode.png"), tr("&New Node..."), this);
    nodeDrawModeAct->setStatusTip(tr("Place Nodes"));
    connect( nodeDrawModeAct, SIGNAL(triggered()), this, SLOT(addNodes()));
    nodeDrawModeAct->setCheckable(true);



    //add edge
     edgeDrawModeAct = new QAction(QIcon("icons/addedge.png"), tr("&New Edge..."), this);
     edgeDrawModeAct->setStatusTip(tr("Place Nodes"));
     connect(edgeDrawModeAct, SIGNAL(triggered()), this, SLOT(addEdges()));
     edgeDrawModeAct->setCheckable(true);


     //delete item
     deleteItemAct = new QAction(QIcon("icons/delete.png"), tr("&Delete Item..."), this);
     deleteItemAct->setStatusTip(tr("Delete Item"));
     connect(deleteItemAct, SIGNAL(triggered()), this, SLOT(deleteTool()));
     deleteItemAct->setCheckable(true);

     //select item
     selectItemAct = new QAction(QIcon("icons/accept.png"), tr("&Select item..."), this);
     selectItemAct->setStatusTip(tr("Select"));
     connect(selectItemAct, SIGNAL(triggered()), this, SLOT(selectTool()));
     selectItemAct->setCheckable(true);


     clearProblemWidgetAct = new QAction(QIcon("icons/delete.png"), tr("&Clear Problem..."), this);
     clearProblemWidgetAct->setStatusTip(tr("Clear Problem Space"));
     connect( clearProblemWidgetAct, SIGNAL(triggered()), this, SLOT(clearProblemStructure()));


     //view
     viewDebugLogDialogAct = new QAction(QIcon("icons/accept.png"), tr("&LogWindow..."), this);
     viewDebugLogDialogAct->setStatusTip(tr("Show Log Window"));
     connect( viewDebugLogDialogAct, SIGNAL(triggered()), this, SLOT(showLogWindow()));



}

void MainWindow::showLogWindow()
{
logDebugDialog->show();
}

void MainWindow::clearProblemStructure()
{
    mDebugLog->log("Problem Structure Cleared");
}

void MainWindow::setMapParams()
{
    Scenario scenario;
    scenario.spanning_points=this->ui->editSpanningPoints->text().toUInt();
    scenario.local_fight_points = this->ui->editLocalFightPoints->text().toUInt();
    scenario.multiple_path_iterations= this->ui->editPathIterations->text().toUInt();

    scenario.spanMethod=this->ui->cmbSpanMethod->currentIndex();
    scenario.lfpMethod=this->ui->cmbLFPMethod->currentIndex();
    mapGenerator->setScenario(scenario);

}

void MainWindow::initMenu()
{
 mMenuBar= new QMenuBar(this);

 mFileMenu= mMenuBar->addMenu(tr("&File"));
 mFileMenu->addAction(newAct);
 mFileMenu->addAction(openAct);
 mFileMenu->addAction(saveAct);
 mFileMenu->addAction(saveResultAct);


 mViewMenu= mMenuBar->addMenu(tr("&View"));
 mViewMenu->addAction(viewDebugLogDialogAct);


}

void MainWindow::on_pushButton_clicked()
{
    mDebugLog->clear();
}

void MainWindow::on_bntResultFileName_clicked()
{
     QString fileName;
     fileName = QFileDialog::getSaveFileName(this,
     tr("Save Result File"), "Saved", tr("Map Structure File(*.msf)"));

     this->ui->lineFilenameSave->setText(fileName);

     //mapGenerator->getForestWidget()->saveToFile(fileName);
}

void MainWindow::nodeDrawMode(bool on)
{
    mDebugLog->log("toggled:");
    if (on==true)
    {
        mDebugLog->log("true");
    }else{
        mDebugLog->log("false");
    }
}

void MainWindow::on_btnLoadPreset_clicked()
{
    presetDialog->show();
}





void MainWindow::on_chkMinimumSpanningTreeProblem_clicked()
{
     if (ui->chkMinimumSpanningTreeProblem->isChecked())
    {
       graphForestView->getMinimumSpanningTree();
    }else
    {
        graphForestView->hideMinimumSpanningTree();
    }
}

void MainWindow::on_chkMinimumSpanningTreeSolution_clicked()
{
    if (ui->chkMinimumSpanningTreeSolution->isChecked())
    {
       graphMapView->getMinimumSpanningTree();
    }else
    {
         graphMapView->hideMinimumSpanningTree();
    }
}

void MainWindow::on_btnResetCanvas_clicked()
{
    mapGenerator->reset();
}
