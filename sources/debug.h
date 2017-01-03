// Code by RV

#ifndef _DEBUG_H_
#define _DEBUG_H_


#define FLOAT_DECIMAL_PLACES 4

class Debug {
public:  
  Debug(int nLevel=1);
  void SetDebugLevel(int n);
  void Mess(String out); 
  void Mess(String out, int n); 
  void Mess(String out, float f); 

private:
	int m_nDebug;

};


#endif // _DEBUG_H_
