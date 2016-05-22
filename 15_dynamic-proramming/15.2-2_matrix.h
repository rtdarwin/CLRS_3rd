#include<iostream>
#include<utility>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

class Matrix {
  public:
	// Constructors, Assignment operator, Destructor
	Matrix();
	Matrix( const Matrix& r );
	Matrix( Matrix&& r );
	void operator= ( const Matrix& r );
	~Matrix();
	
	// Acess
	int rows() const { return _row; };
	int columns() const { return _col; };

	// Modifier
	
	// Operators
	int operator() ( int i, int j ) const;
	int& operator() ( int i, int j );
	friend Matrix operator* ( const Matrix& l, const Matrix& r );
	friend istream& operator>> ( istream& is, Matrix& m );
	friend ostream& operator<< ( ostream& os, Matrix& m );
  private:
	int _row;
	int _col;
	int **_data;
};


// ----------------------------- IMPLEMENTATION --------------------------------
Matrix::Matrix()
	: _row(0), _col(0), _data(NULL)
{}


Matrix::Matrix( const Matrix& r )
	: _row( r._row ), _col( r._col)
{
	_data = new int* [_row];
	int *t = new int [_row * _col];
	for( int i = 0; i < _row; i++ )
		_data[i] = t + i * _row;
	memcpy( static_cast<void*>(_data),
		static_cast<void*>(r._data),
		sizeof(int) * _row * _col );
}


Matrix::Matrix( Matrix&& r )
	: _row( r._row ), _col( r._col ), _data( r._data )
{
	r._data = NULL;
}


void Matrix::operator= ( const Matrix& r )
{
	_row = r._row;
	_col = r._col;
	memcpy( static_cast<void*>(_data),
		static_cast<void*>(_data),
		sizeof(int) * _row * _col );
}


Matrix::~Matrix()
{
	// _data is stored continously, I allocate a one-demention array to store it,
	// _data[0] is the begin adress.
	delete []( _data[0] );
}


int Matrix::operator() (int i, int j) const
{
	return _data[i][j];
}


int& Matrix::operator() (int i, int j)
{
	return _data[i][j];
}


Matrix operator* (const Matrix& l, const Matrix& r)
{
///.///
}


istream& operator>> (istream& is, Matrix& m)
{
	vector<int> t_line;
	int t;
	// Read first integer to skip blank lines.
	is >> t;
	t_line.push_back( t );
	char cur;
	// Read a line, determine which integers a line has.
	//   I am sorry to say that I don't know how to use istream object
	//   to read character, here, I read from stdin with c library scanf().
	while( scanf( "%c", &cur ) && t != '\n' ){
		putchar( cur );
		is >> t;
		t_line.push_back( t );
	}
	m._col = t_line.size();

	// Read remaining
	char last = '\n';
	while( scanf( "%c", &cur ) && ( last == '\n' ) && ( cur == '\n' ) ){
		putchar( cur );
		last = cur;
		is >> t;
		t_line.push_back( t );
	}
	m._row = t_line.size() / m._col;

	return is;
}


ostream& operator<< (ostream& os, Matrix& m)
{
	for( int i = 0; i < m._row; i++ ){
		for( int j = 0; j < m._col; j++ ){
			os << " " << m._data[i][j];
		}
		os << "\n";
	}

	return os;
}

