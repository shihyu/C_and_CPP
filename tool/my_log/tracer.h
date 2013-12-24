#ifndef TTRACER_H
#define TTRACER_H

#include <iostream>
using namespace std;
#define GLOGENTRY(args...) __CallLog__ __call_log__(LOG_TAG, __FILE__, __LINE__, __PRETTY_FUNCTION__);

// 10-15 09:04:27.020   685   814 I wmp_impl: TID:814 .../PhoneWindowManager.cpp:6274:    
class __CallLog__ {
private:
    const char* mLogtag;
    const char* mFile;
    int mLine;
    const char* mFunc;
    long long mEnterTime;
public:
    inline __CallLog__(const char* __logtag, const char* __file, int __line, const char* __func)
        : mLogtag(__logtag)
        , mFile(__file)
        , mLine(__line)
        , mFunc(__func) {
        cout << "Enter\t" << mLogtag << "\t" << mFile << ":" << mLine << ":\t" << mFunc << endl;
    }

    inline void timeDiff(int diffLine) {
    }

    inline ~__CallLog__() {
        cout << "Leave\t" << mLogtag << "\t" << mFile << ":" << mLine << ":\t" << mFunc << endl;
    }
};
#endif
