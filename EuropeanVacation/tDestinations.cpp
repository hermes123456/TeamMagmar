#include "tDestinations.h"
#include "ui_tDestinations.h"
#include <QSqlQuery>
#include <QSql>

// Default Constructor
tDestinations::tDestinations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tDestinations)
{
    ui->setupUi(this);

    myDB = QSqlDatabase::database();

    defaultReset();
}

// Destructor
tDestinations::~tDestinations()
{
    delete ui;
}

void tDestinations::tDestinations::defaultReset()
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("SELECT * "
                    "FROM Distances "
                    "WHERE Start = '"+startCity+"'"
                    " ORDER BY 3");

    QSqlQuery qry;
    qry.prepare("SELECT * "
                "FROM Distances "
                "WHERE Start = '"+startCity+"'"
                "ORDER BY Kilometers ASC");
    qry.exec();
    qry.next();

    QString idValue = qry.value(1).toString();
    qDebug() << idValue;

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting location"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Destination"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Distance(km)"));

    ui->tDestinationOptionsTV->verticalHeader()->setVisible(false);
    ui->tDestinationOptionsTV->setModel(model);

    QAbstractItemModel* tableModel= ui->tDestinationOptionsTV->model();

    int w = ui->tDestinationOptionsTV->verticalHeader()->width(); // +4 seems to be needed
    for (int i = 0; i < tableModel->columnCount(); i++)
       w += ui->tDestinationOptionsTV->columnWidth(i); // seems to include gridline (on my machine)
    int h = ui->tDestinationOptionsTV->horizontalHeader()->height();
    for (int i = 0; i < tableModel->rowCount(); i++)
       h += ui->tDestinationOptionsTV->rowHeight(i);

    ui->tDestinationOptionsTV->setMinimumWidth(w);
    ui->tDestinationOptionsTV->setMaximumWidth(w);

    ui->tDestinationOptionsTV->setMinimumHeight(h);
    ui->tDestinationOptionsTV->setMaximumHeight(h);
}
