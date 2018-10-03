#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QStringBuilder>

#include "categories.h"
#include "recipes.h"

#include <QDebug>
#define QD qDebug() << __FILE__ << __LINE__

#define DIR "Recepten"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO("author", "Véronique Wuyts")
    Q_CLASSINFO("Date", "2018-10-02")

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private slots:
    void openFile(void);
    void showCategories(void);
    void backToCategories(void);
    void showRecipes(void);
    void backToRecipes(void);
    void showRecipe(void);
    void setServings(int);

private:
    Ui::MainWindow *ui;
    const QString TITLE = "Mijn Kookboek";
    const QStringList PLURAL = {"personen", "taarten"};
    const QStringList SINGULAR = {"persoon", "taart"};

    QAction *m_fileOpenAct;
    QJsonDocument m_categoryDoc;
    QString m_dir;
    int m_servings;
    Categories m_categories;
    Recipes m_recipes;
    Recipe m_recipe;

    void showIngredients(void);
    void showSteps(void);
    void showNotes(void);
    void createActions(void);
};

#endif // MAINWINDOW_H
