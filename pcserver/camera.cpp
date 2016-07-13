#include <QtOpenGL>

#include "Camera.h"
/*---------------------------------------------------------------------------*/
#ifdef _3DS_OPENGL_ARM_
#define glTranslater    glTranslatef
#define glMultMatrixr   glMultMatrixf
#define glRotater       glRotatef
#else
#define glTranslater    glTranslated
#define glMultMatrixr   glMultMatrixd
#define glRotater       glRotated
#endif
/*---------------------------------------------------------------------------*/
Camera::Camera( void )
{
    m_Pos = QVector3D( 0, 0, 0 );
    m_RotateY = 0.0;
    m_RotateH = 0.0;
    m_Len = QVector3D( 0, 0, 0 );
    m_TryPos = QVector3D( 0, 0, 0 );
    m_TryRotateY = 0.0;
    m_TryRotateH = 0.0;
    m_Try = false;
}
/*---------------------------------------------------------------------------*/
void Camera::SetPos( const QVector3D pos, bool _try )
{
    m_Try = _try;

    if ( m_Try ) m_TryPos = pos;
    else
    {
        m_Pos += pos;
        m_TryPos = QVector3D( 0, 0, 0 );
    }
}

void Camera::SetRotateY( qreal rotateY, bool _try )
{
    m_Try = _try;

    if ( m_Try ) m_TryRotateY = rotateY;
    else
    {
        m_RotateY += rotateY;
        m_TryRotateY = 0.0;
    }
}

void Camera::SetRotateH( qreal rotateH, bool _try )
{
    m_Try = _try;

    if ( m_Try ) m_TryRotateH = rotateH;
    else
    {
        m_RotateH += rotateH;
        m_TryRotateH = 0.0;
    }
}
/*---------------------------------------------------------------------------*/
void Camera::Apply( void )
{
    QVector3D ha = QVector3D::crossProduct( m_Pos - QVector3D( 0, m_Pos.y( ), 0 ),
                                            QVector3D( 0, 1, 0 ) );
    QVector3D focus = -m_Pos - m_TryPos - m_Len;
    glTranslater( focus.x( ), focus.y( ), focus.z( ) );
    glRotater( m_RotateH + m_TryRotateH, ha.x( ), ha.y( ), ha.z( ) );
    glRotater( m_RotateY + m_TryRotateY, 0, 1, 0 );
}
/*---------------------------------------------------------------------------*/
void Camera::ZoomIn( qreal step )
{
    QVector3D tangent = m_Pos - QVector3D( 0, m_Pos.y( ), 0 );
    m_Len -= tangent.normalized( ) * step;
}

