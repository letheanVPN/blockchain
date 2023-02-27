#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "mainwindow.h"
#include "include_base_utils.h"

#include <QApplication>
#include <QUrl>
#include <QWebChannel>
#include <QWebSocketServer>
#ifdef Q_OS_DARWIN
#  include "urleventfilter.h"
#endif
int main(int argc, char** argv)
{
//  epee::log_space::get_set_log_detalisation_level(true, LOG_LEVEL_0);
//  epee::log_space::get_set_need_thread_id(true, true);
//  epee::log_space::log_singletone::enable_channels("core,currency_protocol,tx_pool,p2p,wallet");

  QApplication app(argc, argv, Qt::SubWindow);

  // setup the QWebSocketServer
  QWebSocketServer webSocketServer(QStringLiteral("Lethean GUI Backend Server"), QWebSocketServer::NonSecureMode);
  if(!webSocketServer.listen(QHostAddress::LocalHost, 12345)) {
    qWarning() << "Failed to open web socket server." << webSocketServer.errorString();
    return 1;
  }
  WebSocketClientWrapper clientWrapper(&webSocketServer);

  // setup the channel
  QWebChannel channel;
  QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                   &channel, &QWebChannel::connectTo);
  MainWindow viewer;

  // register QObjects to be exposed to JavaScript
  if(!viewer.init_backend(argc, argv)) {
    return 1;
  }

  channel.registerObject(QStringLiteral("mediator_object"), &viewer);

#ifdef Q_OS_DARWIN
  URLEventFilter url_event_filter(&viewer);
  app.installEventFilter(&url_event_filter);
#endif
  app.installNativeEventFilter(&viewer);

  return app.exec();
}
