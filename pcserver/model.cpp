#include "Model.h"

Model::Model(QString filename)
{
    fileName = filename;
    QString textruename;
    QVector3D temp3D;
    QVector2D temp2D;
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream fileText(&file);
            while (!fileText.atEnd())
            {
                QString fileLine = fileText.readLine();
                if(fileLine.startsWith("vn "))
                {
                    QStringList lineList = fileLine.split(" ");
                    temp3D.setX( lineList[1].toFloat() );
                    temp3D.setY( lineList[2].toFloat() );
                    temp3D.setZ( lineList[3].toFloat() );
                    VNormals.push_back(temp3D);
                }
                else if(fileLine.startsWith("vt "))
                {
                    QStringList lineList = fileLine.split(" ");
                    temp2D.setX( lineList[1].toFloat() );
                    temp2D.setY( lineList[2].toFloat() );
                    UVs.push_back(temp2D);
                }
                else if(fileLine.startsWith("v "))
                {
                    QStringList lineList = fileLine.split(" ");
                    temp3D.setX( lineList[1].toFloat() );
                    temp3D.setY( lineList[2].toFloat() );
                    temp3D.setZ( lineList[3].toFloat() );
                    Vertices.push_back(temp3D);
                }
                else if(fileLine.startsWith("f "))
                {
                    Face F;
                    QStringList lineList = fileLine.split(" ");

                    for(int i = 1; i <= 3; i++)
                    {
                        QStringList arg = lineList[i].split("/");
                        F.v[i-1] = Vertices[arg[0].toInt()-1];
                        F.t[i-1] = UVs[arg[1].toInt()-1];
                        F.vn[i-1] = VNormals[arg[2].toInt()-1];
                    }
                    Faces.push_back(F);
                }
                else if(fileLine.startsWith("mtllib "))
                {
                    QStringList lineList = fileLine.split(" ");
                    textruename = lineList[1];
                }
            }
        }
        file.close();
        QFileInfo fi(fileName);
        QString BaseName = fi.fileName();
        QString fn(fileName);
        fn.remove(fn.size() - BaseName.size(), BaseName.size());
        LoadMTL(fn, fn + textruename);
    }
}

void Model::render()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < Faces.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            glNormal3f(Faces[i].vn[j].x(), Faces[i].vn[j].y(), Faces[i].vn[j].z());
            glTexCoord2f(Faces[i].t[j].x(), Faces[i].t[j].y());
            glVertex3f(Faces[i].v[j].x(), Faces[i].v[j].y(), Faces[i].v[j].z());
        }
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

void Model::LoadMTL(QString fn, QString MTLname)
{
    if(!MTLname.isEmpty())
    {
        QFile file(MTLname);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream fileText(&file);
            while (!fileText.atEnd())
            {
                QString fileLine = fileText.readLine();
                if(fileLine.startsWith("map_Kd "))
                {
                    QStringList lineList = fileLine.split(" ");
                    textureName = fn + lineList[1];
                    LoadTexture();
                }
            }
        }
        file.close();
    }
}

void Model::LoadTexture()
{
    textureImg = QImage(textureName);

    textureImg = QGLWidget::convertToGLFormat( textureImg );
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.width(), textureImg.height(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, textureImg.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glBindTexture( GL_TEXTURE_2D, 0 );
}
