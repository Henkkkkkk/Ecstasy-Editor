#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QApplication>
#ifndef CPPSYNTAX_H
#define CPPSYNTAX_H

class CppSyntax : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CppSyntax(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat classFormat;
    QTextCharFormat afterExpFormat;
    QTextCharFormat operatorFormat;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
    QTextCharFormat dataFormat;
    QTextCharFormat headerFormat;
    QTextCharFormat includeFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat ioFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif //CPPSYNTAX_H

