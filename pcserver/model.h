#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QTextStream>
#include <QVector3D>
#include <QVector2D>
#include <QtOpenGL>

/* one texture only */

struct Face{
    QVector<QVector3D> v;
    QVector<QVector3D> vn;
    QVector<QVector2D> t;
    Face(){
        v.resize(3);
        vn.resize(3);
        t.resize(3);
    }
};

class Model
{
public:
    Model() {}
    Model(QString filename);
    void render();

    int faces() const { return Faces.size(); }
    int points() const { return Vertices.size(); }

private:
    QString fileName;
    QString textureName;
    QVector<QVector3D> Vertices; //v
    QVector<QVector3D> VNormals; //vn
    QVector<QVector2D> UVs;      //vt
    QVector<Face>      Faces;    //f
    GLuint texture;
    QImage textureImg;
    void LoadMTL(QString fn, QString MTLname);
    void LoadTexture();
};

#endif
