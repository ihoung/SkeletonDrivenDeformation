#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QStandardItemModel>
#include <QAbstractButton>
#include <QItemSelection>
#include <QMainWindow>
#include "NGLScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  NGLScene *m_gl;
  std::unique_ptr<QStandardItemModel> m_hierarchyModel;

  void connectUI();
  void initHierarchy();

  void loadTransform(const ngl::Transformation);

private slots:
  void addBone();
  void removeBone();
  void setSkeletonMode(QAbstractButton* button, bool checked);
  void treeViewSelectionChanged(const QItemSelection&, const QItemSelection&);
};
#endif // MAINWINDOW_H
