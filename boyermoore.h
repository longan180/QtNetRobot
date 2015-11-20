#ifndef BOYERMOORE_H
#define BOYERMOORE_H
#include<QtCore>

#define MAX_CHAR 500000
#define SIZE 500000
#define MAX(x, y) (x) > (y) ? (x) : (y)

class BoyerMoore
{
public:
    int *BoyerMoores(char *pattern, int m, char *text, int n);

private:
    void PreBmBc(char *pattern, int m, int bmBc[]);
    void suffix_old(char *pattern, int m, int suff[]);
    void suffix(char *pattern, int m, int suff[]);
    void PreBmGs(char *pattern, int m, int bmGs[]);

};

#endif // BOYERMOORE_H
