#include <iostream>
#include <ios>
#include <string>
#include <fstream>



// Sample PPM color chart from "RayTracing Over a Weekend" by Peter Shirley

int main()
{

    std::string file {"ppmexample.ppm"};
    std::ofstream ost(file);                        // the file is written into Home directory; Codelite output path descriptions not working
                                                    // in XCode output path can be specified as relative or specific and works
    int nx{400};
    int ny{300};
    
    ost<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j=ny-1; j>=0; --j)  {
        for(int i=0; i<nx; ++i) {
            float r=float(i) / float(nx);
            float g=float(j) / float(ny);
            float b=0.2;
            int ir=int(255.99*r);
            int ig=int(255.99*g);
            int ib=int(255.99*b);
            ost<<ir<<" "<<ig<<" "<<ib<<"\n";
        }       
    }
    
 return 0;
}