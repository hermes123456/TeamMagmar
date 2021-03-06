#include "tDestinations.h"
#include "ui_tDestinations.h"
#include <QSqlQuery>
#include <QSql>

/****************************************************************************
 * METHOD - tConfirmCustom
 * --------------------------------------------------------------------------
 * This method is the constructor.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      Database must exist and be open.
 *
 * POST-CONDITIONS
 *      ==> Returns nothing.
 ***************************************************************************/
tDestinations::tDestinations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tDestinations)
{
    ui->setupUi(this);

    myDB = QSqlDatabase::database();

    defaultReset();
}

/****************************************************************************
 * METHOD - tConfirmCustom
 * --------------------------------------------------------------------------
 * This method is the destructor.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      Database must exist and be open.
 *
 * POST-CONDITIONS
 *      ==> Returns nothing.
 ***************************************************************************/
tDestinations::~tDestinations()
{
    delete ui;
}

/****************************************************************************
 * METHOD - defaltReset
 * --------------------------------------------------------------------------
 * This method accesses the data base and queries it to get all entries
 * where Paris is in the first collumn and puts them into a QTableView
 * widget. It also dynamicly sets the size of the table to fit the data.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      No parameters are required.
 *
 * POST-CONDITIONS
 *      ==> Returns nothing.
 *      ==> Populates the destination table view with all cities from
 *          paris and the distances between them
 ***************************************************************************/
void tDestinations::tDestinations::defaultReset()
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("SELECT * "
                    "FROM Distances "
                    "WHERE Start = '"+startCity+"'"
                    " ORDER BY 3");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting location"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Destination"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Distance(km)"));

    ui->tDestinationOptionsTV->verticalHeader()->setVisible(false);
    ui->tDestinationOptionsTV->setModel(model);

    QAbstractItemModel* tableModel= ui->tDestinationOptionsTV->model();

    int w = ui->tDestinationOptionsTV->verticalHeader()->width()+4;//change +4 if its too big or small
    for (int i = 0; i < tableModel->columnCount(); i++)
       w += ui->tDestinationOptionsTV->columnWidth(i); // seems to include gridline
    int h = ui->tDestinationOptionsTV->horizontalHeader()->height()+4;//change +4 if its too big or small
    for (int i = 0; i < tableModel->rowCount(); i++)
       h += ui->tDestinationOptionsTV->rowHeight(i);

    ui->tDestinationOptionsTV->setMinimumWidth(w);
    ui->tDestinationOptionsTV->setMaximumWidth(w);

    ui->tDestinationOptionsTV->setMinimumHeight(h);
    ui->tDestinationOptionsTV->setMaximumHeight(h);
}
