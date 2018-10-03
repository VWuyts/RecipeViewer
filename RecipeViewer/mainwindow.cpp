#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_categories = Categories();
    m_recipes = Recipes();
    m_recipe = Recipe();

    // Setup window
    setWindowTitle(TITLE);
    createActions();

    // Create fonts
    QFont font;
    font.setPointSize(9);
    QFont boldFont;
    boldFont.setBold(true);

    // Setup cookbook page
    ui->stackedWidget->setCurrentIndex(0);
    ui->pbToCategories->setEnabled(false);
    ui->gbCookbook->setFont(font);
    ui->lCatError->setFont(boldFont);

    // Setup category page
    ui->gbCategories->setFont(font);
    ui->lRecipeError->setFont(boldFont);

    // Setup recipes page
    ui->gbRecipes->setFont(font);

    // Setup recipe page
    ui->spServings->setMinimum(1);
    ui->spServings->setMaximum(50);
    ui->teSteps->setReadOnly(true);
    ui->teNotes->setReadOnly(true);
    ui->gbRecipe->setFont(font);
    ui->gbRecipe->setFont(boldFont);
    QFont wFont = ui->wRecipe->font();
    wFont.setBold(false);
    ui->wRecipe->setFont(wFont);



    // Connections
    connect(ui->pbOpenFile, SIGNAL(clicked(bool)), this, SLOT(openFile()));
    connect(ui->pbToCategories, SIGNAL(clicked(bool)), this, SLOT(showCategories()));
    connect(ui->pbToRecipes, SIGNAL(clicked(bool)), this, SLOT(showRecipes()));
    connect(ui->lwCategories, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showRecipes()));
    connect(ui->pbToRecipe, SIGNAL(clicked(bool)), this, SLOT(showRecipe()));
    connect(ui->lwRecipes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showRecipe()));
    connect(ui->pbBackToCat, SIGNAL(clicked(bool)), this, SLOT(backToCategories()));
    connect(ui->pbBacktoRec, SIGNAL(clicked(bool)), this, SLOT(backToRecipes()));
    connect(ui->pbReady, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->spServings, SIGNAL(valueChanged(int)), this, SLOT(setServings(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    QD << "in fileOpen()";

    QString filename = QFileDialog::getOpenFileName(this, "Select file", QDir::homePath(), "JSON files (*.json)");
    if (filename.isEmpty())
    {
        ui->leFile->setText("[Selecteer het Kookboek.json bestand]");
        ui->lCatError->setText("Je moet het Kookboek.json bestand selecteren alvorens je kan verdergaan.");
        ui->pbToCategories->setEnabled(false);
    }
    else
    {
        QFile f(filename);
        if(!f.open(QFile::ReadOnly))
        {
            qFatal("File could not be opened for reading");
        }
        QByteArray categoryData = f.readAll();
        m_dir = QFileInfo(f).absolutePath();
        f.close();
        m_categoryDoc = QJsonDocument::fromJson(categoryData);

        ui->lCatError->setText("");
        ui->leFile->setText(filename);
        ui->pbToCategories->setEnabled(true);
    }
}

void MainWindow::showCategories()
{
    QD << "in showCategories()";

    QJsonObject json = m_categoryDoc.object();
    if (!m_categories.read(json))
    {
        ui->lCatError->setText("Het geselecteerde json bestand heeft niet het juiste formaat.");
        ui->pbToCategories->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        foreach (const Category *category, m_categories.categoryList())
        {
            ui->lwCategories->addItem(category->name());
        }
        ui->lwCategories->setCurrentRow(0);
        m_fileOpenAct->setDisabled(true);
        ui->pbToCategories->setDisabled(true);
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::backToCategories()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showRecipes(void)
{
    QD << "in showRecipes()";

    int index = ui->lwCategories->currentRow();

    // Read file
    QString filePath = m_dir % QDir::separator() % DIR % QDir::separator() % m_categories.categoryList()[index]->file();
    QFile f(filePath);
    if (!f.open(QFile::ReadOnly))
    {
        qFatal("File could not be opened for reading");
    }
    QByteArray recipeData = f.readAll();
    f.close();
    QJsonDocument recipeDoc = QJsonDocument::fromJson(recipeData);
    QJsonObject json = recipeDoc.object();
    if (!m_recipes.read(json))
    {
        ui->lRecipeError->setText("Het geselecteerde json bestand heeft niet het juiste formaat.");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->lwRecipes->clear();
        foreach (const Recipe *recipe, m_recipes.recipeList())
        {
            ui->lwRecipes->addItem(recipe->name());
        }
        ui->lwRecipes->setCurrentRow(0);
        ui->lRecipeError->setText("");
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::backToRecipes()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showRecipe()
{
    QD << "in showRecipe()";

    int index = ui->lwRecipes->currentRow();
    m_recipe = *m_recipes.recipeList()[index];
    ui->gbRecipe->setTitle(m_recipe.name());

    setServings(m_recipe.servings().amount());
    showDifficulty();
    showSteps();
    showNotes();

    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::setServings(int servings)
{
    QD << "in setServings()" << servings;

    m_servings = servings;
    ui->spServings->setValue(m_servings);
    QString unit = m_recipe.servings().unit();
    if (m_servings == 1)
    {
        int index = PLURAL.indexOf(unit);
        if (index >= 0) unit = SINGULAR.at(index);
    }
    ui->lServings->setText(unit);
    showIngredients();
}

void MainWindow::showDifficulty()
{
    QD << "in showDifficulty()";

    //TODO
}

void MainWindow::showIngredients()
{
    QD << "in showIngredients()";

    ui->lwIngredients->clear();

    foreach (const Ingredients *ingredients, m_recipe.ingredients())
    {
        if (!ingredients->part().isEmpty())
        {
            ui->lwIngredients->addItem(ingredients->part());
        }
        foreach (const Ingredient *ingredient, ingredients->ingredientList())
        {
            double amount = ingredient->amount();
            amount = (amount / m_recipe.servings().amount()) * m_servings;
            QString ingrStr = " -"
                    % (amount > 0 ? " " + QString::number(amount) : "")
                    % (ingredient->unit().isEmpty() ? "" : " ") % ingredient->unit()
                    % " " % ingredient->name()
                    % (ingredient->note().isEmpty() ? "" : ", ") % ingredient->note();
            ui->lwIngredients->addItem(ingrStr);
        }
    }
}

void MainWindow::showSteps()
{
    QD << "in showSteps()";

    ui->teSteps->clear();

    for (int i = 0; i < m_recipe.steps().length(); i++)
    {
        ui->teSteps->append(QString::number(i + 1) % ". " % m_recipe.steps()[i]);
    }
}

void MainWindow::showNotes()
{
    QD << "in showNotes()";

    ui->teNotes->clear();

    if (m_recipe.notes().isEmpty())
    {
        ui->lNotes->setHidden(true);
        ui->teNotes->setHidden(true);
    }
    else
    {
        ui->lNotes->setHidden(false);
        ui->teNotes->setHidden(false);
        foreach (const QString &note, m_recipe.notes())
        {
            ui->teNotes->append("- " % note);
        }
    }
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu("File");

    // Open file
    m_fileOpenAct = new QAction("Open", this);
    m_fileOpenAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(m_fileOpenAct, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    fileMenu->addAction(m_fileOpenAct);

    // Exit
    fileMenu->addSeparator();
    QAction *exitAct = new QAction("Exit", this);
    exitAct->setShortcut(QKeySequence("Ctrl+W"));
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(close()));
    fileMenu->addAction(exitAct);
}
