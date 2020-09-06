
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int, int> ul, pair<int, int> lr, RGBAPixel a)
        : upLeft(ul), lowRight(lr), avg(a), left(NULL), right(NULL) {}

// twoDtree destructor, given.
twoDtree::~twoDtree() {
    clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree &other) {
    copy(other);
}


// twoDtree assignment operator, given.
twoDtree &twoDtree::operator=(const twoDtree &rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

twoDtree::Node *twoDtree::buildTree(stats &s, pair<int, int> ul, pair<int, int> lr, bool vert) {
    Node *r = new Node(ul, lr, s.getAvg(ul, lr));
    bool first = true;
    long minSum = -1;
    if (ul.first == lr.first && ul.second == lr.second) {
        return r;
    }
    if (lr.first == ul.first && lr.second > ul.second) { //single column
        pair<int, int> currUplr;
        pair<int, int> currDownul;
        pair<int, int> finalUplr;
        pair<int, int> finalDownul;
        for (int i = ul.second; i < lr.second; i++) {
            currUplr.first = lr.first;
            currUplr.second = i;
            currDownul.first = ul.first;
            currDownul.second = i + 1;
            long currSum = s.getScore(ul, currUplr) + s.getScore(currDownul, lr);
            if (first || currSum <= minSum) {
                first = false;
                minSum = currSum;
                finalUplr = currUplr;
                finalDownul = currDownul;
            }
        }
        r->left = buildTree(s, ul, finalUplr, false);
        r->right = buildTree(s, finalDownul, lr, false);
    }
    if (lr.second == ul.second && lr.first > ul.first) { //single row
        pair<int, int> currLeftlr;
        pair<int, int> currRightul;
        pair<int, int> finalLeftlr;
        pair<int, int> finalRightul;
        for (int i = ul.first; i < lr.first; i++) {
            currLeftlr.first = i;
            currLeftlr.second = lr.second;
            currRightul.first = i + 1;
            currRightul.second = ul.second;
            long currSum = s.getScore(ul, currLeftlr) + s.getScore(currRightul, lr);
            if (first || currSum <= minSum) {
                first = false;
                minSum = currSum;
                finalLeftlr = currLeftlr;
                finalRightul = currRightul;
            }
        }
        r->left = buildTree(s, ul, finalLeftlr, true);
        r->right = buildTree(s, finalRightul, lr, true);
    }
    if (vert && (lr.first > ul.first) && (lr.second > ul.second)) {    //vertical
        pair<int, int> currLeftlr;
        pair<int, int> currRightul;
        pair<int, int> finalLeftlr;
        pair<int, int> finalRightul;
        for (int i = ul.first; i < lr.first; i++) {
            currLeftlr.first = i;
            currLeftlr.second = lr.second;
            currRightul.first = i + 1;
            currRightul.second = ul.second;
            long currSum = s.getScore(ul, currLeftlr) + s.getScore(currRightul, lr);
            if (first || currSum <= minSum) {
                first = false;
                minSum = currSum;
                finalLeftlr = currLeftlr;
                finalRightul = currRightul;
            }
        }
        //recursive
        r->left = buildTree(s, ul, finalLeftlr, !vert);
        r->right = buildTree(s, finalRightul, lr, !vert);
    } else if (!vert && (lr.first > ul.first) && (lr.second > ul.second)) {   //horizontal
        pair<int, int> currUplr;
        pair<int, int> currDownul;
        pair<int, int> finalUplr;
        pair<int, int> finalDownul;
        for (int i = ul.second; i < lr.second; i++) {
            currUplr.first = lr.first;
            currUplr.second = i;
            currDownul.first = ul.first;
            currDownul.second = i + 1;
            long currSum = s.getScore(ul, currUplr) + s.getScore(currDownul, lr);
            if (first || currSum <= minSum) {
                first = false;
                minSum = currSum;
                finalUplr = currUplr;
                finalDownul = currDownul;
            }
        }
        //recursive
        r->left = buildTree(s, ul, finalUplr, !vert);
        r->right = buildTree(s, finalDownul, lr, !vert);
    }
    return r;
// YOUR CODE HERE!!
}

twoDtree::twoDtree(PNG &imIn) {
    pair<int, int> ul;
    ul.first = 0;
    ul.second = 0;
    pair<int, int> lr;
    lr.first = imIn.width() - 1;
    lr.second = imIn.height() - 1;
    stats myStats(imIn);
    width = imIn.width();
    height = imIn.height();
    root = buildTree(myStats, ul, lr, true);
// YOUR CODE HERE
}

void twoDtree::render(PNG &myImage, Node *node) {
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
            int x1 = node->upLeft.first;
            int y1 = node->upLeft.second;
            int x2 = node->lowRight.first;
            int y2 = node->lowRight.second;
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    *myImage.getPixel(i, j) = node->avg;
                }
            }
        }
        if (node->left != NULL) {
            render(myImage, node->left);
        }
        if (node->right != NULL) {
            render(myImage, node->right);
        }
    }
}


PNG twoDtree::render() {
    PNG myImage(width, height);
    render(myImage, root);
    return myImage;
// YOUR CODE HERE!!

}

void twoDtree::prune(int tol, Node *node) {
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
            return;
        }
        if (prunable(node, tol, node->avg)) {
            clear(node->left);
            clear(node->right);
            node->left = NULL;
            node->right = NULL;
        } else {
            if (node->left != NULL) {
                prune(tol, node->left);
            }
            if (node->right != NULL) {
                prune(tol, node->right);
            }
        }
    }
}

bool twoDtree::prunable(Node *node, long tol, RGBAPixel avgPixel) {
    long r = avgPixel.r - node->avg.r;
    long g = avgPixel.g - node->avg.g;
    long b = avgPixel.b - node->avg.b;
    long diff = r * r + g * g + b * b;
    if (node->left == NULL && node->right == NULL) {
        if (diff <= tol) {
            return true;
        } else {
            return false;
        }
    } else {
        return prunable(node->left, tol, avgPixel) && prunable(node->right, tol, avgPixel);
    }
}

int twoDtree::idealPrune(int leaves) {
    int min = 0;
    int max = 255*255*3;
    while(max - min > 100){
        int mid = (min + max)/2;
        if(pruneSize(mid)<leaves){    //lower
            max = mid;
        } else if(pruneSize(mid)>leaves){   //upper
            min = mid;
        }
    }
    int ret = min;
    while(pruneSize(ret)!=leaves && ret <= max){
        ret++;
    }
    return ret;
// YOUR CODE HERE!!

}

int twoDtree::pruneSize(int tol, Node *node) {
    if (node != NULL) {
        RGBAPixel avg = node->avg;
        if (prunable(node, tol, avg)) {
            return 1;
        } else {
            return pruneSize(tol, node->left) + pruneSize(tol, node->right);
        }
    }
    return 0;
}

int twoDtree::pruneSize(int tol) {
    return pruneSize(tol, root);
// YOUR CODE HERE!!

}

void twoDtree::prune(int tol) {
    prune(tol, root);
// YOUR CODE HERE!!
}

void twoDtree::clear(Node *node) {
    if (node != NULL) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = NULL;
    }
}

void twoDtree::clear() {
    clear(root);
    width = 0;
    height = 0;
    // YOUR CODE HERE!!
}


twoDtree::Node *twoDtree::copy(Node *node) {
    if (node == NULL) {
        return NULL;
    } else {
        Node *newNode = new Node(node->upLeft, node->lowRight, node->avg);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }
}

void twoDtree::copy(const twoDtree &orig) {
    height = orig.height;
    width = orig.width;
    root = copy(orig.root);
// YOUR CODE HERE!!

}



