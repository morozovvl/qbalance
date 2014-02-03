/****************************************************************************
**
** Copyright (C) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Script Generator project on Qt Labs.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "setupgenerator.h"
#include "reporthandler.h"
#include "fileout.h"

//#define Q_SCRIPT_LAZY_GENERATOR

void SetupGenerator::addClass(const AbstractMetaClass *cls) 
{
    packHash[cls->package()].append(cls);
}

void writeQtScriptQtBindingsLicense(QTextStream &stream);

void maybeDeclareMetaType(QTextStream &stream, const QString &typeName,
                          QSet<QString> &registeredTypeNames);
bool hasDefaultConstructor(const AbstractMetaClass *meta_class);

void SetupGenerator::generate()
{
    QHashIterator<QString, QList<const AbstractMetaClass*> > pack(packHash);
    while (pack.hasNext()) {
        pack.next();
        QList<const AbstractMetaClass*> list = pack.value();
        if (list.isEmpty())
            continue;

        QString packName = pack.key();
        QStringList components = packName.split(".");
        if ((components.size() > 2) && (components.at(0) == "com")
            && (components.at(1) == "trolltech")) {
            // kill com.trolltech in key
            components.removeAt(0);
            components.removeAt(0);
        }
        packName.replace(".", "_");

        {
            FileOut initFile(m_out_dir + "/generated_cpp/" + packName + "/" + packName + "_init.cpp");
            QTextStream &s = initFile.stream;

            if (FileOut::license)
                writeQtScriptQtBindingsLicense(s);

            s << "#include <QtScript/QScriptValue>" << endl
              << "#include <QtScript/QScriptEngine>" << endl;
#ifdef Q_SCRIPT_LAZY_GENERATOR
            s << "#include <QtScript/QScriptClass>" << endl
              << "#include <QtScript/QScriptString>" << endl;
#endif
            s << endl;

            // declare individual class creation functions
            foreach (const AbstractMetaClass *cls, list) {
                s << "QScriptValue qtscript_create_" << cls->name() << "_class(QScriptEngine *engine);" << endl;
            }
            s << endl;

            // write table of class names
            {
                s << "static const char * const qtscript_" << packName << "_class_names[] = {" << endl;
                bool needComma = false;
                foreach (const AbstractMetaClass *cls, list) {
                    s << "    ";
                    if (needComma)
                        s << ", ";
                    s << "\"" << cls->name() << "\"" << endl;
                    needComma = true;
                }
                s << "};" << endl << endl;
            }

            // write table of function pointers
            {
                s << "typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);" << endl;
                s << "static const QtBindingCreator qtscript_" << packName << "_class_functions[] = {" << endl;
                bool needComma = false;
                foreach (const AbstractMetaClass *cls, list) {
                    s << "    ";
                    if (needComma)
                        s << ", ";
                    s << "qtscript_create_" << cls->name() << "_class" << endl;
                    needComma = true;
                }
                s << "};" << endl << endl;
            }

#ifdef Q_SCRIPT_LAZY_GENERATOR
            {
                // declare meta-types
                QSet<QString> registeredTypeNames = m_qmetatype_declared_typenames;
                foreach (const AbstractMetaClass *cls, list) {
                    if (cls->isNamespace())
                        continue;
                    QString name = cls->qualifiedCppName();
                    if (cls->typeEntry()->isValue() && ::hasDefaultConstructor(cls))
                        maybeDeclareMetaType(s, name, registeredTypeNames);
                    maybeDeclareMetaType(s, name + "*", registeredTypeNames);
                }
                s << endl;
                // write table of metatype-ids
                s << "static const int qtscript_" << packName << "_metatype_ids[] = {" << endl;
                for (int i = 0; i < list.size(); ++i) {
                    const AbstractMetaClass *cls = list.at(i);
                    s << "    ";
                    if (i > 0)
                        s << ", ";
                    if (cls->isNamespace()) {
                        s << "-1, -1";
                    } else {
                        QString name = cls->qualifiedCppName();
                        if (cls->typeEntry()->isValue() && ::hasDefaultConstructor(cls))
                            s << "qMetaTypeId<" << name << ">()";
                        else
                            s << "-1";
                        s << ", qMetaTypeId<" << name << "*>()";
                    }
                    s << endl;
                }
                s << "};" << endl << endl;
            }

            // write the fake prototype class
            {
                s << "class qtscript_" << packName << "_FakePrototype : public QScriptClass" << endl
                  << "{" << endl
                  << "public:" << endl
                  << "    qtscript_" << packName << "_FakePrototype(QScriptEngine *engine)" << endl
                  << "        : QScriptClass(engine) {}" << endl << endl

                  << "    QueryFlags queryProperty(const QScriptValue &fake," << endl
                  << "        const QScriptString &name, QueryFlags flags, uint *)" << endl
                  << "    {" << endl
                  << "        if (fake.prototype().isValid())" << endl
                  << "            return 0;" << endl
                  << "        int classIndex = fake.data().toInt32();" << endl
                  << "        const char *className = qtscript_" << packName << "_class_names[classIndex];" << endl
//              << "        qDebug() << \"faking\" << className;" << endl
                  << "        QScriptValue extensionObject = engine()->globalObject();" << endl
                  << "        QScriptValue ctor = extensionObject.property(className);" << endl
                  << "        QScriptValue genuine = ctor.property(\"prototype\");" << endl
                  << "        Q_ASSERT(genuine.isObject());" << endl
                  << "        const_cast<QScriptValue&>(fake).setPrototype(genuine);" << endl
                  << "        if (!genuine.property(name).isValid())" << endl
                  << "            flags &= ~HandlesReadAccess;" << endl
                  << "        return flags & ~HandlesWriteAccess;" << endl
                  << "    }" << endl << endl

                  << "    QScriptValue property(const QScriptValue &fake, "
                  << "const QScriptString &name, uint)" << endl
                  << "    {" << endl
                  << "        return fake.prototype().property(name, QScriptValue::ResolveLocal);" << endl
                  << "    }" << endl
                  << "};" << endl << endl;
            }

            // write the lazy class loader
            {
                s << "static QScriptValue qtscript_" << packName << "_getSetClass("
                  << "QScriptContext *context, QScriptEngine *engine)" << endl
                  << "{" << endl
                  << "    QScriptValue target = context->thisObject();" << endl
                  << "    int classIndex = context->callee().data().toInt32();" << endl
                  << "    const char *className = qtscript_" << packName << "_class_names[classIndex];" << endl
                  << "    qDebug() << \"loading\" << className;" << endl
                  << "    target.setProperty(className, QScriptValue(), "
                  << "QScriptValue::PropertyGetter|QScriptValue::PropertySetter);" << endl
                  << "    if (context->argumentCount() == 1) {" << endl
                  << "        target.setProperty(className, context->argument(0));" << endl
                  << "    } else {" << endl
                  << "        target.setProperty(className, qtscript_"
                  << packName << "_class_functions[classIndex](engine)," << endl
                  << "            QScriptValue::SkipInEnumeration);" << endl
                  << "    }" << endl
                  << "    return target.property(className);" << endl
                  << "}" << endl << endl;
            }
#endif

            // bindings init function
            s << "void qtscript_initialize_" << packName << "_bindings(QScriptValue &extensionObject)" << endl
              << "{" << endl
              << "    QScriptEngine *engine = extensionObject.engine();" << endl;
#ifdef Q_SCRIPT_LAZY_GENERATOR
            s << "    qtscript_" << packName << "_FakePrototype *fakeProtoClass;" << endl
              << "    fakeProtoClass = new qtscript_" << packName << "_FakePrototype(engine);" << endl;
#endif
            s << "    for (int i = 0; i < " << list.size() << "; ++i) {" << endl
#ifndef Q_SCRIPT_LAZY_GENERATOR
              << "        extensionObject.setProperty(qtscript_" << packName << "_class_names[i]," << endl
              << "            qtscript_" << packName << "_class_functions[i](engine)," << endl
              << "            QScriptValue::SkipInEnumeration);" << endl
#else
              << "        QScriptValue classIndex(engine, i);" << endl
              << "        QScriptValue fakeCtor = engine->newFunction(qtscript_" << packName << "_getSetClass);" << endl
              << "        fakeCtor.setData(classIndex);" << endl
              << "        extensionObject.setProperty(qtscript_" << packName << "_class_names[i]," << endl
              << "            fakeCtor, QScriptValue::PropertyGetter|QScriptValue::PropertySetter"
              << "|QScriptValue::SkipInEnumeration);" << endl
              << "        QScriptValue fakeProto = engine->newObject(fakeProtoClass, classIndex);" << endl
              << "        fakeProto.setPrototype(QScriptValue());" << endl
              << "        if (qtscript_" << packName << "_metatype_ids[i*2] != -1)" << endl
              << "            engine->setDefaultPrototype(qtscript_"
              << packName << "_metatype_ids[i*2], fakeProto);" << endl
              << "        if (qtscript_" << packName << "_metatype_ids[i*2+1] != -1)" << endl
              << "            engine->setDefaultPrototype(qtscript_"
              << packName << "_metatype_ids[i*2+1], fakeProto);" << endl
#endif
              << "    }" << endl
              << "}" << endl;

            if (initFile.done())
                ++m_num_generated_written;
            ++m_num_generated;
        }

        {
            FileOut pluginFile(m_out_dir + "/generated_cpp/" + packName + "/plugin.h");
            QTextStream &s = pluginFile.stream;

            if (FileOut::license)
                writeQtScriptQtBindingsLicense(s);

            s << "#ifndef PLUGIN_H" << endl
              << "#define PLUGIN_H" << endl << endl;

            s << "#include <QtScript/QScriptExtensionPlugin>" << endl
              << "#include <QtScript/QScriptValue>" << endl
              << "#include <QtScript/QScriptEngine>" << endl << endl;

            // declare the init function
            s << "Q_DECL_HIDDEN void qtscript_initialize_" << packName << "_bindings(QScriptValue &);" << endl << endl;

            // plugin class declaration
            s << "class " << packName << "_ScriptPlugin : public QScriptExtensionPlugin" << endl
              << "{" << endl
              << "    Q_OBJECT" << endl
              << "#if QT_VERSION >= 0x050000" << endl
              << "    Q_PLUGIN_METADATA(IID \"org.qt-project.Qt.QScriptExtensionInterface\")" << endl
              << "#endif" << endl
              << "public:" << endl
              << "    QStringList keys() const;" << endl
              << "    void initialize(const QString &key, QScriptEngine *engine);" << endl
              << "};" << endl
              << "" << endl
              << "#endif // PLUGIN_H" << endl;

            if (pluginFile.done())
                ++m_num_generated_written;
            ++m_num_generated;
        }

        {
            FileOut pluginFile(m_out_dir + "/generated_cpp/" + packName + "/plugin.cpp");
            QTextStream &s = pluginFile.stream;

            if (FileOut::license)
                writeQtScriptQtBindingsLicense(s);

            s << "#include \"plugin.h\"" << endl << endl;

            // keys()
            s << "QStringList " << packName << "_ScriptPlugin::keys() const" << endl
              << "{" << endl
              << "    QStringList list;" << endl;
            {
                QString key;
                for (int i = 0; i < components.size(); ++i) {
                    if (i > 0)
                        key.append(".");
                    key.append(components.at(i));
                    s << "    list << QLatin1String(\"" << key << "\");" << endl;
                }
            }
            s << "    return list;" << endl
              << "}" << endl;

            // initialize()
            s << endl
              << "void " << packName << "_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)" << endl
              << "{";
            {
                QString key;
                for (int i = 0; i < components.size(); ++i) {
                    s << endl << "    ";
                    if (i > 0) {
                        key.append(".");
                        s << "} else ";
                    }
                    key.append(components.at(i));
                    s << "if (key == QLatin1String(\"" << key << "\")) {";
                }
            }
            s << endl << "        QScriptValue extensionObject = ";
            // ### generalize
            if (packName == "com.trolltech.qt.phonon")
                s << "setupPackage(\"phonon\", engine)";
            else
                s << "engine->globalObject()";
            s << ";" << endl;

            s << "        qtscript_initialize_" << packName << "_bindings(extensionObject);" << endl;

            s << "    } else {" << endl
              << "        Q_ASSERT_X(false, \"" << packName << "::initialize\", qPrintable(key));" << endl
              << "    }" << endl
              << "}" << endl << endl;

            s << "#if QT_VERSION < 0x050000" << endl
              << "Q_EXPORT_STATIC_PLUGIN(" << packName << "_ScriptPlugin)" << endl
              << "Q_EXPORT_PLUGIN2(qtscript_" << packName.toLower() << ", " << packName << "_ScriptPlugin)" << endl
              << "#endif" << endl;

            if (pluginFile.done())
                ++m_num_generated_written;
            ++m_num_generated;
        }
    }
}
