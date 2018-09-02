/************************************************************
* //correctly working code for adding data from csv to sqlite,
* main.c is correct code,ignore code in mainwindow.cpp
*
*
*****************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include <QGuiApplication>
#include <QQuickView>
#include "querymodel.h"

 QSqlQuery *query_questions ;

 /* Question table */
 int create_question_tabel(QString path ,QString tableName)
 {

     bool k = query_questions->exec("DROP TABLE IF EXISTS "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }
     QString quest = "create table IF NOT EXISTS "
     +tableName+
    " (qno INTEGER primary key,question TEXT ,description TEXT,imagepath TEXT,option1 TEXT,"
     "option2 TEXT,option3 TEXT,option4 TEXT,option5 TEXT)";
     qDebug()<<quest;
     k=query_questions->exec(quest);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

     k = query_questions->exec("SELECT * FROM "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

 }
 /*usr response table */
 int create_Usrresptable_tabel(QString path ,QString tableName)
 {

     int jj = 8 ;//length of response =8
     int len = tableName.length();
     QString respidx = tableName.mid(jj,len-jj);
     qDebug() <<"respidx" << respidx;
     bool k = query_questions->exec("DROP TABLE IF EXISTS "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }
     QString quest = "create table IF NOT EXISTS "
     +tableName+
    " (qno INTEGER primary key,response CHARACTER(1),test_qno INTEGER FORIEGN KEY REFERENCES test"+respidx+"(qno) ON DELETE CASCADE)";
     qDebug()<<quest;
     k=query_questions->exec(quest);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

     k = query_questions->exec("SELECT * FROM "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

 }

 /* answer table */
 int create_answer_tabel(QString path ,QString tableName)
 {

     int jj = 6 ;//length of answer = 6
     int len = tableName.length();
     QString answidx = tableName.mid(jj,len-jj);
     qDebug() <<"answidx" << answidx;

     bool k = query_questions->exec("DROP TABLE IF EXISTS "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }
     QString quest = "create table IF NOT EXISTS "
     +tableName+
    " (qno INTEGER primary key,answer CHARACTER(1),test_qno INTEGER FORIEGN KEY REFERENCES test"+answidx+"(qno) ON DELETE CASCADE)";
     qDebug()<<quest;
     k=query_questions->exec(quest);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

     k = query_questions->exec("SELECT * FROM "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

 }

 QString parse_csv_string(QString string) {

     //string = "'" + string ;
     int index = 0;
     while ((string.indexOf(',', index, Qt::CaseSensitive)) > 0) {
         int k = string.indexOf(',', index, Qt::CaseSensitive);
         //qDebug() << k;
         if(string[index] != '"') {
         string.insert(k,"'");
         string.insert(index,"'");
         index=k+3;
         }
         else {
             char c = '\'';
           string.replace(index,1,c);
           index++;
           index = (string.indexOf('"', index, Qt::CaseSensitive));
           string.replace(index,1,c);
           index=index+2;
         }
     }
    // qDebug() << string;
     return string;
 }

 int import_csv_to_db(QString path,QString csv_path,QString table_name) {

     QFile f(csv_path);
     int linCount = 0;
     if(f.open (QIODevice::ReadOnly)) {
         QTextStream stream (&f);
         QString temp;
         while(!stream.atEnd()){
             QString statement = "INSERT INTO "+table_name+" VALUES("+QString::number(linCount)+",";
             QStringList line = stream.readLine().split(';'); //here you define your separator
             for(int i=0; i<line.length(); ++i) {
                // statement.append(line.at(i));
                 temp.append(line.at(i));
                 //statement.append(",");
                 temp.append(",");
                 //qDebug() << line.length();
             }
          temp =  parse_csv_string(temp);
             //qDebug() <<"temp "<< temp;
             temp.chop(1); //remove trailing ,'
             statement.append(temp);
             temp.clear();
             statement.append(")"); //close value group
             if(linCount == 0) { linCount++; continue; }
             linCount ++;
             //qDebug() << statement;
             bool k = query_questions->exec(statement);
             if(k == false) {
                qDebug() << query_questions->lastError();
                f.close ();
                return -1;
             }
         }
         f.close ();
     }
     else {
         qDebug() << "csv file open failed "+csv_path;
         f.close ();
         return -1;
     }



 }

 int exec_pragma(QString path ,QString pragmaStat) {

      bool k = query_questions->exec(pragmaStat);
     if(k == false) {
         qDebug() <<"exec pragma" <<query_questions->lastError();
         return -1;
     }
     return 0;

 }

  int show_database(QString path,QString table_name) {

    bool k = query_questions->exec("SELECT* FROM "+table_name);
    if(k==false) {
        qDebug() << query_questions->lastError();
        return -1;
    }
     QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery(*query_questions);
     QTableView *view = new QTableView();
     view->setModel(model);
     qDebug() << query_questions->lastError();
     view->setWindowTitle(table_name);
     view->show();

 }


 int drop_table(QString path ,QString tableName) {

     bool k = query_questions->exec("DROP TABLE IF EXISTS "+tableName);
     if(k == false) {
         qDebug() << query_questions->lastError();
         return -1;
     }

     return 0;
 }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  qDebug()<<argc<<"\n"<<argv[0];
  //  MainWindow w;
   //w.setCentralWidget(view);
   //w.show();
//#define FILL_DATABASE
//correctly working code for adding data from csv to sqlite
    static QString database_path_ ="/home/divakar/qtprojects/cppsqlmodel/database/applicationdb2";
    int numOfTest = 2;
    int numOfQp = 4;

    QSqlDatabase  question_table_=QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase *question_table = &question_table_;
    question_table->setDatabaseName(database_path_);
    if (!(question_table->open()))
    {
        qDebug() << "Error: connection with database fail:question table";
        qDebug() << question_table->lastError();
        return -1;
    }
//#define FILL_DATABASE
#ifdef FILL_DATABASE
    QSqlQuery query_questions__(*question_table);
    query_questions = &query_questions__;

    int ret = exec_pragma(database_path_,"PRAGMA foreign_keys = ON");
    if(ret < 0) {
        qDebug() << "pragma failed";
    }

#define ADD_QUESTION_DATABASE
#ifdef ADD_QUESTION_DATABASE
    QString tableNameQuest = "test";
//    int numOfTest = 2;
//    int numOfQp = 4;
    //QString csvPathquest = "/home/divakar/qtprojects/cppsqlmodel/database/question/q";
    QString csvPathquest = ":/database/question/q";
    QString csvExtQuest = ".csv";
    for(int qpnum = 1;qpnum <= numOfQp;qpnum++) {
        for(int testnum = 1;testnum <= numOfTest;testnum++) {
            QString temp = QString::number(qpnum)+QString::number(testnum);
            QString csv_path = csvPathquest+temp+csvExtQuest;
            QString table_name = tableNameQuest+temp;
            int ret = create_question_tabel(database_path_,table_name);
            ret = import_csv_to_db(database_path_,csv_path,table_name);
            ret = show_database(database_path_,table_name);
        }
    }
#endif

#define ADD_USRRESPTABLE_DATABASE
#ifdef ADD_USRRESPTABLE_DATABASE
//    int numOfTest = 2;
//    int numOfQp = 4;
    QString tableNameResp = "response";
    QString csvPathResp =":/database/resp" ;//"/home/divakar/qtprojects/cppsqlmodel/database/resp";
    QString csvExtResp = ".csv";
    for(int qpnum = 1;qpnum <= numOfQp;qpnum++) {
        for(int testnum = 1;testnum <= numOfTest;testnum++) {
            QString temp = QString::number(qpnum)+QString::number(testnum);
            //for esponse table same csv file(resp11.csv) is added to all the tables.
            QString csv_path =csvPathResp+"11"+csvExtResp; //csvPathResp+temp+csvExtResp;
            QString table_name = tableNameResp+temp;
            int ret = create_Usrresptable_tabel(database_path_,table_name);
            ret = import_csv_to_db(database_path_,csv_path,table_name);
            ret = show_database(database_path_,table_name);
        }
    }
#endif


#define ADD_ANSWER_DATABASE
#ifdef ADD_ANSWER_DATABASE
//    int numOfTest = 2;
//    int numOfQp = 4;
    QString tableNameAns = "answer";
    QString csvPathAns =":/database/answercsv/answer"; //"/home/divakar/qtprojects/cppsqlmodel/database/answercsv/answer";
    QString csvExtAns = ".csv";
    for(int qpnum = 1;qpnum <= numOfQp;qpnum++) {
        for(int testnum = 1;testnum <= numOfTest;testnum++) {
            QString temp = QString::number(qpnum)+QString::number(testnum);
            QString csv_path = csvPathAns+temp+csvExtAns;
            QString table_name = tableNameAns+temp;
            int ret = create_answer_tabel(database_path_,table_name);
            ret = import_csv_to_db(database_path_,csv_path,table_name);
            ret = show_database(database_path_,table_name);
        }
    }
#endif

//#define DROP_TABLES
#ifdef DROP_TABLES
//    int numOfTest = 2;
//    int numOfQp = 4;
    QString tableNameDrop = "test";
#if 0
    for(int qpnum = 1;qpnum <= numOfQp;qpnum++) {
        for(int testnum = 1;testnum <= numOfTest;testnum++) {
            QString temp = QString::number(qpnum)+QString::number(testnum);
            QString table_name = tableNameDrop+temp;
            int ret = drop_table(database_path_,table_name);
        }
    }
#endif
   bool  zz =  query_questions->exec("DELETE FROM test11 WHERE rowid = 3");
   if (zz == false)
   {
       qDebug() << "Error: connection with database fail:question table";
       qDebug() << question_table->lastError();
       return -1;
   }
    zz = query_questions->exec("DELETE FROM test12 WHERE rowid = 4");
    if (zz == false)
    {
        qDebug() << "Error: connection with database fail:question table";
        qDebug() << question_table->lastError();
        return -1;
    }
    zz = query_questions->exec("DELETE FROM test21 WHERE rowid = 1");
    if (zz == false)
    {
        qDebug() << "Error: connection with database fail:question table";
        qDebug() << question_table->lastError();
        return -1;
    }
    zz = query_questions->exec("DELETE FROM test31 WHERE rowid = 1");
    if (zz == false)
    {
        qDebug() << "Error: connection with database fail:question table";
        qDebug() << question_table->lastError();
        return -1;
    }
    zz = query_questions->exec("DELETE FROM test41 WHERE rowid = 2");
    if (zz == false)
    {
        qDebug() << "Error: connection with database fail:question table";
        qDebug() << question_table->lastError();
        return -1;
    }

#endif


//#define SHOW_DB_AFTER_DROP
#ifdef SHOW_DB_AFTER_DROP
    QString tableNameAnswer = "answer";
    QString tableNameResponse = "response";

    for(int qpnum = 1;qpnum <= numOfQp;qpnum++) {
        for(int testnum = 1;testnum <= numOfTest;testnum++) {
            QString temp = QString::number(qpnum)+QString::number(testnum);
            QString table_name = tableNameAnswer+temp;
            QString table_name_2 = tableNameResponse+temp;
           int ret = show_database(database_path_,table_name);
           ret = show_database(database_path_,table_name_2);
        }
    }
#endif //SHOW_DB_AFTER_DROP


#endif //FILL_DATABASE


//#define TABLE_MODEL
#ifdef TABLE_MODEL
    // QSqlTableModel *model=new QSqlTableModel();

    QLSqlTableModel *model=new QLSqlTableModel(nullptr,question_table_);

    model->setTable("response11");
    model->setFilter("response11.rowid=10");
    model->setJoinMode(model->JoinMode::InnerJoin);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setRelation(2, QSqlRelation("test11", "qno",
    "qno,question,description,imagepath,option1,option2,option3,option4,option5"));
    model->select();
    model->generateRoleNames();
//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("QNO"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("RESPONSE"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUESTION"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));


    QTableView *view = new QTableView;
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    view->show();
#endif

    QLSqlTableModel dataModel(nullptr,*question_table);
    QLSqlTableModel2 dataModel2(nullptr,*question_table);

    dataModel.setsqlquery(11,6);
    dataModel2.setdbdata(5,"c",11);

//    SqlQueryModel dataModel;
//    dataModel.setQuery("select * from test11",*question_table);

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    context->setContextProperty("queryModel", &(dataModel));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
