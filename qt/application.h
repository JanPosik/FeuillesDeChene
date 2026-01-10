#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QProgressBar>
#include "core.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

public:
    Core::GameState State;

private:
    Ui::Application *ui;
    void LoadDatabase();
    void LoadRecordFile();
    void UpdateUI();
    void CheckAnswer();
    void ContinueAfterWrongAnswer();
    void ChangeDifficultyDependencies();
    Core::Record LoadRecord();
    void SaveRecord(Core::Record&, bool);
    void UpdateNewRecordBar();

private:
    QString RecordPath = "../../data/records.txt";
    QProgressBar* NewRecordBar;
};
#endif // APPLICATION_H
