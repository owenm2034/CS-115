// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 29th

const int MAXROWS = 2;
const int MAXCOLS = 3;


template <typename M_type>
class Matrix
{
  private:
   M_type doubleArray[MAXROWS][MAXCOLS];
   int rows;
   int cols;

  public:
   // Constructor
   Matrix();  // Set rows to MAXROWS and cols to MAXCOLS
	            // Initialize all the values of doubleArray to zero
    
   // Getter Functions
   void printMatrix(); 

   // Setter Functions
   void setMatrix(M_type [][MAXCOLS]); // Set the doubleArray to what is sent
   void addMatrix(M_type [][MAXCOLS]); // Add an array to doubleArray
   void addMatrix(Matrix<M_type> otherMatrix); // Add a Matrix to doubleArray

   // destructor not needed
};