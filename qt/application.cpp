#include "application.h"
#include "ui_application.h"
#include <QFileDialog>

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);
    ui->wrong_answer_widget->hide();
    ui->b_check_answer->setEnabled(false);
    ui->b_next_word_after_wrong->setEnabled(false);

    connect(ui->menu_load_database, &QAction::triggered, this, &Application::LoadDatabase);
    connect(ui->menu_load_record, &QAction::triggered, this, &Application::LoadRecordFile);
    connect(ui->b_check_answer, &QPushButton::clicked, this, &Application::CheckAnswer);
    connect(ui->b_next_word_after_wrong, &QPushButton::clicked, this, &Application::ContinueAfterWrongAnswer);
    // difficulty changes
    connect(ui->menu_difficulty_any, &QAction::triggered, this, [this](){this->State.Difficulty = DIFFICULTY::ANY; ui->difficulty->setText("Any"); ChangeDifficultyDependencies();});
    connect(ui->menu_difficulty_easy, &QAction::triggered, this, [this](){this->State.Difficulty = DIFFICULTY::EASY; ui->difficulty->setText("Easy"); ChangeDifficultyDependencies();});
    connect(ui->menu_difficulty_medium, &QAction::triggered, this, [this](){this->State.Difficulty = DIFFICULTY::MEDIUM; ui->difficulty->setText("Medium"); ChangeDifficultyDependencies();});
    connect(ui->menu_difficulty_hard, &QAction::triggered, this, [this](){this->State.Difficulty = DIFFICULTY::HARD; ui->difficulty->setText("Hard"); ChangeDifficultyDependencies();});

    // load record
    auto record = LoadRecord();
    Core::ApplyRecord(this->State, record);

    // create progress bar and set it at corner of menu bar
    QWidget* corner = new QWidget(ui->menubar);
    QHBoxLayout* layout = new QHBoxLayout(corner);
    layout->setContentsMargins(0, 0, 0, 0);

    this->NewRecordBar = new QProgressBar(corner);
    this->NewRecordBar->setMinimum(0);
    this->NewRecordBar->setMaximum(100);
    this->NewRecordBar->setFormat("%p%");
    this->NewRecordBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->NewRecordBar->setMinimumWidth(110);
    this->NewRecordBar->setValue(0);
    this->NewRecordBar->setToolTip("Shows percentage to beat new record");

    layout->addWidget(this->NewRecordBar);
    corner->setLayout(layout);
    ui->menubar->setCornerWidget(corner, Qt::TopRightCorner);


    UpdateUI();
}

Application::~Application()
{
    auto record = Core::MakeRecord(this->State);
    SaveRecord(record, (this->State.Record > this->State.LastRecord));

    delete ui;
}

void Application::LoadDatabase()
{
    QString databasePath = QFileDialog::getOpenFileName(this, tr("Select database"), QDir::homePath(), tr("All files (*)"));
    Core::LoadDatabase(this->State, databasePath.toStdString());
    Core::NextWord(this->State);

    // update ui if database loaded
    if (this->State.WordsLoaded)
    {
        ui->translate_from_full_text->setText("Word to translate (" + QString::fromStdString(this->State.LangFrom) + "):");
        ui->translate_to_full_text->setText("Translate (" + QString::fromStdString(this->State.LangTo) + "):");
        ui->b_check_answer->setEnabled(true);
        UpdateUI();
    }
}

void Application::LoadRecordFile()
{
    this->RecordPath = QFileDialog::getOpenFileName(this, tr("Select records file"), QDir::homePath(), tr("All files (*)"));
    auto record = LoadRecord();
    Core::ApplyRecord(this->State, record);
    UpdateUI();
}

void Application::UpdateUI()
{
    ui->score->setText(QString::number(this->State.Score));
    ui->mode->setText("Classic");
    ui->record->setText(QString::number(this->State.Record));
    ui->current_hint->setText(QString::fromStdString(this->State.CurrentHint));
    ui->right_answer->setText(QString::fromStdString(this->State.CurrentTarget));
}

void Application::CheckAnswer()
{
    bool right = Core::CheckAnswer(this->State, ui->input_translation->text().toStdString());

    if (right)
    {
        Core::NextWord(this->State);
        ui->input_translation->setText("");
        UpdateUI();
    }
    else
    {
        ui->wrong_answer_widget->show();
        ui->b_check_answer->setEnabled(false);
        ui->b_next_word_after_wrong->setEnabled(true);
    }
    UpdateNewRecordBar();
}

void Application::ContinueAfterWrongAnswer()
{
    Core::NextWord(this->State);
    UpdateUI();
    ui->b_check_answer->setEnabled(true);
    ui->b_next_word_after_wrong->setEnabled(false);
    ui->wrong_answer_widget->hide();
    ui->input_translation->setText("");
}

void Application::ChangeDifficultyDependencies()
{
    Core::NextWord(this->State);
    UpdateUI();
    ui->b_check_answer->setEnabled(this->State.WordsLoaded);
    ui->b_next_word_after_wrong->setEnabled(false);
    ui->wrong_answer_widget->hide();
}

Core::Record Application::LoadRecord()
{
    QFile record_file(this->RecordPath);

    if (!record_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {0};

    QTextStream in(&record_file);
    QString line = in.readLine();

    bool success;
    int read_record = line.toInt(&success);

    if (!success)
        read_record = 0;

    return {read_record};
}

void Application::SaveRecord(Core::Record& record, bool save)
{
    QFile record_file(this->RecordPath);

    if (!record_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&record_file);
    out << record.Default;
    record_file.flush();
    record_file.close();
}

void Application::UpdateNewRecordBar()
{
    float percentage = (this->State.Record > 0) ? ((float)this->State.Score / (float)this->State.Record * 100) : 0;
    this->NewRecordBar->setValue(percentage);
}
