#ifndef MAINWINDOW_H  // Directiva de preprocesador para evitar la inclusión múltiple
#define MAINWINDOW_H
#include <QMainWindow>  // Incluye la clase QMainWindow para la ventana principal de la aplicación

QT_BEGIN_NAMESPACE
namespace Ui {
class DrawFul;
}
QT_END_NAMESPACE

class QPainter;  // Declaración anticipada de la clase QPainter para dibujar en la ventana
class QImage;    // Declaración anticipada de la clase QImage para manejar imágenes

class MainWindow : public QMainWindow  // Definición de la clase MainWindow heredando de QMainWindow
{
    Q_OBJECT  // Macro necesaria para usar la funcionalidad de señales y ranuras de Qt

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor de la clase MainWindow
    ~MainWindow();                           // Destructor de la clase MainWindow

protected:
    void paintEvent(QPaintEvent *e) override;          // Método para manejar eventos de pintado
    void mousePressEvent(QMouseEvent *e) override;     // Método para manejar eventos de clic del mouse
    void mouseMoveEvent(QMouseEvent *e) override;      // Método para manejar eventos de movimiento del mouse
    void mouseReleaseEvent(QMouseEvent *e) override;   // Método para manejar eventos de liberación del mouse
    void closeEvent(QCloseEvent *event) override;      //Método para manejar el evento de cerrar la ventana


private slots:

    void on_color_clicked();

    void on_tamano_clicked();

    void on_borrador_clicked();

    void on_pincel_clicked();

    void on_linea_clicked();

    void on_rectangulo_clicked();

    void on_elipse_clicked();

    void on_triangulo_clicked();

    void on_cerrar_clicked();

    void on_guardar_clicked();

    void on_abrir_clicked();

    void on_nuevo_clicked();

    void on_link_clicked();

private:

    Ui::DrawFul *ui;            // Puntero al objeto de la interfaz de usuario
    QPainter *mPainter;         // Puntero al objeto QPainter para pintar sobre el pincel
    QImage *mImage;             // Puntero al objeto QImage donde se pintará
    bool mTalvez();
    bool mGuardar(const QImage &imagen);
    QPoint mEmpieza_Mouse;      // Punto de inicio del evento del mouse
    QPoint mTermina_Mouse;      // Punto de finalización del evento del mouse
    QColor mColor;              //  guardará el color del pincel
    QColor mColor_Auxiliar;     // variable global para guardar el color antes de usar el borrador
    bool mCambio;               // Estado que indica si se a cambiado o no la imagen
    bool mBorrador;             // Estado que indica si se está borrando o no
    int mAccion;                // Indicador de que accion que se esta haciendo
    int mTamano_Pincel;         // se define el parametro ( atributo ) que guardará el tamaño del pincel

};
#endif // MAINWINDOW_H
