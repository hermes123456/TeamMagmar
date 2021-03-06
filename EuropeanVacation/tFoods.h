#ifndef TFOODS_H
#define TFOODS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>

namespace Ui {
class tFoods;
}

class tFoods : public QWidget
{
    Q_OBJECT

public:
    explicit tFoods(QWidget *parent = nullptr);
    ~tFoods();

    void defaultReset();
     //!< Loads default food table and city list


private slots:
    void on_tCityList_currentIndexChanged(const QString &arg1);
    //!< Traveler selects city to display onto table

private:
    Ui::tFoods *ui;

    QSqlDatabase myDB; // Database object for database connection
};

#endif //TFOODS_H
