#include "mainwindow.h"  // Incluye el archivo de encabezado de la clase MainWindow
#include "ui_mainwindow.h"  // Incluye el archivo de encabezado generado por Qt Designer
#include <QGuiApplication>  // Incluye la clase QGuiApplication para manejar la aplicación
#include <QColorDialog> // ingreso del color, por parte del usuario para el pincel
#include <QScreen>  // Incluye la clase QScreen para obtener información sobre la pantalla
#include <QMouseEvent>  // Incluye la clase QMouseEvent para manejar eventos del mouse
#include <QPaintEvent>  // Incluye la clase QPaintEvent para manejar eventos de pintado
#include <QPainter>  // Incluye la clase QPainter para dibujar en la pantalla
#include <QImage>  // Incluye la clase QImage para manejar imágenes
#include <QInputDialog> // Incluir la cabecera necesaria para captuarar detos de ventanas
#include <QMessageBox>
#include <QFileDialog>
#include <QImageWriter>
#include <QFileDialog>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>



//#include <QDebug>
// qDebug()<< xx; #include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Constructor de la clase MainWindow, heredando de QMainWindow
    , ui(new Ui::DrawFul)  // Inicializa el objeto de la interfaz de usuario
{
    ui->setupUi(this);  // Configura la interfaz de usuario utilizando el diseño generado por Qt Designer
    // Crea una nueva imagen con el tamaño de la pantalla disponible y el formato ARGB32
    mImage = new QImage(QGuiApplication::primaryScreen()->availableSize(), QImage::Format_ARGB32);

    // Crea un nuevo objeto QPainter asociado con la imagen mImage
    mPainter = new QPainter(mImage);

    // Activa el antialiasing para líneas suaves
    mPainter->setRenderHint(QPainter::Antialiasing);

    // Inicializa la variable mAccion como 0 (pincel)
    mAccion = 0;

    // Inicializa el color del pincel
    mColor = QColor(Qt::black);

    mImage->fill(Qt::white);
    // Inicializa el tamaño del pincel
    mTamano_Pincel = 5;



}

MainWindow::~MainWindow()  // Destructor de la clase MainWindow
{
    delete ui;  // Libera la memoria del objeto de la interfaz de usuario
    delete mPainter;  // Libera la memoria del objeto QPainter
    delete mImage;  // Libera la memoria de la imagen
}

void MainWindow::paintEvent(QPaintEvent *e)  // Método para manejar eventos de pintado
{
    QPainter painter(this);  // Crea un objeto QPainter para pintar en la ventana principal
    //painter.fillRect(mImage->rect(), Qt::white);
    painter.drawImage(120, 0, *mImage);  // Dibuja la imagen mImage en la ventana principal en la posición (49, 0)
    e->accept();  // Acepta el evento de pintado
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if (e->buttons() & Qt::LeftButton) {
        if (mAccion == 0 ) {
            // Acción 0: Pintar con picel
            QPen pen(mColor, mTamano_Pincel, Qt::SolidLine, Qt::RoundCap);
            mPainter->setPen(pen);
            mTermina_Mouse = e->pos();
            mTermina_Mouse.setX(mTermina_Mouse.x() - 120);
            mPainter->drawLine(mEmpieza_Mouse, mTermina_Mouse);
            mEmpieza_Mouse = e->pos();
            mEmpieza_Mouse.setX(mEmpieza_Mouse.x() - 120);
            mCambio = true;
            update();  // Actualiza la ventana para mostrar los cambios
        }
    }

    e->accept();  // Acepta el evento del mouse
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        mEmpieza_Mouse = e->pos();
        mEmpieza_Mouse.setX(mEmpieza_Mouse.x() - 120);
        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {

        if(mAccion == 1) {

            // Acción 1: Dibujar una linea
            QPen pen(mColor, mTamano_Pincel, Qt::SolidLine, Qt::SquareCap);
            mPainter->setPen(pen);
            mTermina_Mouse = e->pos();
            mTermina_Mouse.setX(mTermina_Mouse.x() - 120);
            QLine line(mEmpieza_Mouse, mTermina_Mouse);
            mPainter->drawLine(line);
            mCambio = true;
            update();
        } else if (mAccion == 2 && mImage) {

            // Acción 2: Dibujar el rectángulo vacio
            QPen pen(mColor, mTamano_Pincel, Qt::SolidLine, Qt::SquareCap);
            mPainter->setPen(pen);
            mTermina_Mouse = e->pos();
            mTermina_Mouse.setX(mTermina_Mouse.x() - 120);
            QRect rect(mEmpieza_Mouse, mTermina_Mouse);
            mPainter->drawRect(rect);
            mCambio = true;
            update();
        } else if(mAccion == 3) {

            // Acción 4: Dibujar elipse
            QPen pen(mColor, mTamano_Pincel, Qt::SolidLine, Qt::SquareCap);
            mPainter->setPen(pen);
            mTermina_Mouse = e->pos();
            mTermina_Mouse.setX(mTermina_Mouse.x() - 120);
            QRect rect(mEmpieza_Mouse, mTermina_Mouse);
            mPainter->drawEllipse(rect);
            mCambio = true;
            update();
        }

        else if (mAccion == 4 && mImage) {

            // Acción 4: Dibujar un triangulo
            QPen pen(mColor, mTamano_Pincel, Qt::SolidLine, Qt::SquareCap);
            mPainter->setPen(pen);
            QPolygon polygon;
            mTermina_Mouse = e->pos();
            mTermina_Mouse.setX(mTermina_Mouse.x() - 120);
            polygon << mEmpieza_Mouse;
            polygon << mTermina_Mouse;
            polygon << QPoint(mEmpieza_Mouse.x(), mTermina_Mouse.y());
            mPainter->drawConvexPolygon(polygon);
            mCambio = true;
            update();
        }

        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::on_tamano_clicked()
{
    bool ok;

    int nuevoTamano = QInputDialog::getInt(this, tr("Drawfull"),
                                           tr("Tamaño del pincel"),
                                           mTamano_Pincel,
                                           1,
                                           250,
                                           1,
                                           &ok);
    if (ok) {
        mTamano_Pincel = nuevoTamano;
    }
}

void MainWindow::on_color_clicked()
{
    if (mBorrador== true){
        return ;
    } else{
        mColor = QColorDialog::getColor(Qt::black,this,"Color de la brocha");// cambiando color
        mColor_Auxiliar = mColor;
    }
}



// activacion del borrador
void MainWindow::on_borrador_clicked()
{
    mBorrador = true;
    mAccion = 0;
    mColor_Auxiliar = mColor; // Guarda el color antes de borrar
    mColor = QColor(Qt::white); // Pone de color blanco el pincel
}

void MainWindow::on_pincel_clicked()
{
    mBorrador = false;
    mAccion = 0;
    mColor = mColor_Auxiliar; // Guarda el color antes de borrar
}


void MainWindow::on_linea_clicked()
{
    mBorrador = false;
    mAccion = 1;
    mColor = mColor_Auxiliar; // Guarda el color antes de borrar
}


void MainWindow::on_rectangulo_clicked()
{
    mBorrador = false;
    mAccion = 2;
    mColor = mColor_Auxiliar; // Guarda el color antes de borrar
}


void MainWindow::on_elipse_clicked()
{
    mBorrador = false;
    mAccion = 3;
    mColor =mColor_Auxiliar; // Guarda el color antes de borrar
}


void MainWindow::on_triangulo_clicked()
{
    mBorrador = false;
    mAccion = 4;
    mColor = mColor_Auxiliar; // Guarda el color antes de borrar
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    if (mTalvez()) {
        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::on_cerrar_clicked()
{
    close();
}

bool MainWindow::mTalvez()
{
    // Verificar si ha habido cambios desde la última vez que se guardó
    if (mCambio) {
        QMessageBox::StandardButton ret;

        // Título y mensaje del cuadro de diálogo
        ret = QMessageBox::warning(this, tr("DrawFull"),
                                   tr("Esta imagen ha sido modificada.\n"
                                      "¿Quieres guardar los cambios?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        // Procesar la respuesta del usuario
        if (ret == QMessageBox::Save) {
            // Si el usuario elige guardar, llamar a la función saveFile() para guardar el archivo
            bool Guardo = mGuardar(*mImage);
            if (!Guardo) {
                // Si ocurrió un error al guardar, puedes mostrar un mensaje adicional o realizar acciones necesarias
                QMessageBox::critical(this, tr("Error al guardar"),
                                      tr("No se pudo guardar la imagen. ¡Inténtalo de nuevo!"));
                return false; // Indicar que la operación no se realizó con éxito
            }


            // Si se guardó exitosamente, continuar con la operación
        } else if (ret == QMessageBox::Discard) {
            // Si el usuario elige descartar los cambios, continuar sin guardar
            // Puedes implementar aquí la lógica para descartar los cambios
        } else if (ret == QMessageBox::Cancel) {
            // Si el usuario elige cancelar, abortar la operación y devolver false
            return false;
        }
    }

    // Si no hay cambios o si se han manejado los cambios, devolver true para continuar
    return true;
}

void MainWindow::on_guardar_clicked()
{
    mGuardar(*mImage);
}



void MainWindow::on_abrir_clicked()
{    
    if (mTalvez()) {
        QString rutaArchivo = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
        QFileInfo informacionArchivo(rutaArchivo);
        if (!rutaArchivo.isEmpty()){
            QImage imagenCargada(rutaArchivo);
            if (!imagenCargada.isNull()) {
                mPainter->drawImage(0,0,imagenCargada);
                mCambio = false;
                setWindowTitle("Drawfull: " + informacionArchivo.fileName());
                update();
            } else {
                QMessageBox::critical(this, tr("Error al abrir imagen"),
                                      tr("No se pudo cargar la imagen: ") + informacionArchivo.fileName());
            }
        } else {
            QMessageBox::critical(this, tr("Error al abrir imagen"),
                                  tr("No se pudo cargar la imagen: ")  + informacionArchivo.fileName());
        }
    }
}



void MainWindow::on_nuevo_clicked()
{
    mCambio = false;
    mImage->fill(Qt::white);
    setWindowTitle("Drawfull: Nuevo archivo");
    update();
}



bool MainWindow::mGuardar(const QImage &imagen)
{
    // Verificar si la imagen es válida
    if (imagen.isNull()) {
        QMessageBox::critical(this, tr("Error al guardar"),
                              tr("No se pudo guardar la imagen. ¡Inténtalo de nuevo!"));
        return false;
    }

    // Obtener la ruta de archivo seleccionada por el usuario
    QString rutaArchivo = QFileDialog::getSaveFileName(this, "Guardar Imagen", QDir::homePath(),"Imágenes (*.png *.jpg *.bmp)");

    // Verificar si el usuario canceló la selección
    if (rutaArchivo.isEmpty()) {
        QMessageBox::critical(this, tr("Error al guardar"),
                              tr("Operación de guardado cancelada por el usuario."));

        return false;
    }

    // Obtener el formato de archivo según la extensión del nombre de archivo
    QFileInfo informacionArchivo(rutaArchivo);
    QString formato = informacionArchivo.suffix().toLower(); // Obtener la extensión en minúsculas

    // Crear un QImageWriter para guardar la imagen en el formato adecuado
    QImageWriter writer(rutaArchivo, formato.toUtf8());
    if (!writer.canWrite()) {
        QMessageBox::critical(this, tr("Error al guardar"),
                              tr("Error: No se puede escribir en el archivo"));
        return false;
    }

    // Escribir la imagen en el archivo
    if (!writer.write(imagen)) {
        QMessageBox::critical(this, tr("Error al guardar"),
                              tr("Error al escribir la imagen en: ") + rutaArchivo);

        return false;
    }
    QMessageBox::information(this, tr("Éxito al guardar"),
                             tr("Imagen guardada exitosamente en: ")  + rutaArchivo);

    mCambio = false;
    setWindowTitle("Drawfull: " + informacionArchivo.fileName());
    return true;
}

void MainWindow::on_link_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/JuanJowski/Drawfull"));
}

