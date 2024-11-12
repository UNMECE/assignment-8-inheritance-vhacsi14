#include <iostream>
#include <cmath>


const double epsilon_0 = 8.854e-12;
const double mu_0 = 4.0e-7 * M_PI;

class Field
{
    protected: 
	double x, y, z;

    public: 
	Field() : x(0), y(0), z(0) {} 
	Field(double x, double y, double z) : x(x), y(y), z(z) {} 

    virtual void printMagnitude() const 
    {
	std::cout << "Field Components: (" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    virtual ~Field() {} 
}; 

class ElectricField : public Field 
{
    private: 
	double valueElectField;
    
    public: 
	ElectricField() : Field(), valueElectField(0) {}
	ElectricField(double x, double y, double z) : Field(x, y, z), valueElectField(0) {} 

void calcElectricField(double Q, double r) 
{
    valueElectField = Q /(4 * M_PI * r * r * epsilon_0);
} 

void printMagnitude() const override 
{ 
    Field::printMagnitude();
	std::cout << "Calculated Electric Field: " << valueElectField << " N/C " << std::endl;
} 

ElectricField operator+(const ElectricField& other)
{
    return ElectricField(x + other.x, y + other.y, z + other.z); 
}

    friend std::ostream& operator<<(std::ostream& os, const ElectricField& eField)
    {
	os << "Electric Field Components: (" << eField.x << ", " << eField.y << ", " << eField.z << ")"
	   << " | Calculated Electric Field: " << eField.valueElectField << " N/C ";
	return os;
    }
};

class MagneticField : public Field 
{
    private:
	double valueMagField;
    public: 
	MagneticField() : Field(), valueMagField(0) {}
	MagneticField(double x, double y, double z) : Field(x, y, z), valueMagField(0) {}

    void calcMagneticField(double I, double r) 
    {
	valueMagField = I / (2 * M_PI * r * mu_0);
    }

    void printMagnitude() const override 
    {
	Field::printMagnitude();
	std::cout << "Calculated Magnetic Field: " << valueMagField << " T" << std::endl;
    }

    MagneticField operator+(const MagneticField& other) 
    {
	return MagneticField(x + other.x, y + other.y, z + other.z);
    }


    friend std::ostream& operator<<(std::ostream& os, const MagneticField& mField)
    {
	os << "Magnetic FIeld Components: (" << mField.x << ", " << mField.y << ", " << mField.z << ")"
	   << " | Calculated Magnetic Field: " << mField.valueMagField << " T";
	return os;
    }
};



int main() {

   
    ElectricField e1(1.0, 0.0, 0.0), e2(0.0, 1.0, 0.0);
    e1.calcElectricField(1.0e-6, 0.5); 
    e2.calcElectricField(2.0e-6, 1.0); 

    
    e1.printMagnitude();
    e2.printMagnitude();

    
    ElectricField e3 = e1 + e2;
    std::cout << e3 << std::endl;

    
    MagneticField m1(1.0, 0.0, 0.0), m2(0.0, 1.0, 0.0);
    m1.calcMagneticField(10.0, 0.1); 
    m2.calcMagneticField(20.0, 0.2);

    
    m1.printMagnitude();
    m2.printMagnitude();

    
    MagneticField m3 = m1 + m2;
    std::cout << m3 << std::endl;

    return 0;
}
