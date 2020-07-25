#include "server.h"
#include <QtCore>
#include <QtWebSockets>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

QT_USE_NAMESPACE

static QString getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg( peer->peerAddress().toString(), QString::number(peer->peerPort() ) );

}

//! [initiateSecureServer]
QWebSocketServer* Server::initiateSecureServer()
{

    QWebSocketServer *lm_pWebSocketServer = new QWebSocketServer(QStringLiteral("Secure Web Socket Server"),
                                              QWebSocketServer::SecureMode,
                                              this);
    QSslConfiguration sslConfiguration;
    QString path = "/root/dev/QtDev/wsServer/";
    QString certPath = path + "localhost.cert";
    QString keyPath = path + "localhost.key";
    QFile certFile(certPath);
    QFile keyFile(keyPath);

    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);

    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);

    certFile.close();
    keyFile.close();

    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    lm_pWebSocketServer->setSslConfiguration(sslConfiguration);
    qDebug("Done Constructing the m_pWebSocketServer");
    return lm_pWebSocketServer;
}

//! [Constructor]
Server::Server(quint16 port, bool secure, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(nullptr)
{
    if(secure){
        m_pWebSocketServer = initiateSecureServer();
    }
    else
    {
       m_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"),  QWebSocketServer::NonSecureMode, this);
    }

    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server listening on port" << port;
        QTextStream(stdout) << "[+] Server listening on port " << port << '\n';
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
    }
    else
    {
        QTextStream(stdout) << "[-] Can' listen on port " << port << '\n';

    }
}

//! [Destructor]
Server::~Server()
{
    m_pWebSocketServer->close();
}
//! [Destructor]

//! [onNewConnection]
void Server::onNewConnection()
{
    auto pSocket = m_pWebSocketServer->nextPendingConnection();
    QTextStream(stdout) <<"[+] "<< getIdentifier(pSocket) << " connected!\n";
    pSocket->setParent(this);
    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived,this, &Server::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected , this, &Server::socketDisconnected);
    m_clients << pSocket;
}


//! [logMessage]
void Server::logMessage(QWebSocket *pSender, const QString &message)
{
    QTextStream(stdout) <<"[!] "<< getIdentifier(pSender) << " send "<< message.trimmed() << "\n";

}



//! [processBinaryMessage]
void Server::processBinaryMessage(QByteArray message)
{

    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    logMessage(pSender, message);
    for(QWebSocket *pClient : qAsConst(m_clients)){

        // *************************************
        // don't echo message back to sender
        // *************************************

        if(pClient != pSender) {
            pClient->sendBinaryMessage(message);
        }
    }

}






//! [processMessage]
void Server::processMessage(const QString &message)
{

    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    logMessage(pSender, message);
    for(QWebSocket *pClient : qAsConst(m_clients)){

        // *************************************
        // don't echo message back to sender
        // *************************************

        if(pClient != pSender) {
            pClient->sendTextMessage(message);
        }
    }

}



//! [onSslErrors]
void Server::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "SSL errors occurred";
    QTextStream(stdout) <<"[-] "<<"SSL errors occurred!\n";

    foreach( const QSslError &error, errors )
    {
          qDebug() << "SSL Error: " << error.errorString();
          QTextStream(stdout) <<"[-] "<<"SSL Error" << error.errorString() << "\n";

    }

}



//! [socketDisconnected]
void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) <<"[+] " << getIdentifier(pClient) << " disconnected!\n";
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}


























