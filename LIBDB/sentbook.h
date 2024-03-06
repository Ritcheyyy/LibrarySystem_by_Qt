#ifndef SENTBOOK_H
#define SENTBOOK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class sentbook;
}
QT_END_NAMESPACE

class sentbook : public QWidget
{
    Q_OBJECT

public:
    explicit sentbook(QWidget *parent = nullptr);
    ~sentbook();

private:
    Ui::sentbook *ui;
};

#endif // SENTBOOK_H
