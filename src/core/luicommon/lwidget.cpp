#include "lwidget.h"
#include "ltitlebar.h"
LWidget::LWidget(QWidget * parent /*= nullptr*/)
    : QWidget(parent)
    , m_pTitleBar(new LTitleBar)
{
    // Qt::FramelessWindowHint 无边框
    // Qt::WindowStaysOnTopHint 窗口在最顶端，不会拖到任务栏下面
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    initWidget();

    connectInit();
}

LWidget::~LWidget()
{
    // 清理资源
    if (m_pTitleBar)
    {
        delete m_pTitleBar;
        m_pTitleBar = nullptr;
    }
    if (m_pPalletWidget)
    {
        delete m_pPalletWidget;
        m_pPalletWidget = nullptr;
    }
}

void LWidget::initWidget()
{
}

void LWidget::setWidgetState(WidgetState widgetState)
{
    m_currentWidgetState = widgetState;
}

void LWidget::connectInit()
{
    connect(m_pTitleBar, &LTitleBar::btnCloseClicked, this, &LWidget::onTitleBarBtnCloseClicked);
    connect(m_pTitleBar, &LTitleBar::btnMinClicked, this, &LWidget::onTitleBarBtnMinClicked);
    connect(m_pTitleBar, &LTitleBar::btnMaxOrNomalClicked, this, &LWidget::onTitleBarBtnNomalOrMaxClicked);
    connect(m_pTitleBar, &LTitleBar::titleBarDoubleClicked, this, &LWidget::onTitleBarDoubleClicked);
}

void LWidget::onTitleBarBtnCloseClicked()
{
    close();
}

void LWidget::onTitleBarBtnMinClicked()
{
    showMinimized();
}

void LWidget::onTitleBarBtnNomalOrMaxClicked()
{
    // 如果最大化，则变为正常，否则全部最大化
    if (m_currentWidgetState == WidgetState::MaxState)
    {
        m_currentWidgetState = WidgetState::NomalState;
        showNormal();
    }
    else
    {
        m_currentWidgetState = WidgetState::MaxState;
        showMaximized();
    }
}

void LWidget::onTitleBarDoubleClicked()
{
    // 如果最大化，则变为正常，否则全部最大化
    onTitleBarBtnNomalOrMaxClicked();
}
