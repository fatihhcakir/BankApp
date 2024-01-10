#ifndef INVACCOUNT_H
#define INVACCOUNT_H

#include "account.h"

class InvAccount : public Account
{
public:
    InvAccount(QString accountID);
    InvAccount();
    vector<float> getInvestments ();
    bool setInvestments(QString accountID);
    void createAccount(QString accountID);
    float changeInvests(QString toType,float amount);

private:
    vector<float>invests;
};

#endif // INVACCOUNT_H
