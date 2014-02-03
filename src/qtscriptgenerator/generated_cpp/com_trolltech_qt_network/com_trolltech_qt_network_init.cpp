#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QAuthenticator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslKey_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslCertificateExtension_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkRequest_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsServiceRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAddressEntry_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxyFactory_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkInterface_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookie_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSsl_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslError_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslCipher_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxy_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHostInfo_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkConfiguration_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsTextRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCacheMetaData_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxyQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslCertificate_class(QScriptEngine *engine);
QScriptValue qtscript_create_QIPv6Address_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsMailExchangeRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslConfiguration_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsDomainNameRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsHostAddressRecord_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttpPart_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHostAddress_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkConfigurationManager_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAccessManager_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookieJar_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkSession_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractNetworkCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHttpMultiPart_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDnsLookup_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkReply_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkDiskCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QUdpSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSslSocket_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_network_class_names[] = {
    "QAuthenticator"
    , "QSslKey"
    , "QSslCertificateExtension"
    , "QNetworkRequest"
    , "QDnsServiceRecord"
    , "QNetworkAddressEntry"
    , "QNetworkProxyFactory"
    , "QNetworkInterface"
    , "QNetworkCookie"
    , "QSsl"
    , "QSslError"
    , "QSslCipher"
    , "QNetworkProxy"
    , "QHostInfo"
    , "QNetworkConfiguration"
    , "QDnsTextRecord"
    , "QNetworkCacheMetaData"
    , "QNetworkProxyQuery"
    , "QSslCertificate"
    , "QIPv6Address"
    , "QDnsMailExchangeRecord"
    , "QSslConfiguration"
    , "QDnsDomainNameRecord"
    , "QDnsHostAddressRecord"
    , "QHttpPart"
    , "QHostAddress"
    , "QNetworkConfigurationManager"
    , "QTcpServer"
    , "QNetworkAccessManager"
    , "QLocalServer"
    , "QNetworkCookieJar"
    , "QNetworkSession"
    , "QAbstractNetworkCache"
    , "QHttpMultiPart"
    , "QDnsLookup"
    , "QLocalSocket"
    , "QAbstractSocket"
    , "QNetworkReply"
    , "QNetworkDiskCache"
    , "QTcpSocket"
    , "QUdpSocket"
    , "QSslSocket"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_network_class_functions[] = {
    qtscript_create_QAuthenticator_class
    , qtscript_create_QSslKey_class
    , qtscript_create_QSslCertificateExtension_class
    , qtscript_create_QNetworkRequest_class
    , qtscript_create_QDnsServiceRecord_class
    , qtscript_create_QNetworkAddressEntry_class
    , qtscript_create_QNetworkProxyFactory_class
    , qtscript_create_QNetworkInterface_class
    , qtscript_create_QNetworkCookie_class
    , qtscript_create_QSsl_class
    , qtscript_create_QSslError_class
    , qtscript_create_QSslCipher_class
    , qtscript_create_QNetworkProxy_class
    , qtscript_create_QHostInfo_class
    , qtscript_create_QNetworkConfiguration_class
    , qtscript_create_QDnsTextRecord_class
    , qtscript_create_QNetworkCacheMetaData_class
    , qtscript_create_QNetworkProxyQuery_class
    , qtscript_create_QSslCertificate_class
    , qtscript_create_QIPv6Address_class
    , qtscript_create_QDnsMailExchangeRecord_class
    , qtscript_create_QSslConfiguration_class
    , qtscript_create_QDnsDomainNameRecord_class
    , qtscript_create_QDnsHostAddressRecord_class
    , qtscript_create_QHttpPart_class
    , qtscript_create_QHostAddress_class
    , qtscript_create_QNetworkConfigurationManager_class
    , qtscript_create_QTcpServer_class
    , qtscript_create_QNetworkAccessManager_class
    , qtscript_create_QLocalServer_class
    , qtscript_create_QNetworkCookieJar_class
    , qtscript_create_QNetworkSession_class
    , qtscript_create_QAbstractNetworkCache_class
    , qtscript_create_QHttpMultiPart_class
    , qtscript_create_QDnsLookup_class
    , qtscript_create_QLocalSocket_class
    , qtscript_create_QAbstractSocket_class
    , qtscript_create_QNetworkReply_class
    , qtscript_create_QNetworkDiskCache_class
    , qtscript_create_QTcpSocket_class
    , qtscript_create_QUdpSocket_class
    , qtscript_create_QSslSocket_class
};

void qtscript_initialize_com_trolltech_qt_network_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 42; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_network_class_names[i],
            qtscript_com_trolltech_qt_network_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
