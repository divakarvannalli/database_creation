#ifndef QUERYMODEL_H
#define QUERYMODEL_H

#include <assert.h>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QtSql>
#include<QDebug>
#include <QSqlQuery>

/*relationtable model for reading from db */
class QLSqlTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT

private:
    QHash<int, QByteArray> roles; //hash table <key,value>

public:
    QLSqlTableModel(QObject *parent=nullptr, QSqlDatabase db=QSqlDatabase() );
    ~QLSqlTableModel();

public:
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    void generateRoleNames();
    QHash<int, QByteArray> roleNames() const {return roles; }
    Q_INVOKABLE void setsqlquery(int tableNo,int rowNo);
   // Q_INVOKABLE bool setdbdata(int row,QByteArray data,int tableNo);
//#ifdef HAVE_QT5
//    virtual QHash<int, QByteArray> roleNames() const{return roles;}
//#endif
};

/*relationTable for editing database*/
class QLSqlTableModel2 : public QSqlRelationalTableModel
{
    Q_OBJECT

private:
    //QHash<int, QByteArray> roles; //hash table <key,value>

public:
    QLSqlTableModel2(QObject *parent=nullptr, QSqlDatabase db=QSqlDatabase() );
    ~QLSqlTableModel2();

public:
//    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
//    void generateRoleNames();
//    QHash<int, QByteArray> roleNames() const {return roles; }
//    Q_INVOKABLE void setsqlquery(int tableNo,int rowNo);
    Q_INVOKABLE bool setdbdata(int row,QByteArray data,int tableNo);
//#ifdef HAVE_QT5
//    virtual QHash<int, QByteArray> roleNames() const{return roles;}
//#endif
};

/*----------------------------------------------------------------------------------------*/
/*sqlquery model */
class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    //QString query_ = "SELECT* FROM description_table where id" ;
    explicit SqlQueryModel(QObject *parent = 0);
    Q_INVOKABLE
    void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE
    void setQuery(const QSqlQuery &query);
    Q_INVOKABLE
    void execquery(int k){


    }
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}
    quintptr aid;
    QModelIndex modelindex = index(1,1);
private:
    void generateRoleNames();
    QHash<int, QByteArray> m_roleNames;
};


#endif // QUERYMODEL_H
