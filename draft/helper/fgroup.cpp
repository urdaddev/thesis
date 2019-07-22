#include <iostream>
#include <cstdio>
#include <armadillo>
#include <map>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/encodings.h>
int main(){
using namespace rapidjson;
FILE* fp = fopen("big.json", "r"); // non-Windows use "r"
char readBuffer[655360];
FileReadStream is(fp, readBuffer, sizeof(readBuffer));
Document d;
d.ParseStream(is);
for (SizeType i = 0; i < d.Size(); i++) 
       assert(d[i]["list"].IsObject());
       d.GetInt64();
arma::mat A(3,3);
A.save("s",arma::cs)
double ab[3]={2.1,2.1,2.2};
double *ptr=A.colptr(0);
 ptr=ab;
double arr[5]={1,2,3,4,5};


static const char* kTypeNames[] = 
    { "Null", "False", "True", "Object", "Array", "String", "Number" };
for (Value::ConstMemberIterator itr = d.MemberBegin();
    itr != d.MemberEnd(); ++itr)
{
    printf("Type of member %s is %s\n",
        itr->name.GetString(), kTypeNames[itr->value.GetType()]);
}
Value::ConstMemberIterator itr = d.FindMember("index");
if (itr != d.MemberEnd())
    printf("%d\n", itr->value.GetInt());   
fclose(fp);
}