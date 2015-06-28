#include "Preprocessor.h"

Preprocessor::Preprocessor() {
    this->includeDirectory = "";
}

Preprocessor::Preprocessor(string includeDirectory) {
    this->includeDirectory = includeDirectory;
}

int Preprocessor::setIncludeDirectory(string includeDirectory) {
    this->includeDirectory = includeDirectory;
    return 0;
}

string Preprocessor::preprocess(string file_name) {
    string resultCode = fileToString(file_name);
    Preprocessor preprocessor = Preprocessor();
    resultCode = preprocessor.deleteComments(resultCode);
    resultCode = preprocessor.applyDefines(resultCode);  
    resultCode = preprocessor.applyIncludes(resultCode, "");
    return resultCode;
}

string Preprocessor::preprocess(string file_name, string filePath) {
    string resultCode = fileToString(file_name);
    Preprocessor preprocessor = Preprocessor();
    resultCode =  preprocessor.deleteComments(resultCode);
    resultCode = preprocessor.applyDefines(resultCode);
    resultCode = preprocessor.applyIncludes(resultCode, filePath);
    return resultCode;
}

string Preprocessor::applyDefines(string code) {
    const string definePointer = "#define";
    string resultCode(code);
    string::size_type definePositionBegin = code.find(definePointer, 0);
    string::size_type definePosition, shift = 0;
    while (definePositionBegin != code.npos) {
        definePosition = definePositionBegin + definePointer.length();
        while (code[definePosition] == ' ') {
            definePosition++;
        }
        if (!this->inBrackets(code, definePositionBegin)) {
            string::size_type constantEndPosition = code.find(' ', definePosition);
            string constantValue = code.substr(definePosition, constantEndPosition - definePosition);
            string::size_type macroEndPosition = code.find(' ', constantEndPosition + 1);
            string macroValue = code.substr(constantEndPosintion + 1, macroEndPosition - constantEndPosition - 1);
            string::size_type macroPosition = resultCode.find(macroValue);
            while (macroPosition != resultCode.npos) {
                resultCode.replace(macroValue, constantValue);
                macroPosition = resultCode.find(macroValue, macroPosition);
            }
        }
        definePositionBegin = code.find(definePointer, definePosition);
    }
    return resultCode;
}


string Preprocessor::applyIncludes(string code, string filePath) {
    const string includePointer = "#include";
    const string specialDirectory = this->includeDirectory;
    const string format = ".cmm";
    string resultCode(code);
    string::size_type includePositionBegin = code.find(includePointer, 0);
    string::size_type includePosition, shift = 0;
    while (includePositionBegin != code.npos) {
        includePosition = includePositionBegin + includePointer.length();
        while (code[includePosition] == ' ') {
            includePosition++;
        }
        if (!this->inBrackets(code, includePositionBegin)) {
            if (code[includePosition] == '<') {
                string::size_type fileNameEndPosition = code.find('>', includePosition);
                string fileName = code.substr(includePosition + 1, fileNameEndPosition - includePosition);
                string fileSource = this->preprocess(specialDirectory + fileName + format);
                string::size_type replaceSizeCount = includePosition - includePositionBegin + fileName.length() + 2;
                resultCode.replace(includePositionBegin + shift, replaceSizeCount, fileSource);
                shift += replaceSizeCount + fileSource.length();
            } else if (code[includePosition] == '"'){
                includePosition++;
                string::size_type fileNameEndPosition = code.find('>', includePosition);
                string fileName = code.substr(includePosition, fileNameEndPosition - includePosition);
                string fileSource = this->preprocess(filePath + fileName, filePath + fileName.substr(0, fileName.find_last_of('/')));
                string::size_type replaceSizeCount = includePosition - includePositionBegin + fileName.length() + 2;
                resultCode.replace(includePositionBegin + shift, replaceSizeCount, fileSource);
                shift += replaceSizeCount + fileSource.length();
            }
        }
        includePositionBegin = code.find(includePointer, includePosition);
    }
    return resultCode;
}

bool Preprocessor::inBrackets(string code, int position) {
    int bracketBalance = 0, lineBeginnig = position;
    std::vector<int> bracketPosition;
    while (lineBeginnig > -1) {
        if (code[lineBeginnig] == '"') {
            bracketPosition.push_back(lineBeginnig);
        }
        if (code[lineBeginnig] == '\n') {
            break;
        }
        lineBeginnig--;
    }
    string block = "'";
    block += '"';
    block += "'";
    int blockPosition = code.find(block, lineBeginnig);
    for (string::size_type i = 0; i < bracketPosition.size(); i++) {
        if (blockPosition > bracketPosition[i]) {
            bracketBalance = 1 - bracketBalance;
        } else if (bracketBalance == 1) {
            bracketBalance = 1 - bracketBalance;
            blockPosition = code.find(block, lineBeginnig);
        }
    }
    return (bracketBalance == 1);
}

string Preprocessor::deleteComments(string code) {
    const string lineCommentPointer = "//";
    const string commentBeginPointer = "/*";
    const string commentEndPointer = "*/";
    string resultCode (code);
    string::size_type commentPosition = resultCode.find(lineCommentPointer, 0);
    string::size_type commentEndPosition;
    while (commentPosition != string::npos) {
        commentEndPosition = resultCode.find('\n', commentPosition);
        if (commentEndPosition == resultCode.npos) {
            commentEndPosition = resultCode.length();
        }
        if (!inBrackets(resultCode, commentPosition)) {
            resultCode.replace(commentPosition, commentEndPosition - commentPosition, "");
        } else {
            commentPosition += lineCommentPointer.length();
        }
        commentPosition = resultCode.find(lineCommentPointer, commentPosition);
    }
    commentPosition = resultCode.find(commentBeginPointer, 0);

    while (commentPosition != string::npos) {
        commentEndPosition = resultCode.find(commentEndPointer, commentPosition);
        if (commentEndPosition == resultCode.npos) {
            commentEndPosition = resultCode.length();
        } else {
            commentEndPosition += commentEndPointer.length();
        }
        if (!inBrackets(resultCode, commentPosition)) {
            resultCode.replace(commentPosition, commentEndPosition - commentPosition, "");
        } else {
            commentPosition += commentBeginPointer.length();
        }
        commentPosition = resultCode.find(commentBeginPointer, commentPosition);
    }

    return resultCode;
}
