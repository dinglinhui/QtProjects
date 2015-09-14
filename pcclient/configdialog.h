#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QDialogButtonBox>

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(const QIcon &icon, const QString &fileName);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QDialogButtonBox *buttonBox;
};

#endif
