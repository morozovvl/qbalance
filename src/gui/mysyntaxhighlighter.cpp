#include <QDebug>
#include "mysyntaxhighlighter.h"
#include "../engine/scriptengine.h"


MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat singleLineCommentFormat;

    // Установим правила подсветки синтаксиса для ключевых слов
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "break" << "case" << "catch" << "const" \
                    << "continue" << "default"  << "do" << "else" \
                    << "finally" << "for"  << "function" << "if" \
                    << "in" << "new"  << "prototype" << "return" \
                    << "switch" << "this"  << "typeof" << "throw" \
                    << "try" << "var"  << "while" << "with" \
                    << "boolean" << "byte"  << "char" << "throws" \
                    << "double" << "enum"  << "export" << "float" \
                    << "goto" << "implements"  << "import" << "int" \
                    << "interface" << "long"  << "native" << "short";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp("\\b" + pattern + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Установим правила подсветки для классов
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    // Установим правила подсветки для строковых типов в кавычках
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.pattern.setMinimal(true);
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // Установим правила подсветки для строковых типов в апострофах
    rule.pattern = QRegExp("'.*'");
    rule.pattern.setMinimal(true);
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // Установим правила подсветки для функций
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // Установим правила подсветки для однострочных комментариев
    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    // Установим правила подсветки для многострочных комментариев
    multiLineCommentFormat.setForeground(Qt::gray);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}


void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
         if (previousBlockState() != 1)
             startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
           setCurrentBlockState(1);
           commentLength = text.length() - startIndex;
        } else {
           commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
           }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
}
