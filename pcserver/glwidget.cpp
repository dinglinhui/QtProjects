#include <cmath>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QKeySequence>
#include "GLWidget.h"
/*---------------------------------------------------------------------------*/
void MyPerspective( GLdouble fov, GLdouble aspectRatio, GLdouble zNear, GLdouble zFar )
{
    using namespace std;
    // 使用OpenGL函数，但是需要添加math.h头文件
    GLdouble rFov = fov * 3.14159265 / 180.0;
    GLdouble up = -zNear * tan( rFov / 2.0 );
    GLdouble down = -up;
    GLdouble left = up * aspectRatio;
    GLdouble right = -left;
    glFrustum( left, right, up, down, zNear, zFar );
}
/*---------------------------------------------------------------------------*/
GLWidget::GLWidget( QWidget* pParent ):
    QGLWidget( pParent )
{
    // 设置窗口
    resize( 640, 360 );                                     // 初始大小为640×360（小宽屏）
    m_AspectRatio = qreal( width( ) ) / qreal( height( ) ); // 初始的宽高比
}

void GLWidget::initializeGL( void )
{
    initializeOpenGLFunctions( );

    // 打开开关
    qglClearColor( QColor( 0, 0, 0, 255 ) );
    qglColor( QColor( 255, 0, 0 ) );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    // 创建顶点缓存并且设置顶点
    glGenBuffers( 1, &m_VertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
    CubeVertices( 20.0f );

    // 创建索引缓存以及设置索引
    glGenBuffers( 1, &m_ColorBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_ColorBuffer );
    CubeColors( );

    glEnable( GL_DEPTH_TEST );
    glFrontFace( GL_CW );
    glEnable( GL_CULL_FACE );
    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glShadeModel( GL_SMOOTH );

    // 设置摄像机
    m_Camera.SetPos( QVector3D( 0.0, 0.0, 50.0 ) );// 设置摄像机坐标
}
/*---------------------------------------------------------------------------*/
void GLWidget::resizeGL( int width, int height )
{
    // 改变大小时程序如何应对？
    GLdouble aspectRatio = GLdouble( width ) / GLdouble( height );

    // 设置视口
    if ( aspectRatio < m_AspectRatio )
    {
        GLint smallHeight = GLint( GLdouble( width ) / m_AspectRatio );
        GLint heightBlank = ( GLint( height ) - smallHeight ) / 2;
        glViewport( 0, heightBlank, GLint( width ), smallHeight );
    }
    else
    {
        GLint smallWidth = GLint( GLdouble( height ) * m_AspectRatio );
        GLint widthBlank = ( GLint( width ) - smallWidth ) / 2;
        glViewport( widthBlank, 0, smallWidth, GLint( height ) );
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    // 设置裁剪区域
    MyPerspective( 45.0, m_AspectRatio, 0.5, 1000.0 );

    // 为模型视图载入标准矩阵
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}
/*---------------------------------------------------------------------------*/
void GLWidget::CubeVertices( GLfloat length )
{
    // 设置立方体的顶点
    GLfloat semiLength = length / 2.0f;
    GLfloat cubeVertices[] =
    {
        -semiLength, -semiLength, semiLength,   // 0
        semiLength, -semiLength, semiLength,    // 1
        semiLength, -semiLength, -semiLength,   // 2
        -semiLength, -semiLength, -semiLength,  // 3
        -semiLength, semiLength, semiLength,    // 4
        semiLength, semiLength, semiLength,     // 5
        semiLength, semiLength, -semiLength,    // 6
        -semiLength, semiLength, -semiLength,   // 7
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof( cubeVertices ),
                  cubeVertices, GL_STATIC_DRAW );
    glVertexPointer( 3, GL_FLOAT, 0, 0 );
}
/*---------------------------------------------------------------------------*/
void GLWidget::CubeColors( void )
{
    GLubyte cubeColors[] =
    {
        255, 0, 0, 255,
        255, 255, 0, 255,
        0, 255, 0, 255,
        0, 0, 0, 255,
        255, 0, 255, 255,
        255, 255, 255, 255,
        0, 255, 255, 255,
        0, 0, 255, 255,
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof( cubeColors ),
                  cubeColors, GL_STATIC_DRAW );
    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, 0 );
}
/*---------------------------------------------------------------------------*/
void GLWidget::paintGL( void )
{
    GLubyte cubeIndices[] =
    {
        0, 1, 2, 0, 2, 3,// 下面
        7, 6, 4, 6, 5, 4,// 上面
        7, 4, 3, 4, 0, 3,// 左面
        5, 6, 1, 6, 2, 1,// 右面
        4, 5, 0, 5, 1, 0,// 前面
        3, 2, 6, 3, 6, 7,// 背面
    };

    glClear( GL_COLOR_BUFFER_BIT |
             GL_DEPTH_BUFFER_BIT );

    glPushMatrix( );
    m_Camera.Apply( );
    glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_ColorBuffer );
    glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeIndices );
    glPopMatrix( );
}
/*---------------------------------------------------------------------------*/
void GLWidget::keyPressEvent( QKeyEvent* pEvent )
{
    if ( pEvent->matches( QKeySequence::FullScreen ) )
    {
        emit ToggleFullScreen( );
    }
}
/*---------------------------------------------------------------------------*/
void GLWidget::mousePressEvent( QMouseEvent* pEvent )
{
    m_LastPos = pEvent->pos( );
    switch ( pEvent->button( ) )
    {
    case Qt::LeftButton:
    case Qt::RightButton:

        break;
    case Qt::MiddleButton:
    default: break;
    }
}
/*---------------------------------------------------------------------------*/
void GLWidget::mouseMoveEvent( QMouseEvent* pEvent )
{
    QVector2D delta( pEvent->pos( ) - m_LastPos );
    if ( pEvent->buttons( ) & Qt::LeftButton ||
         pEvent->buttons( ) & Qt::RightButton )
    {
        m_Camera.SetRotateH( -delta.y( ), true );
        m_Camera.SetRotateY( delta.x( ), true );
    }
    else if ( pEvent->buttons( ) & Qt::MiddleButton )
    {
        m_Camera.SetPos( QVector3D( -delta.x( ) / 5, delta.y( ) / 5, 0 ), true );
    }
    repaint( );
}
/*---------------------------------------------------------------------------*/
void GLWidget::mouseReleaseEvent( QMouseEvent* pEvent )
{
    QVector2D delta( pEvent->pos( ) - m_LastPos );
    switch ( pEvent->button( ) )
    {
    case Qt::LeftButton:
    case Qt::RightButton:
        m_Camera.SetRotateH( -delta.y( ) );
        m_Camera.SetRotateY( delta.x( ) );
        break;
    case Qt::MiddleButton:
        m_Camera.SetPos( QVector3D( -delta.x( ) / 5, delta.y( ) / 5, 0 ) );
        break;
    default: break;
    }
    repaint( );
}
/*---------------------------------------------------------------------------*/
void GLWidget::wheelEvent( QWheelEvent* pEvent )
{
    m_Camera.ZoomIn( pEvent->delta( ) / 6 );
    repaint( );
}
