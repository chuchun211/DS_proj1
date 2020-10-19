#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Block{
public:
    Block(string shape) {
        name = shape;
        arr = new int*[4];
        for(int i=0; i<4; i++) {
            arr[i] = new int[4];
            fill(arr[i], arr[i]+4, 0);
        }
        if(shape == "T1") {
            height = 2;
            width = 3;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[2][2] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "T2") {
            height = 3;
            width = 2;
            arr[1][1] = 1;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "T3") {
            height = 2;
            width = 3;
            arr[2][1] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
            arr[3][2] = 1;
        }
        else if(shape == "T4") {
            height = 3;
            width = 2;
            arr[1][0] = 1;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][0] = 1;
        }
        else if(shape == "L1") {
            height = 3;
            width = 2;
            arr[1][0] = 1;
            arr[2][0] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "L2") {
            height = 2;
            width = 3;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[2][2] = 1;
            arr[3][0] = 1;
        }
        else if(shape == "L3") {
            height = 3;
            width = 2;
            arr[1][0] = 1;
            arr[1][1] = 1;
            arr[2][1] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "L4") {
            height = 2;
            width = 3;
            arr[2][2] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
            arr[3][2] = 1;
        }
        else if(shape == "J1") {
            height = 3;
            width = 2;
            arr[1][1] = 1;
            arr[2][1] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "J2") {
            height = 2;
            width = 3;
            arr[2][0] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
            arr[3][2] = 1;
        }
        else if(shape == "J3") {
            height = 3;
            width = 2;
            arr[1][0] = 1;
            arr[1][1] = 1;
            arr[2][0] = 1;
            arr[3][0] = 1;
        }
        else if(shape == "J4") {
            height = 2;
            width = 3;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[2][2] = 1;
            arr[3][2] = 1;
        }
        else if(shape == "S1") {
            height = 2;
            width = 3;
            arr[2][1] = 1;
            arr[2][2] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "S2") {
            height = 3;
            width = 2;
            arr[1][0] = 1;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][1] = 1;
        }
        else if(shape == "Z1") {
            height = 2;
            width = 3;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][1] = 1;
            arr[3][2] = 1;
        }
        else if(shape == "Z2") {
            height = 3;
            width = 2;
            arr[1][1] = 1;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][0] = 1;
        }
        else if(shape == "I1") {
            height = 4;
            width = 1;
            arr[0][0] = 1;
            arr[1][0] = 1;
            arr[2][0] = 1;
            arr[3][0] = 1;
        }
        else if(shape == "I2") {
            height = 1;
            width = 4;
            arr[3][0] = 1;
            arr[3][1] = 1;
            arr[3][2] = 1;
            arr[3][3] = 1;
        }
        else if(shape == "O") {
            height = 2;
            width = 2;
            arr[2][0] = 1;
            arr[2][1] = 1;
            arr[3][0] = 1;
            arr[3][1] = 1;
        }
    }
    int occupied(int r, int c) {return arr[r][c];}
    friend class Matrix;
private:
    int **arr;
    int height, width;
    string name;
};

class Matrix {
public:
    Matrix(int r, int c, int val) {
        arr = new int*[r];
        for(int i=0; i<r; i++) {
            arr[i] = new int[c];
            fill(arr[i], arr[i]+c, val);
        }
        row = r;
        col = c;
    }
    ~Matrix() {
        for(int i=0; i<row; i++)
            delete [] arr[i];
        delete [] arr;
    }
    bool movingBlock(Block*, int, int);
    string encode_output() {
        int r = row;
        int c = col-1;
        int i, j;
        stringstream ss;
        for(i=0; i<r; i++) {
            for(j=0; j<c; j++)
                ss << arr[i][j] << " ";
            ss << arr[i][j] << endl;
        }
        return ss.str();
    }
    friend ostream& operator<<(ostream &output, const Matrix &m);
private:
    int row, col;
    int **arr;
};

ostream& operator<<(ostream &output, const Matrix &m) {
    int r = m.row;
    int c = m.col-1;
    int i, j;
    for(i=0; i<r; i++) {
        for(j=0; j<c; j++)
            cout << m.arr[i][j] << " ";
        cout << m.arr[i][j] << endl;
    }
    return output;
}

bool Matrix::movingBlock(Block* shape, int from, int mov)
{
    int h = shape->height;
    int w = shape->width;
    int pos_r = 0;
    int pos_c = from;
    // 1st fall down
    int tmp;
    bool valid = 1;
    bool ground = 0;
    for(int i=0; i<row; i++) {
        tmp = (i < 3) ? (3-i) : 0;
        for(int j=pos_c; j<pos_c+w; j++) {
            for(int k=3; k>=tmp; k--) {
                if( arr[i-3+k][j] && shape->arr[k][j-pos_c] ) {
                    ground = 1;
                    if( pos_r-h < 0 ) {
                        valid = 0;
                        return valid;
                    }
                    pos_r--;
                    break;
                }
            }
            if(ground) break;
        }
        if((pos_r == row-1) || ground) break;
        else pos_r++;
    }
    // shift
    if( (from + mov < 0) || (from + mov + w > col) ) {
        valid = 0;
        return valid;
    }
    else {
        for(int i=pos_c+1; i<pos_c+mov; i++) {
            for(int j=pos_r; j>pos_r-4; j--) {
                for(int k=0; k<4; k++) {
                    if( arr[j][i] && shape->arr[j][k] ) {
                        valid = 0;
                        return valid;
                    }
                }
            }
        }
        for(int i=pos_c-1; i>pos_c+mov; i--) {
            for(int j=pos_r; j>pos_r-4; j--) {
                for(int k=0; k<4; k++) {
                    if( arr[j][i] && shape->arr[j][k] ) {
                        valid = 0;
                        return valid;
                    }
                }
            }
        }
    }
    pos_c += mov;
    // 2nd fall down
    ground = 0;
    for(int i=pos_r; i<row; i++) {
        tmp = (i < 3) ? (3-i) : 0;
        for(int j=pos_c; j<pos_c+w; j++) {
            for(int k=3; k>=tmp; k--) {
                if( arr[i-3+k][j] && shape->arr[k][j-pos_c] ) {
                    ground = 1;
                    if( pos_r-h <= 0 ) {
                        valid = 0;
                        return valid;
                    }
                    pos_r--;
                    break;
                }
            }
            if(ground) break;
        }
        if((pos_r == row-1) || ground) break;
        else pos_r++;
    }
    // draw the game board
    for(int i=3; i>3-h; i--) {
        for(int j=0; j<w; j++) {
            if( shape->arr[i][j] ) {
                arr[pos_r-3+i][pos_c+j] = 1;
            }
        }
    }
    //cout << *this << endl;
    // eliminate rows or not
    bool full[4];
    fill(full, full+4, 1);
    for(int i=pos_r; i>pos_r-4; i--) {
        for(int j=0; j<col; j++) {
            if( arr[i][j] == 0 ) {
                full[pos_r-i] = 0;
                break;
            }
        }
    }
    // eliminating
    int eliminated = 0;
    for(int i=0; i<4; i++) {
        if( full[i] ) {
            int tmp = pos_r-i+eliminated;
            int* p = arr[tmp];
            for(int j=tmp; j>0; j--) {
                arr[j] = arr[j-1];
            }
            arr[0] = p;
            fill(arr[0], arr[0]+col, 0);
            eliminated++;
        }
    }

    return valid;
}

int main(int, char** argv)
{
    ifstream fin;
    fin.open(argv[1], ifstream::in);
    ofstream log("108062104_proj1.final");
    string data;
    if(!fin)
        cout << "Fail to open " << argv[1] << endl;
    else {
        int row, col;
        fin >> row >> col;
        Matrix game = Matrix(row, col, 0);
        string shape;
        int from, mov;
        while(fin >> shape) {
            if( shape == "End" ) break;
            fin >> from >> mov;
            Block tmp(shape);
            bool valid = game.movingBlock(&tmp, from-1, mov);
            if( !valid ) {
                data = "invalid";
                log << data;
                //cout << data;
                break;
            }
            data = game.encode_output();
        }
        //cout << data;
        log << data;
    }
    log.close();

    return 0;
}
