#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QPoint>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include "camera.h"

class GLWidget:
        public QGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget( QWidget* pParent = 0 );
    void initializeGL( void );
    void resizeGL( int width, int height );
    void paintGL( void );

    void keyPressEvent( QKeyEvent* pEvent );
    void mousePressEvent( QMouseEvent* pEvent );
    void mouseReleaseEvent( QMouseEvent* pEvent );
    void mouseMoveEvent( QMouseEvent* pEvent );
    void wheelEvent( QWheelEvent* pEvent );

    void CubeVertices( GLfloat length );
    void CubeColors( void );
signals:
    void ToggleFullScreen( void );
private:
    Camera          m_Camera;
    QPoint          m_LastPos;
    qreal           m_AspectRatio;
    GLuint          m_VertexBuffer, m_ColorBuffer;
};

#endif // GLWIDGET_H
