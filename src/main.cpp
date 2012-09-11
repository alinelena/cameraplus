#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QtDeclarative>
#include <QGLWidget>

#include "imports/plugin.h"

#include "settings.h"
#include "filenaming.h"
#include "quillitem.h"
#include "displaystate.h"

Q_DECL_EXPORT int main(int argc, char *argv[]) {
  QApplication::setAttribute(Qt::AA_X11InitThreads, true);
  QApplication app(argc, argv);

  QDeclarativeView view;
  view.setViewport(new QGLWidget);
  view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
  view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  Plugin::registerTypes(view.engine());
  qmlRegisterType<Settings>("CameraPlus", 1, 0, "Settings");
  qmlRegisterType<FileNaming>("CameraPlus", 1, 0, "FileNaming");
  qmlRegisterType<QuillItem>("CameraPlus", 1, 0, "QuillItem");
  qmlRegisterType<DisplayState>("CameraPlus", 1, 0, "DisplayState");

  QUrl sourceUrl = QUrl::fromLocalFile(QDir::currentPath() + "/main.qml");
  view.setSource(sourceUrl);

  view.showFullScreen();

  int ret = app.exec();
  return ret;
};
