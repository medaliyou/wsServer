#ifndef SERVER_H
#define SERVER_H
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtWebSockets/QWebSocketServer>

class Server : public QObject
{
    Q_OBJECT

public:
    //Server() {}

    explicit Server(quint16 port, bool secure=false, QObject *parent=nullptr);

    //virtual ~Server() {}
    ~Server() override;

private slots:
    void logMessage(QWebSocket *pSender, const QString &message);
    QWebSocketServer* initiateSecureServer();
    //! To do
    //! Add json data exchange
    //! Add Security options in both client server sides
    //! Add bizzare request handler
    //! Add multi clients load balancer
    //! Add a proxy server for the handshake only
    //! ******************************************
    void onNewConnection();
    void processMessage(const QString &message);
    void processBinaryMessage(QByteArray message);
    void onSslErrors(const QList<QSslError> &errors);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};


#endif // SERVER_H
