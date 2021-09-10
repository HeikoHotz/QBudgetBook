#include <QApplication>
#include <QDebug>
#include "QBudgetBookMainWindow.h"

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
	const char* msg = message.toUtf8().data();
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        fflush(stderr);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        fflush(stderr);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        fflush(stderr);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        fflush(stderr);
        abort();
        break;
    default:
    	break;
    }
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(messageHandler);

	// Set application information
	QApplication app(argc, argv);

	qDebug() << "QBudgetBook ....start app";

	QBudgetBookMainWindow win;
	win.initScreen();
	win.show();

	return app.exec();
}
