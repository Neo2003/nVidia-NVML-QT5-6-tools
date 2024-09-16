
#include "MainWindow.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/rc/icon.ico"));
    MainWindow *dialog = new MainWindow();
    dialog->show(); 

    return app.exec();   
}
