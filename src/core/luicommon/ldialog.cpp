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
            // �Ƴ� diaLog �Ĳ��֣���ֹ diaLog ��ʧ����
            diaLog->setLayout(nullptr);
            // �����ֵĸ���������Ϊ this
            layout->setParent(this);
            // ����������Ϊ this �Ĳ���
            this->setLayout(layout);
            // ���ò��ֵı߾�
            layout->setContentsMargins(0, 0, 0, 0);
            // ���ò��ֵĴ�СԼ��
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
