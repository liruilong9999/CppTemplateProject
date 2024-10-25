#ifndef SubThread2_H
#define SubThread2_H

#include <QThread>

class SubThread2 : public QThread
{
    Q_OBJECT
public:
    SubThread2(QObject * parent = nullptr);
    ~SubThread2();
    void run() override;
};

#endif
