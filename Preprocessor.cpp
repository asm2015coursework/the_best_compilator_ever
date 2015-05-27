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
    resultCode =  preprocessor.deleteComments(resultCode);
    resultCode = preprocessor.applyIncludes(resultCode);
    return resultCode;
}

string Preprocessor::applyIncludes(string code) {
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
                string fileName = code.substr(includePosition + 1, code.find('>', includePosition) - includePosition);
                string fileSource = this->preprocess(specialDirectory + fileName + format);
                resultCode.replace(includePositionBegin + shift, includePosition - includePositionBegin + fileName.length() + 2, fileSource);
                shift += includePosition - includePositionBegin + fileName.length() + 2 + fileSource.length();
            } else if (code[includePosition] == '"'){
                includePosition++;
                string fileName = code.substr(includePosition, code.find('"', includePosition) - includePosition);
                string fileSource = this->preprocess(fileName);
                resultCode.replace(includePositionBegin + shift, includePosition - includePositionBegin + fileName.length() + 2, fileSource);
                shift += includePosition - includePositionBegin + fileName.length() + 2 + fileSource.length();
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
