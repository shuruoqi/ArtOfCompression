
#include "stats.h"

stats::stats(PNG & im){

// YOUR CODE HERE!!
    int x = im.width();
    int y = im.height();
    vector<long> col0R;
    vector<long> col0G;
    vector<long> col0B;
    vector<long> col0R2;
    vector<long> col0G2;
    vector<long> col0B2;
    col0R.push_back(im.getPixel(0,0)->r);
    col0G.push_back(im.getPixel(0,0)->g);
    col0B.push_back(im.getPixel(0,0)->b);
    col0R2.push_back(im.getPixel(0,0)->r * im.getPixel(0,0)->r);
    col0G2.push_back(im.getPixel(0,0)->g * im.getPixel(0,0)->g);
    col0B2.push_back(im.getPixel(0,0)->b * im.getPixel(0,0)->b);
//    printf("1");
    for(int j = 1; j < y; j++){
//        printf("2");
        long currRsum = col0R[j -1] + im.getPixel(0,j)->r;
        long currGsum = col0G[j -1] + im.getPixel(0,j)->g;
        long currBsum = col0B[j -1] + im.getPixel(0,j)->b;
        long currsqRsum = col0R2[j -1] + (im.getPixel(0,j)->r)*(im.getPixel(0,j)->r);
        long currsqGsum = col0G2[j -1] + (im.getPixel(0,j)->g)*(im.getPixel(0,j)->g);
        long currsqBsum = col0B2[j -1] + (im.getPixel(0,j)->b)*(im.getPixel(0,j)->b);
        col0R.push_back(currRsum);
        col0G.push_back(currGsum);
        col0B.push_back(currBsum);
        col0R2.push_back(currsqRsum);
        col0G2.push_back(currsqGsum);
        col0B2.push_back(currsqBsum);
    }
    sumRed.push_back(col0R);
    sumsqRed.push_back(col0R2);
    sumGreen.push_back(col0G);
    sumsqGreen.push_back(col0G2);
    sumBlue.push_back(col0B);
    sumsqBlue.push_back(col0B2);
    
    for(int i = 1; i < x;i ++){
//        printf("3");
        vector<long> colXR;
        vector<long> colXG;
        vector<long> colXB;
        vector<long> colXR2;
        vector<long> colXG2;
        vector<long> colXB2;
        long topSumR = im.getPixel(i,0)->r + sumRed[i-1][0];
        long topSumG = im.getPixel(i,0)->g + sumGreen[i-1][0];
        long topSumB = im.getPixel(i,0)->b + sumBlue[i-1][0];
        long currsqRsum = (im.getPixel(i,0)->r)*(im.getPixel(i,0)->r) + sumsqRed[i-1][0];
        long currsqGsum = (im.getPixel(i,0)->g)*(im.getPixel(i,0)->g) + sumsqGreen[i-1][0];
        long currsqBsum = (im.getPixel(i,0)->b)*(im.getPixel(i,0)->b) + sumsqBlue[i-1][0];
        colXR.push_back(topSumR);
        colXG.push_back(topSumG);
        colXB.push_back(topSumB);
        colXR2.push_back(currsqRsum);
        colXG2.push_back(currsqGsum);
        colXB2.push_back(currsqBsum);
//        sumRed.push_back(colXR);
//        sumGreen.push_back(colXG);
//        sumBlue.push_back(colXB);
//        sumsqRed.push_back(colXR2);
//        sumsqGreen.push_back(colXG2);
//        sumsqBlue.push_back(colXB2);
        for(int j = 1; j < y; j++){
//            printf("4");
//            printf("%ld\n",im.getPixel(i,j)->r);
//            printf("%ld\n",sumRed[i][j-1]);
//            printf("%ld\n",sumRed[i-1][j]);
//            printf("%ld\n",sumRed[i-1][j-1]);
            long currRsum = im.getPixel(i,j)->r + colXR[j-1] + sumRed[i-1][j] - sumRed[i-1][j-1];
//            printf("5");
            long currGsum = im.getPixel(i,j)->g + colXG[j-1] + sumGreen[i-1][j] - sumGreen[i-1][j-1];
            long currBsum = im.getPixel(i,j)->b + colXB[j-1] + sumBlue[i-1][j] - sumBlue[i-1][j-1];
//            printf("6");
            long currsqRsum = (im.getPixel(i,j)->r)*(im.getPixel(i,j)->r) + colXR2[j-1] + sumsqRed[i-1][j] - sumsqRed[i-1][j-1];
            long currsqGsum = (im.getPixel(i,j)->g)*(im.getPixel(i,j)->g) + colXG2[j-1] + sumsqGreen[i-1][j] - sumsqGreen[i-1][j-1];
            long currsqBsum = (im.getPixel(i,j)->b)*(im.getPixel(i,j)->b) + colXB2[j-1] + sumsqBlue[i-1][j] - sumsqBlue[i-1][j-1];
            colXR.push_back(currRsum);
            colXG.push_back(currGsum);
            colXB.push_back(currBsum);
//            long currsqRsum
            colXR2.push_back(currsqRsum);
            colXG2.push_back(currsqGsum);
            colXB2.push_back(currsqBsum);
        }
        sumRed.push_back(colXR);
        sumGreen.push_back(colXG);
        sumBlue.push_back(colXB);
        sumsqRed.push_back(colXR2);
        sumsqGreen.push_back(colXG2);
        sumsqBlue.push_back(colXB2);
    }
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
    int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;
    if(ulx == 0 && uly != 0){ //first column
        switch (channel) {
            case 'r':
                return sumRed[lrx][lry] -sumRed[lrx][uly-1];
                break;
            case 'g':
                return sumGreen[lrx][lry] -sumGreen[lrx][uly-1];
                break;
            default:
                return sumBlue[lrx][lry] -sumBlue[lrx][uly-1];
                break;
        }
    } else if (ulx != 0 && uly == 0){  //first row
        switch (channel) {
            case 'r':
                return sumRed[lrx][lry] - sumRed[ulx-1][lry];
                break;
            case 'g':
                return sumGreen[lrx][lry] - sumGreen[ulx-1][lry];
                break;
            default:
                return sumBlue[lrx][lry] - sumBlue[ulx-1][lry];
                break;
        }
    } else if (ulx == 0 && uly == 0){
        switch (channel) {
            case 'r':
                return sumRed[lrx][lry];
                break;
            case 'g':
                return sumGreen[lrx][lry];
                break;
            default:
                return sumBlue[lrx][lry];
                break;
        }
    } else {
        switch (channel) {
            case 'r':
                return sumRed[lrx][lry] -sumRed[ulx-1][lry] -sumRed[lrx][uly-1] + sumRed[ulx-1][uly-1];
                break;
            case 'g':
                return sumGreen[lrx][lry] -sumGreen[ulx-1][lry] -sumGreen[lrx][uly-1] + sumGreen[ulx-1][uly-1];
                break;
            default:
                return sumBlue[lrx][lry] -sumBlue[ulx-1][lry] -sumBlue[lrx][uly-1] + sumBlue[ulx-1][uly-1];
                break;
        }
    }
// YOUR CODE HERE!!

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
    int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;
    if(ulx == 0 && uly != 0){ //first column
        switch (channel) {
            case 'r':
                return sumsqRed[lrx][lry] -sumsqRed[lrx][uly-1];
                break;
            case 'g':
                return sumsqGreen[lrx][lry] -sumsqGreen[lrx][uly-1];
                break;
            default:
                return sumsqBlue[lrx][lry] -sumsqBlue[lrx][uly-1];
                break;
        }
    } else if (ulx != 0 && uly == 0){  //first row
        switch (channel) {
            case 'r':
                return sumsqRed[lrx][lry] - sumsqRed[ulx-1][lry];
                break;
            case 'g':
                return sumsqGreen[lrx][lry] - sumsqGreen[ulx-1][lry];
                break;
            default:
                return sumsqBlue[lrx][lry] - sumsqBlue[ulx-1][lry];
                break;
        }
    } else if (ulx == 0 && uly == 0){
        switch (channel) {
            case 'r':
                return sumsqRed[lrx][lry];
                break;
            case 'g':
                return sumsqGreen[lrx][lry];
                break;
            default:
                return sumsqBlue[lrx][lry];
                break;
        }
    } else {
        switch (channel) {
            case 'r':
                return sumsqRed[lrx][lry] -sumsqRed[ulx-1][lry] -sumsqRed[lrx][uly-1] + sumsqRed[ulx-1][uly-1];
                break;
            case 'g':
                return sumsqGreen[lrx][lry] -sumsqGreen[ulx-1][lry] -sumsqGreen[lrx][uly-1] + sumsqGreen[ulx-1][uly-1];
                break;
            default:
                return sumsqBlue[lrx][lry] -sumsqBlue[ulx-1][lry] -sumsqBlue[lrx][uly-1] + sumsqBlue[ulx-1][uly-1];
                break;
        }
    }

// YOUR CODE HERE!!

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;
    return (long)(lrx - ulx + 1)*(lry - uly + 1);

// YOUR CODE HERE!!

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){
    double area = rectArea(ul,lr);
    double devR = getSumSq('r',ul,lr) - getSum('r',ul,lr)*getSum('r',ul,lr)/area;
    double devG = getSumSq('g',ul,lr) - getSum('g',ul,lr)*getSum('g',ul,lr)/area;
    double devB = getSumSq('b',ul,lr) - getSum('b',ul,lr)*getSum('b',ul,lr)/area;
    
    return (long)devR + devB + devG;

// YOUR CODE HERE!!

}

RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
    double area = rectArea(ul,lr);
    double Rbar = getSum('r',ul,lr)/area;
    double Gbar = getSum('g',ul,lr)/area;
    double Bbar = getSum('b',ul,lr)/area;
    return RGBAPixel(Rbar,Gbar,Bbar);

// YOUR CODE HERE!!

}
