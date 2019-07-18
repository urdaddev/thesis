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
    


    const float data[4]={1.1,2.1,3.3,4.2};
    float dataname{};


    const auto myobj=YAS_OBJECT_NVP("obj",("othername",data),("hmm",data),("what",data),("data",data));
   

   
    const char *fname = "file.bin";
    std::remove(fname);
    yas::save<yas::file|yas::binary>(fname,myobj);

   return 0;

}
