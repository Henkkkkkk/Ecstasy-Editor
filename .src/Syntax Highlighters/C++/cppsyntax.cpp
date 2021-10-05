#include "cppsyntax.h"

CppSyntax::CppSyntax(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    //Opening the settings.json file
    QFile file(QApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content)};
    QJsonObject jo{jsonDoc.object()};


    if(jo["darkTheme"].toBool() == false)
        keywordFormat.setForeground(QColor(82,0,255));
    else
        keywordFormat.setForeground(QColor(86,156,214));
    const QString keywordPatterns[] = {QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"),
        QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"), QStringLiteral("\\bstatic\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bvirtual\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\boperator\\b")};


    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    if(jo["darkTheme"].toBool() == false)
        afterExpFormat.setForeground(QColor(0,16,128));
    else
        afterExpFormat.setForeground(QColor(156,220,254));
    const QString afterExpPatterns[] = {QStringLiteral("\\b::[A-Za-z0-9_]+\\b"), QStringLiteral("\\b\\.[A-Za-z0-9_]+\\b"), QStringLiteral("\\b->[A-Za-z0-9_]+\\b")};
    for(const QString &pattern : afterExpPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = afterExpFormat;
        highlightingRules.append(rule);
    }

    if(jo["darkTheme"].toBool() == false)
        classFormat.setForeground(QColor(38,127,153));
    else
        classFormat.setForeground(QColor(78,201,176));
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+::\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    if(jo["darkTheme"].toBool() == false)
        dataFormat.setForeground(QColor(0,0,255));
    else
        dataFormat.setForeground(QColor(44,122,214));
    const QString dataPatterns[] =  {QStringLiteral("\\bint\\b"), QStringLiteral("\\bdouble\\b"),
                                    QStringLiteral("\\bfloat\\b"),QStringLiteral("\\bchar\\b"),
                                    QStringLiteral("\\bbool\\b"), QStringLiteral("\\bvoid\\b"),
                                    QStringLiteral("\\bstruct\\b"), QStringLiteral("\\blong\\b"),
                                    QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bsigned\\b"),
                                    QStringLiteral("\\bshort\\b"), QStringLiteral("\\bchar\\b"),
                                    QStringLiteral("\\blong\\b"), QStringLiteral("\\bstring\\b")};
    for(const QString &pattern : dataPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = dataFormat;
        highlightingRules.append(rule);
    }

    if(jo["darkTheme"].toBool() == false)
        operatorFormat.setForeground(Qt::black);
    else
        operatorFormat.setForeground(Qt::white);
    const QString operatorPatterns[]{QStringLiteral("\\b\\."), QStringLiteral("\\b->"), QStringLiteral("\\b::")};
    for(const QString &pattern : operatorPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = operatorFormat;
        highlightingRules.append(rule);
    }
    if(jo["darkTheme"].toBool() == false)
        headerFormat.setForeground(QColor(172,76,30));
    else
        headerFormat.setForeground(QColor(206,145,120));
    rule.pattern = QRegularExpression(QStringLiteral("[<\"][^>\"]*[>\"]"));
    rule.format = headerFormat;
    highlightingRules.append(rule);
    if(jo["darkTheme"].toBool() == false)
        includeFormat.setForeground(QColor(175,0,229));
    else
        includeFormat.setForeground(QColor(186,134,192));
    const QString includePatterns[]{QStringLiteral("#pragma\\b"), QStringLiteral("#ifdef\\b"), QStringLiteral("#ifndef\\b"), QStringLiteral("#define\\b"),
                                    QStringLiteral("#undef\\b"), QStringLiteral("#include\\b"), QStringLiteral("#endif"), QStringLiteral("using\\b"),
                                    QStringLiteral("\\breturn\\b"), QStringLiteral("\\bdelete\\b"), QStringLiteral("\\bnew\\b"),
                                    QStringLiteral("\\bif\\b"), QStringLiteral("\\belse if\\b"),QStringLiteral("\\belse\\b"), QStringLiteral("\\bswitch\\b"),
                                    QStringLiteral("\\bcase\\b"), QStringLiteral("\\bdefault\\b")};
    for(const QString &pattern : includePatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = includeFormat;
        highlightingRules.append(rule);
    }
    if(jo["darkTheme"].toBool() == false)
        ioFormat.setForeground(QColor(121,95,38));
    else
        ioFormat.setForeground(QColor(220,220,170));
    const QString ioPatterns[]{QStringLiteral("<<"), QStringLiteral(">>")};
    for(const QString &pattern : ioPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = ioFormat;
        highlightingRules.append(rule);
    }
    if(jo["darkTheme"].toBool() == false)
        numberFormat.setForeground(QColor(9,134,88));
    else
        numberFormat.setForeground(QColor(181,206,164));
    rule.pattern = QRegularExpression(QStringLiteral("[0-9]"));
    rule.format = numberFormat;
    highlightingRules.append(rule);

    if(jo["darkTheme"].toBool() == false)
        quotationFormat.setForeground(QColor(172,76,30));
    else
        quotationFormat.setForeground(QColor(206,145,120));
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    if(jo["darkTheme"].toBool() == false)
        functionFormat.setForeground(QColor(121,94,38));
    else
        functionFormat.setForeground(QColor(220,220,170));
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);
    if(jo["darkTheme"].toBool() == false)
        singleLineCommentFormat.setForeground(QColor(0,128,0));
    else
        singleLineCommentFormat.setForeground(QColor(106,153,85));
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    if(jo["darkTheme"].toBool() == false)
        multiLineCommentFormat.setForeground(QColor(0,128,0));
    else
        multiLineCommentFormat.setForeground(QColor(106,153,85));

    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void CppSyntax::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
            + match.capturedLength();
        }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
