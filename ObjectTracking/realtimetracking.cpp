#include "realtimetracking.h"
#include "ui_realtimetracking.h"
#include "scatterdatamodifier.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSize>
#include <QMessageBox>
#include <QtGui/QScreen>


static QtDataVisualization::Q3DScatter * graph;
static ScatterDataModifier *modifier;
static QWidget *container;

RealTimeTracking::RealTimeTracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealTimeTracking)
{
    graph = new QtDataVisualization::Q3DScatter;
    container = QWidget::createWindowContainer(graph);
    modifier = new ScatterDataModifier(graph);

    modifier->addData();
    ui->setupUi(this);


    ui->gridLayout->addWidget(container);
}

RealTimeTracking::~RealTimeTracking()
{
    delete ui;
}


/*
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph);

    //! window size - can ignore
    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 2));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);


    //! widget - can ignore
    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);


    //! data
    QVector<QVector3D> vec;
    vec.append(QVector3D(100,200,100));
    vec.append(QVector3D(200,100,100));
    vec.append(QVector3D(100,100,200));

    //! graph
    ScatterDataModifier *modifier = new ScatterDataModifier(graph);
    modifier->setData(vec);

    //! push button to change data - can ignore
    QPushButton *labelButton = new QPushButton(widget);
    labelButton->setText(QStringLiteral("Change Data"));
    vLayout->addWidget(labelButton, 0, Qt::AlignTop);
    QObject::connect(labelButton, &QPushButton::clicked, modifier, &ScatterDataModifier::addData);


    widget->show();
    return app.exec();
}

#include "scatterdatamodifier.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>

*/
