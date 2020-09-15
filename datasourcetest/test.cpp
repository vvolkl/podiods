
#include "ROOT/RDataSource.hxx"
#include <iostream>
#include "ROOT/RDF/RInterface.hxx"

#include <ROOT/RDF/Utils.hxx>
#include <ROOT/TSeq.hxx>
#include <ROOT/RTrivialDS.hxx>
#include <ROOT/RMakeUnique.hxx>
#include <TError.h>

class ds: public ROOT::RDF::RDataSource {
  public:
     ds() {
        theInts.push_back(3);
        theIntPointers.push_back(&(theInts[0]));
        columnames.push_back("aaa");
       };
   ~ds() {}; 
   const std::vector<std::string> &GetColumnNames() const {return columnames;};
   bool HasColumn(std::string_view colName) const {return true;};
   std::string GetTypeName(std::string_view) const {return "";};
   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges() {return {{0,0}};};
   bool SetEntry(unsigned int slot, ULong64_t entry) {return true;};
   void SetNSlots(unsigned int nSlots) {}; 
   void Initialise() {}; 

    std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &) {
         std::vector<void *> ret;
               ret.emplace_back((void *)(&theIntPointers[0]));
                  return ret;
                     };

                         std::vector<int> theInts;
                             std::vector<int*> theIntPointers;
                                 std::vector<std::string> columnames;

};

using namespace ROOT;
using namespace ROOT::RDF;
//
//
//




RInterface<RDFDetail::RLoopManager, ds> MakeFrame()
{
   auto lm = std::make_unique<RDFDetail::RLoopManager>(std::make_unique<ds>(),
                                                       RDFInternal::ColumnNames_t{});
   return RInterface<RDFDetail::RLoopManager, ds>(std::move(lm));
};

int main() {

  auto a = ds();
  std::cout << a.GetLabel() << std::endl;
  auto d_s = MakeFrame();
  //std::cout << d_s.GetColumnNames() << std::endl;

  return 0;
}
