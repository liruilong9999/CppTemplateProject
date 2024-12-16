#ifndef LTITLEBAR_H
#define LTITLEBAR_H

#include "luicommon_global.h"
#include <QWidget>

class QHBoxLayout;
class QToolButton;
class QLabel;
/*
按钮布局
    |软件图标  | 软件名称（靠左）| 软件名称（居中）  |最小化   |最大化/还原     |关闭       |
    |m_pBtnLogo|m_pTitleLabelLeft|m_pTitleLabelCenter|m_pBtnMin|m_pBtnMaxOrNomal|m_pBtnClose|

*/
enum class TitlePos
{
	LeftPos = 0,
	CenterPos
};

class LUICOMMON_EXPORT LTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit LTitleBar(QWidget * parent = nullptr);
    virtual ~LTitleBar() override;

    QToolButton * btnLogo();
    QToolButton * btnMin();
    QToolButton * btnMaxOrNomal();
    QToolButton * btnClose();
    QLabel *      labelLeft();
    QLabel *      labelCenter();
    QHBoxLayout * titleLayout();

    void setIcon(const QString & icon);
	void setCurrTitlePos(const TitlePos & pos = TitlePos::LeftPos);
    void setTitle(const QString & title);

signals:
    void btnMinClicked();
    void btnMaxOrNomalClicked();
    void btnCloseClicked();
    void titleBarDoubleClicked();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent * event) override;

private:
    QToolButton * m_pBtnLogo{nullptr};
    QToolButton * m_pBtnMin{nullptr};
    QToolButton * m_pBtnMaxOrNomal{nullptr};
    QToolButton * m_pBtnClose{nullptr};
    QLabel *      m_pTitleLabelLeft{nullptr};
    QLabel *      m_pTitleLabelCenter{nullptr};
    QHBoxLayout * m_pTitleLayout{nullptr};
};

#endif