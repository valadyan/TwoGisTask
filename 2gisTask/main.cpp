#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FileParser.h"
#include "Top.h"

int main(int argc, char *argv[])
{

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  TopController* topController = new TopController();
  engine.rootContext()->setContextObject(topController);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  QFile* file = new QFile("text.txt");
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    return app.exec();

  FileParser* fileParser = new FileParser(file);


  QObject::connect(fileParser, &FileParser::sendWord,
                   topController, &TopController::addWordInTop);
  QObject::connect(fileParser, &FileParser::eof,
                   topController, &TopController::endOfFile);

  fileParser->readFile();

  return app.exec();
}
