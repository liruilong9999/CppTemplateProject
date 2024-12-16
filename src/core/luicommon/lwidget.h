#ifndef LWIDGET_H
#define LWIDGET_H

#include <QWidget>
#include <QPointer>
#include "luicommon_global.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	窗口状态. </summary>
///
/// <remarks>	Liruilong, 2024/12/16. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

enum class WidgetState
{
    MinState = 0, // 最小化
    MaxState,     // 最大化
    NomalState,   // 正常大小
    OtherState    // 其它大小
};

class LTitleBar;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	实现一个自定义的QWidget. </summary>
///
/// <remarks>	Liruilong, 2024/12/16. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class LUICOMMON_EXPORT LWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LWidget(QWidget * parent = nullptr);
    virtual ~LWidget() override;

    void initWidget();

    void setWidgetState(WidgetState widgetState);
    void connectInit();

public slots:
    void onTitleBarBtnCloseClicked();
    void onTitleBarBtnMinClicked();
    void onTitleBarBtnNomalOrMaxClicked();
    void onTitleBarDoubleClicked();

private:
    WidgetState m_currentWidgetState{WidgetState::MaxState};

    /*
    widget结构
     _____________________________
    |                             |
    |          标题栏             |
    |          工具栏			  |
    |          正文               |
    |_____________________________|
    */
    LTitleBar *       m_pTitleBar{nullptr};     // 标题栏
    QWidget *         m_pPalletWidget{nullptr}; // 工具栏
    QPointer<QWidget> m_pCenterWidget{nullptr}; // 正文
};

#endif