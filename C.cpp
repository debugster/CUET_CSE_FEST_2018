#include <bits/stdc++.h>

using namespace std;

/* something starts */
/* something ends */

/* typedef starts */

typedef long long ll;
typedef unsigned long long ull;

/* typedef ends */

/* macro starts */

#define PI acos(-1.0)

/* macro ends */

bool LeapYears[2200];
const ull SECONDS_IN_A_MINUTE = 60;
const ull SECONDS_IN_AN_HOUR = 3600;
const ull SECONDS_IN_A_DAY = 86400;
ull SECONDS_IN_28_DAY_MONTH;
ull SECONDS_IN_29_DAY_MONTH;
ull SECONDS_IN_30_DAY_MONTH;
ull SECONDS_IN_31_DAY_MONTH;
ull SECONDS_IN_NON_LEAP_YEAR;
ull SECONDS_IN_LEAP_YEAR;
int daysNonLeap[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int daysLeap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int year)
{
    if (year % 400 == 0 || (year & 4 == 0 && year % 100 != 0)) {
        return true;
    }
    return false;
}

int getMonth(string m)
{
    if (m == "Jan") return 1;
    else if (m == "Feb") return 2;
    else if (m == "Mar") return 3;
    else if (m == "Apr") return 4;
    else if (m == "May") return 5;
    else if (m == "Jun") return 6;
    else if (m == "Jul") return 7;
    else if (m == "Aug") return 8;
    else if (m == "Sep") return 9;
    else if (m == "Oct") return 10;
    else if (m == "Nov") return 11;
    else if (m == "Dec") return 12;
}

int getAMPM(string AMPM)
{
    if (AMPM == "AM") return 1;
    return 2;
}

ull countSecondsFrom1899(int date, int mon, int year, int hh, int mm, int ss, int AMPM)
{
    ull seconds = 0;
    int i;

    for (i = 1899; i < year; i++) {
        if (LeapYears[i]) {
            seconds += SECONDS_IN_LEAP_YEAR;
        }
        else {
            seconds += SECONDS_IN_NON_LEAP_YEAR;
        }
    }

    int passedMonth = mon - 1;
    if (LeapYears[year]) {
        for (i = 1; i <= passedMonth; i++) {
            seconds += (daysLeap[i] * SECONDS_IN_A_DAY);
        }
    }
    else {
        for (i = 1; i <= passedMonth; i++) {
            seconds += (daysNonLeap[i] * SECONDS_IN_A_DAY);
        }
    }

    int passedDay = date - 1;
    for (i = 1; i <= passedDay; i++) {
        seconds += SECONDS_IN_A_DAY;
    }

    seconds += ((hh * SECONDS_IN_AN_HOUR) + (mm * SECONDS_IN_A_MINUTE) + ss);
    if (AMPM == 2) {
        seconds += (12 * SECONDS_IN_AN_HOUR);
    }

    return seconds;
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int y;
    for (y = 1899; y <= 2100; y++) {
        LeapYears[y] = isLeap(y);
    }

    int test, t, i;
    int sDate, fDate, sMon, fMon, sYear, fYear, sHH, fHH, sMM, fMM, sSS, fSS, sAP, fAP;
    string _sMon, _fMon, _sAP, _fAP;
    string temp; /// for "at"
    char ch; /// for ':'

    cin >> test;
    for (t = 1; t <= test; t++) {
        cin >> sDate >> _sMon >> sYear >> temp >> sHH >> ch >> sMM >> ch >> sSS >> _sAP;
        cin >> fDate >> _fMon >> fYear >> temp >> fHH >> ch >> fMM >> ch >> fSS >> _fAP;

        sMon = getMonth(_sMon);
        fMon = getMonth(_fMon);

        sAP = getAMPM(_sAP);
        fAP = getAMPM(_fAP);

        SECONDS_IN_28_DAY_MONTH = SECONDS_IN_A_DAY * 28;
        SECONDS_IN_29_DAY_MONTH = SECONDS_IN_A_DAY * 29;
        SECONDS_IN_30_DAY_MONTH = SECONDS_IN_A_DAY * 30;
        SECONDS_IN_31_DAY_MONTH = SECONDS_IN_A_DAY * 31;
        SECONDS_IN_LEAP_YEAR = 0;
        for (i = 1; i <= 12; i++) {
            SECONDS_IN_LEAP_YEAR += (SECONDS_IN_A_DAY * daysLeap[i]);
        }
        SECONDS_IN_NON_LEAP_YEAR = 0;
        for (i = 1; i <= 12; i++) {
            SECONDS_IN_NON_LEAP_YEAR += (SECONDS_IN_A_DAY * daysNonLeap[i]);
        }

        ull countForStart = countSecondsFrom1899(sDate, sMon, sYear, sHH, sMM, sSS, sAP);
        ull countForFinish = countSecondsFrom1899(fDate, fMon, fYear, fHH, fMM, fSS, fAP);
        ull ans = countForFinish - countForStart;

        //cout << ans << endl;

        ull ansDay = ans / SECONDS_IN_A_DAY;
        ans %= SECONDS_IN_A_DAY;

        ull ansHour = ans / SECONDS_IN_AN_HOUR;
        ans %= SECONDS_IN_AN_HOUR;

        ull ansMinute = ans / SECONDS_IN_A_MINUTE;
        ans %= SECONDS_IN_A_MINUTE;

        cout << "Case " << t << ": ";
        if (ansDay != 0) {
            cout << ansDay << "d ";
        }
        if (ansHour != 0) {
            cout << ansHour << "h ";
        }
        if (ansMinute != 0) {
            cout << ansMinute << "m ";
        }
        cout << ans << "s\n";

    }

    return 0;
}

