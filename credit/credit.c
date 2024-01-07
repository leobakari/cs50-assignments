#include <cs50.h>
#include <stdio.h>

long long get_user_creditcard(void);
int get_credit_len(long long creditNum);
int get_check_sum(long long number);
bool validate_check_sum(int checkSum);
int get_issuer_num(long long creditNum);
int get_issuer_name(bool validStatus, int issuerNum, int creditLen);

int main(void)
{
    long long creditNum = get_user_creditcard();
    int creditLen = get_credit_len(creditNum);
    int checkSum = get_check_sum(creditNum);
    bool validStatus = validate_check_sum(checkSum);
    int issuerNum = get_issuer_num(creditNum);
    get_issuer_name(validStatus, issuerNum, creditLen);
}

// Gets Creditcard number from user - User cant input string as get_long only accepts positive numeric values
long long get_user_creditcard(void)
{
    long long userCreditcard = get_long("Number: ");
    return userCreditcard;
};

// Gets length of the credit card - used in order to check validity of card number
int get_credit_len(long long creditNum)
{
    int creditLen = 0;
    while (creditNum > 0)
    {
        creditNum = creditNum / 10;
        creditLen++;
    }
    return creditLen;
}

// Calculates the checksum - takes a creditcard as input and returns the checksum as int
int get_check_sum(long long number)
{
    int sumDoubled = 0;
    int sumAdded;
    while (number > 0)
    {
        int lastDigit = number % 10;
        sumAdded = sumAdded + lastDigit;
        number = number / 10;
        lastDigit = number % 10;
        int lastDigitDoubled = lastDigit * 2;
        if (lastDigitDoubled >= 10)
        {
            sumDoubled = sumDoubled + lastDigitDoubled % 10;
            sumDoubled = sumDoubled + lastDigitDoubled / 10;
        }
        else
        {
            sumDoubled = sumDoubled + lastDigit * 2;
        }
        number = number / 10;
    }
    int checkSum = sumDoubled + sumAdded;
    return checkSum;
}

// checks if the checksum points towards a valid card number - returns a boolean statement
bool validate_check_sum(int checkSum)
{
    int checkDigit = checkSum % 10;
    if (checkDigit == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// returns the first two digits of a number
int get_issuer_num(long long creditNum)
{
    while (creditNum >= 100)
    {
        creditNum = creditNum / 10;
    }
    return creditNum;
}
// identifies the issuer name and prints it to the console. If checksum doesnt fit or issuer num unknown, invalid is printed instead
int get_issuer_name(bool validStatus, int issuerNum, int creditLen)
{
    int firstDigit = issuerNum / 10;

    // first digits to identify credit cards.
    int visaIdentifier = 4;
    int masterIdentifierMax = 55;
    int masterIdentifierMin = 51;
    int amexIdentifierA = 34;
    int amexIdentifierB = 37;

    // Length parameters for the card number.
    int visaLenMax = 16;
    int visaLenMin = 13;
    int mastercardLen = 16;
    int amexLen = 15;

    if (validStatus == true)
    {
        if (firstDigit == visaIdentifier && creditLen >= visaLenMin && creditLen <= visaLenMax)
        {
            printf("VISA\n");
        }
        else if (issuerNum <= masterIdentifierMax && issuerNum >= masterIdentifierMin && creditLen == mastercardLen)
        {
            printf("MASTERCARD\n");
        }
        else if (issuerNum == amexIdentifierA || issuerNum == amexIdentifierB)
        {
            if (creditLen == amexLen)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}