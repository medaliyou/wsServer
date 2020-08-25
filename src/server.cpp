#include "inc/server.h"
#include <QtCore>
#include <QtWebSockets>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

QT_USE_NAMESPACE

//! [getIdentifier]
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
    QString path = "/root/dev/QtDev/wsServer/ssl/";
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
    qDebug("[+] Done Constructing the secure m_pWebSocketServer");
    return lm_pWebSocketServer;
}

//! [initiateNonSecureServer]
QWebSocketServer* Server::initiateNonSecureServer()
{

    QWebSocketServer *lm_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"),  QWebSocketServer::NonSecureMode, this);
    qDebug("[+] Done Constructing the non secure m_pWebSocketServer");
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
       m_pWebSocketServer = initiateNonSecureServer();
    }

    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "[+] Server listening on port" << port;
        //QTextStream(stdout) << "[+] Server listening on port " << port << '\n';
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
    }
    else
    {
        QTextStream(stdout) << "[-] Can' listen on port " << port << '\n';
        qDebug() << m_pWebSocketServer->errorString();
        exit(EXIT_FAILURE);

    }
    QTextStream(stdout) << "[+] Server URL " << m_pWebSocketServer->serverUrl().toString() << "\n";

}

//! [Destructor]
Server::~Server()
{
    if(m_pWebSocketServer->isListening()){
        m_pWebSocketServer->close();
    }
    m_pWebSocketServer->deleteLater();
    m_pWebSocketServer = NULL;
}
//! [Destructor]


//! [onNewConnection]
void Server::onNewConnection()
{

    auto pSocket = m_pWebSocketServer->nextPendingConnection();
    //qDebug() <<"[+] "<< getIdentifier(pSocket) << " connected!\n";
    QTextStream(stdout) <<"[+] " << getIdentifier(pSocket) << " connected!\n";

    pSocket->setParent(this);
    pSocket->sendTextMessage("Hello Client " + getIdentifier(pSocket));
    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processMessage);
    connect(pSocket, &QWebSocket::disconnected , this, &Server::socketDisconnected);


    m_clients << pSocket;
    qDebug() << "[INFO] Clients Count ["<< currentClientsCount() << "]\n" ;

}


//! [CurentClientsCount]
int Server::currentClientsCount(){
    return m_clients.size();
}



//! [processMessage]
void Server::processMessage(const QString& message)
{

    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    QJsonDocument messageDocument = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject messageJson = messageDocument.object();
    logTransaction(pSender, messageJson);



    QJsonDocument responseDocument;
    QJsonObject responseJson = prepareJSONfromString("OK " + (QString)pSender->peerName() );
    responseDocument.setObject(responseJson);
    QString responseMessage = QString::fromUtf8(responseDocument.toJson(QJsonDocument::Compact));


    logTransaction(pSender, responseMessage);

/*
    QJsonObject responseMessage = prepareJSONfromString("OK");
*/
    for(QWebSocket *pClient : qAsConst(m_clients)){

        // *************************************
        // don't echo message back to sender
        // *************************************
        pClient->sendTextMessage(responseMessage);

        /*
        if(pClient != pSender) {
            pClient->sendTextMessage(responseMessage);
        }
        */
    }

}




//! [prepareJSONfromString]
QJsonObject Server::prepareJSONfromString(const QString message){
    // This method is needed to convert Server Responses into JSON
    // To ensure it's availibility with the FrontEnd WebSocket API
    QJsonObject responseJson;
    responseJson["server"] = m_pWebSocketServer->serverName();
    responseJson["status"] = "processed";
    responseJson["response_message"] = message;

    return responseJson;

}



//! [logTransaction]

void Server::logTransaction(QWebSocket *pSender, const QJsonObject& JSON){
    QJsonDocument answerDocument(JSON);
    QByteArray data = answerDocument.toJson(QJsonDocument::Compact);
    QString jsonString(data);
    QString strJSON(answerDocument.toJson(QJsonDocument::Compact));
    QTextStream(stdout) <<"[INFO] "<< getIdentifier(pSender) << "\n" << jsonString << "\n";


}
void Server::logTransaction(QWebSocket *pSender, const QString& strJSON){

    QTextStream(stdout) <<"[INFO] "<< getIdentifier(pSender) << "\n" << strJSON << "\n";


}
//! [logMessage]
void Server::logMessage(QWebSocket *pSender, const QString &message)
{
    QTextStream(stdout) <<"[!] "<< getIdentifier(pSender) << " send "<< message.trimmed() << "\n";

}


//! [onSslErrors]
void Server::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "[-] SSL errors occurred";
    //QTextStream(stdout) <<"[-] SSL errors occurred!\n";

    foreach( const QSslError &error, errors )
    {
          qDebug() << "[-] SSL Error: " << error.errorString();
          //QTextStream(stdout) <<"[-] "<<"SSL Error" << error.errorString() << "\n";

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
























