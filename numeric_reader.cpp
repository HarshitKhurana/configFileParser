
#include<iostream>
#include<climits>
#include<bits/stdc++.h>

using namespace std;

/*
 * This class simply reads the file containing integers 1 line at a time
 */
class Reader {
    string filename;
    string line;
    std::ifstream infile;
public:
    class iterator;
    friend class iterator;  // so that iterator class can access private member of Reader class.
    Reader(string fname) : filename(fname) {}

    iterator begin() {
        if (infile)
            infile.close();
        infile.open(filename.c_str(), std::ifstream::in);
        return iterator (*this, false, true);
    }
    iterator end() {
        return iterator(*this, true);
    }

    class iterator {
        bool _eof;
        Reader &rdr;
        public:
        iterator(Reader &r, bool end_of_file) : rdr(r) , _eof(end_of_file) {
        }
        iterator(Reader &r, bool end_of_file, bool) : rdr(r) , _eof(end_of_file) {
            ++ *this;
        }

        iterator& operator++() {
            // access infile object and read line, if EOF return nullptr
            std::string curr_line;
            while (true)  {
                getline(rdr.infile, curr_line);
                if (rdr.infile.eof()) {
                    cout << "[iterator] EOF file reached " << endl;
                    this->_eof = true;  // reached EOF
                }
                //cout << "[iterator ++] line read: " << curr_line << endl;
                // validate line is correct
                break;
            }
            rdr.line = curr_line;
            return *this;
        }   

        // de-reference operator
        int operator*(){ 
            //cout << "[iterator*] : " << rdr.line << endl;
            int x = std::stoi(rdr.line);
            return x;
        }

        bool operator != (const iterator& rhs) const {
            return this->_eof != rhs._eof;
        }
    };

};

int main(int argc, char* argv[]) {

    string filename(argv[1]);
    Reader r(filename);
    Reader::iterator bg = r.begin();
    Reader::iterator ed = r.end();
    for (bg; bg != ed; ++bg) {
        int x = *bg;
        cout << x << endl;
    }
}
