#include "MainWindow.h"
#include "ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->m_mainWndGridLayout->addWidget(m_gl, 0, 0, 4, 4);

  connectUI();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete m_gl;
}

void MainWindow::connectUI()
{
  connect(ui->btn_resetCamera, SIGNAL(clicked()), m_gl, SLOT(resetCamera()));
  //connect(ui->m_hairPrecisionSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeHairPrecision(int)));
  //connect(ui->m_hairLengthSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeHairLength(int)));
  //connect(ui->m_hairDampingSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeHairDamping(int)));
  //connect(ui->m_timeStepSpinBox, SIGNAL(valueChanged(double)), m_gl, SLOT(changeTimeStep(double)));
  //connect(ui->m_startCheckBox, SIGNAL(stateChanged(int)), m_gl, SLOT(changeStimulationStatus(int)));
  //connect(ui->m_windDirX, SIGNAL(valueChanged(double)), m_gl, SLOT(changeWindDirX(double)));
  //connect(ui->m_windDirY, SIGNAL(valueChanged(double)), m_gl, SLOT(changeWindDirY(double)));
  //connect(ui->m_windDirZ, SIGNAL(valueChanged(double)), m_gl, SLOT(changeWindDirZ(double)));
  //connect(ui->m_applyWindDir, SIGNAL(clicked()), m_gl, SLOT(applyWindDirChanged()));
  //connect(ui->m_windForceSlider, SIGNAL(valueChanged(int)), m_gl, SLOT(changeWindForce(int)));
}

