//robin timmermans
#if !defined(C_ERROR_H)
#define C_ERROR_H

enum ErrorType{
	ET_INDEX
};

class C_ERROR
{
private:
	ErrorType m_type;
public:
	C_ERROR(const ErrorType type);
	ErrorType GetType()const {return m_type;}
};

#endif // C_ERROR_H