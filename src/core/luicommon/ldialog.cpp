#include "ldialog.h"

#include <QLayout>

LDialog::LDialog(QWidget * parent)
{
    setParent(parent);
}

LDialog::~LDialog()
{
}

void LDialog::setContentDiaLog(QDialog * diaLog)
{
    if (diaLog)
    {
        QLayout * layout = diaLog->layout();
        if (layout)
        {
            // 移除 diaLog 的布局，防止 diaLog 丢失布局
            diaLog->setLayout(nullptr);
            // 将布局的父对象设置为 this
            layout->setParent(this);
            // 将布局设置为 this 的布局
            this->setLayout(layout);
            // 设置布局的边距
            layout->setContentsMargins(0, 0, 0, 0);
            // 设置布局的大小约束
            layout->setSizeConstraint(QLayout::SetFixedSize);

            layout->addWidget(diaLog);
        }
    }
}

QDialog * LDialog::takeContentDiaLog()
{
    if (layout() && layout()->count() > 0)
    {
        QLayoutItem * item = layout()->takeAt(0);
        if (item)
        {
            QDialog * diaLog = qobject_cast<QDialog *>(item->widget());
            if (diaLog)
            {
                item->widget()->setParent(nullptr);
                delete item;
                return diaLog;
            }
        }
    }
    return nullptr;
}

QDialog * LDialog::contentDiaLog() const
{
    if (layout() && layout()->count() > 0)
    {
        QLayoutItem * item = layout()->takeAt(0);
        if (item)
        {
            QDialog * diaLog = qobject_cast<QDialog *>(item->widget());
            if (diaLog)
            {
                return diaLog;
            }
        }
    }
    return nullptr;
}

void LDialog::accept()
{

}

void LDialog::reject()
{
}

void LDialog::exec()
{
}

void LDialog::open()
{
}

void LDialog::close()
{
}

void LDialog::done(int result)
{
}

void LDialog::closeEvent(QCloseEvent * event)
{
}
