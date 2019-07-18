#include <iostream>
#include <fstream>
#include <functional>
#include <map>

#include <cassert>
#include <cstdio>
#include <yas/mem_streams.hpp>
#include <yas/file_streams.hpp>
#include <yas/std_streams.hpp>
#include <yas/null_streams.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/text_oarchive.hpp>
#include <yas/text_iarchive.hpp>
#include <yas/json_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/std_types.hpp>
#include <yas/serialize.hpp>
#include <yas/tools/archinfo.hpp>
#include <yas/tools/hexdump.hpp>


#include <yas/serialize.hpp>
#include <yas/std_types.hpp>
#include <cstdint>
#include <ostream>

#include <yas/object.hpp>
/***************************************************************************/



/***************************************************************************/

int main() {
    


     float data[4]={1.1,2.1,3.3,4.2};
    float dataname[4][4]={{0}};

 //   const auto myobj=YAS_OBJECT_NVP("obj",("othername",data),("hmm",data),("what",data),("data",data));
   

   
    const char *fname = "file.bin";

    yas::load<yas::file|yas::binary>(fname,YAS_OBJECT_NVP(
                "obj"
                ,("othername", dataname[0])
                ,("hmm", dataname[1])
                ,("what", dataname[2])
                ,("data",dataname[3])
            ));

    std::cout<<dataname[0][0]<<"\n"<<dataname[0][1]<<"\n"<<dataname[1][0]<<"\n"<<dataname[3][3]<<std::endl;

   return 0;

}
