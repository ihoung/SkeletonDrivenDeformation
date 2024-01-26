#include "MainWindow.h"
#include "ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->m_mainWndGridLayout->addWidget(m_gl, 0, 0, 4, 4);

  initHierarchy();
  connectUI();
}

MainWindow::~MainWindow()
{
  delete m_gl;
  delete ui;
}

void MainWindow::connectUI()
{	
	connect(ui->btn_resetCamera, SIGNAL(clicked()), m_gl, SLOT(resetCamera()));
	connect(ui->btn_addBone, SIGNAL(clicked()), this, SLOT(addBone()));
	connect(ui->btn_deleteBone, SIGNAL(clicked()), this, SLOT(removeBone()));
	connect(ui->btnG_TMode, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(setSkeletonMode(QAbstractButton*, bool)));
	connect(ui->treeView_hierarchy->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
		this, SLOT(treeViewSelectionChanged(const QItemSelection&, const QItemSelection&)));
}

void MainWindow::initHierarchy()
{
	m_hierarchyModel = std::make_unique<QStandardItemModel>();
	ui->treeView_hierarchy->setModel(m_hierarchyModel.get());
}

void MainWindow::loadTransform(ngl::Transformation _t)
{
	ngl::Vec3 pos = _t.getPosition();
	ui->dsb_tX->setValue(pos.m_x);
	ui->dsb_tY->setValue(pos.m_y);
	ui->dsb_tZ->setValue(pos.m_z);

	ngl::Vec3 rot = _t.getRotation();
	ui->dsb_rX->setValue(rot.m_x);
	ui->dsb_rY->setValue(rot.m_y);
	ui->dsb_rZ->setValue(rot.m_z);

	ngl::Vec3 scale = _t.getScale();
	ui->dsb_sX->setValue(scale.m_x);
	ui->dsb_sY->setValue(scale.m_y);
	ui->dsb_sZ->setValue(scale.m_z);
}

void MainWindow::addBone()
{
	QModelIndex nextSelectedIndex;

	QModelIndexList indexes = ui->treeView_hierarchy->selectionModel()->selectedIndexes();
	if (indexes.size() > 0)
	{
		QModelIndex selectedIndex = indexes[0];
		QStandardItem* selItem = m_hierarchyModel->itemFromIndex(selectedIndex);
		int parentId = selItem->data().toInt();
		int newBoneId = m_gl->createBone(parentId);
		std::string boneName = m_gl->getBone(newBoneId)->getName();
		QStandardItem* item = new QStandardItem(QIcon("resources/bone.png"), QString(boneName.c_str()));
		QVariant data;
		data.setValue(newBoneId);
		item->setData(data);
		selItem->appendRow(item);

		ui->treeView_hierarchy->setExpanded(selectedIndex, true);
		nextSelectedIndex = m_hierarchyModel->indexFromItem(item);
	}
	else if (!m_gl->hasSkeletonRoot())
	{
		QStandardItem* rootItem = new QStandardItem(QIcon("resources/bone.png"), "root");
		QVariant data;
		data.setValue(m_gl->createBone(-1));
		rootItem->setData(data);
		m_hierarchyModel->appendRow(rootItem);

		nextSelectedIndex = m_hierarchyModel->indexFromItem(rootItem);
	}

	ui->treeView_hierarchy->selectionModel()->select(nextSelectedIndex, QItemSelectionModel::ClearAndSelect);
	ui->rb_initT->setChecked(true);
}

void MainWindow::removeBone()
{
	QModelIndexList indexes = ui->treeView_hierarchy->selectionModel()->selectedIndexes();
	if (indexes.size() > 0)
	{
		QModelIndex selectedIndex = indexes[0];
		QStandardItem* selItem = m_hierarchyModel->itemFromIndex(selectedIndex);
		int boneId = selItem->data().toInt();
		m_gl->removeBone(boneId);
		m_hierarchyModel->removeRow(selectedIndex.row(), selectedIndex.parent());
	}
}

void MainWindow::setSkeletonMode(QAbstractButton* button, bool checked)
{
	QModelIndexList indexes = ui->treeView_hierarchy->selectionModel()->selectedIndexes();
	int selBoneId = -1;
	if (indexes.size() > 0)
	{
		selBoneId = m_hierarchyModel->itemFromIndex(indexes[0])->data().toInt();
	}

	if (button == ui->rb_initT && checked)
	{
		m_gl->setDisplayMode(Skeleton::DisplayMode::Init);
		if (selBoneId != -1)
		{
			loadTransform(m_gl->getBone(selBoneId)->getInitTransform());
		}
	}
	else if (button == ui->rb_curT && checked)
	{
		m_gl->setDisplayMode(Skeleton::DisplayMode::Current);
		if (selBoneId != -1)
		{
			loadTransform(m_gl->getBone(selBoneId)->getCurTransform());
		}
	}

}

void MainWindow::treeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	if (deselected.size() > 0)
	{
		QModelIndex deselIndex = deselected.indexes()[0];
		QStandardItem* deselItem = m_hierarchyModel->itemFromIndex(deselIndex);
		int deselId = deselItem->data().toInt();
		Bone* deselBone = m_gl->getBone(deselId);
		if (deselBone)
		{
			deselBone->setSelection(false);
		}
	}

	if (selected.size() > 0)
	{
		QModelIndex selIndex = selected.indexes()[0];
		QStandardItem* selItem = m_hierarchyModel->itemFromIndex(selIndex);
		int selId = selItem->data().toInt();
		Bone* selBone = m_gl->getBone(selId);
		selBone->setSelection(true);
		if (ui->rb_initT->isChecked())
		{
			loadTransform(selBone->getInitTransform());
		}
		else if (ui->rb_curT->isChecked())
		{
			loadTransform(selBone->getCurTransform());
		}
	}

}

