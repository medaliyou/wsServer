#ifndef SERVER_H
#define SERVER_H
#include <QtCore/QList>
#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>


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
    void logTransaction(QWebSocket *pSender, const QJsonObject &JSON);
    void logTransaction(QWebSocket *pSender, const QString& strJSON);

    QWebSocketServer* initiateSecureServer();
    QWebSocketServer* initiateNonSecureServer();

    //! To do
    //! Add json data exchange 0x1
    //! Add Security options in both client server sides
    //! Add bizzare request handler
    //! Add multi clients load balancer
    //! Add a proxy server for the handshake only
    //! ******************************************
    void onNewConnection();
    void processMessage(const QString &message);
    void onSslErrors(const QList<QSslError> &errors);
    void socketDisconnected();
    int currentClientsCount();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};


#endif // SERVER_H
