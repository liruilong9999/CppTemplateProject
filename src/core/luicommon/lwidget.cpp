#include "lwidget.h"
#include "ltitlebar.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QDebug>

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
    m_pTitleBar     = new LTitleBar(this); // 标题栏
    m_pPalletWidget = new QWidget(this);   // 工具栏
    m_pCenterWidget = new QWidget(this);   // 正文

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(m_pTitleBar);
    layout->addWidget(m_pPalletWidget);
    layout->addWidget(m_pCenterWidget);
    // 设置拉伸因子
    layout->setStretch(0, 0); // 标题栏不拉伸
    layout->setStretch(1, 1); // 工具栏拉伸因子为 1
    layout->setStretch(2, 2); // 正文拉伸因子为 2
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

void LWidget::setContentWidget(QWidget * pContentWidget)
{
    m_pCenterWidget->layout()->addWidget(pContentWidget);
}

QWidget * LWidget::contentWidget()
{
    if (m_pCenterWidget->layout()->count() == 0 )
    {
        return nullptr;
    }
    if (m_pCenterWidget->layout()->itemAt(0)->widget() == nullptr)
    {
        return nullptr;
    }
    return m_pCenterWidget->layout()->itemAt(0)->widget();
}

QWidget * LWidget::takeContentWidget()
{
    if (m_pCenterWidget->layout()->count() == 0)
    {
        return nullptr;
    }
    if (m_pCenterWidget->layout()->itemAt(0)->widget() == nullptr)
    {
        return nullptr;
    }
    QWidget * pContentWidget = m_pCenterWidget->layout()->takeAt(0)->widget();
    pContentWidget->setParent(nullptr);
    return pContentWidget;

}

LTitleBar * LWidget::titleBar()
{
    return m_pTitleBar;
}

QWidget * LWidget::palletWidget()
{
    return m_pPalletWidget;
}

void LWidget::loadStyleSheet(const QString & stylePath)
{
    QFile file(stylePath);
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = file.readAll();
        setStyleSheet(styleSheet);
    }
}

void LWidget::setWindowTitle(QString title)
{
    QWidget::setWindowTitle(title);
    m_pTitleBar->setTitle(title);
}

void LWidget::setWindowIcon(QIcon icon)
{
    QWidget::setWindowIcon(icon);
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
    // 如果是最大化，但是窗口的右上角不在（0，0处）（被move到其它位置），则回到当前屏幕的（0，0）位置再最大化
    if (x() != 0 && y() != 0)
    {
        move(0, 0);
        m_currentWidgetState = WidgetState::MaxState;
        showMaximized();
    }
    else
    {
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
}

void LWidget::onTitleBarDoubleClicked()
{
    // 如果最大化，则变为正常，否则全部最大化
    onTitleBarBtnNomalOrMaxClicked();
}

void LWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mousePos = event->pos();
        if (QRect(m_pTitleBar->x(), m_pTitleBar->y(), m_pTitleBar->width(), m_pTitleBar->height()).contains(m_mousePos))
        {
            m_isMousePressed = true;
            // qDebug() << "mouse pos:" << m_mousePos << "  titlebar:" << m_pTitleBar->width() << m_pTitleBar->height();
        }
    }
}

void LWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isMousePressed = false;
    }
}

void LWidget::mouseMoveEvent(QMouseEvent * event)
{
    // 获取窗口所在title栏坐标的比例，然后拖拽鼠标时窗口跟着一起拖拽，达到跟随效果
    if (m_isMousePressed)
    {
        int dx = event->x() - m_mousePos.x();
        int dy = event->y() - m_mousePos.y();
        move(x() + dx, y() + dy);
    }
}
