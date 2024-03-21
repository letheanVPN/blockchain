#include "websocketclientwrapper.h"
#include "websockettransport.h"

#include <QWebSocketServer>

/*!
    \brief Wraps connected QWebSockets clients in WebSocketTransport objects.

    This code is all that is required to connect incoming WebSockets to the WebChannel. Any kind
    of remote JavaScript client that supports WebSockets can thus receive messages and access the
    published objects.
*/

/*!
    Construct the client wrapper with the given parent.

    All clients connecting to the QWebSocketServer will be automatically wrapped
    in WebSocketTransport objects.
*/
WebSocketClientWrapper::WebSocketClientWrapper(QWebSocketServer *server, QObject *parent)
    : QObject(parent)
      , m_server(server)
{
  connect(server, &QWebSocketServer::newConnection,
          this, &WebSocketClientWrapper::handleNewConnection);
}

/*!
    Wrap an incoming WebSocket connection in a WebSocketTransport object.
*/
void WebSocketClientWrapper::handleNewConnection()
{
  emit clientConnected(new WebSocketTransport(m_server->nextPendingConnection()));
}
