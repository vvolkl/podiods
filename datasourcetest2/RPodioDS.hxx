#ifndef ROOT_RPODIODS
#define ROOT_RPODIODS

#include "ROOT/RDF/RInterface.hxx"
#include "ROOT/RDataSource.hxx"

namespace ROOT {

namespace RDF {

class RPodioDS final : public ROOT::RDF::RDataSource {
private:
   unsigned int fNSlots = 0U;
   ULong64_t fSize = 0ULL;
   bool fSkipEvenEntries = false;
   std::vector<std::pair<ULong64_t, ULong64_t>> fEntryRanges;
   std::vector<std::string> fColNames{"col0"};
   std::vector<ULong64_t> fCounter;
   std::vector<ULong64_t *> fCounterAddr;
   std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &);

protected:
   std::string AsString() { return "trivial data source"; };

public:
   RPodioDS(ULong64_t size, bool skipEvenEntries = false);
   ~RPodioDS();
   const std::vector<std::string> &GetColumnNames() const;
   bool HasColumn(std::string_view colName) const;
   std::string GetTypeName(std::string_view) const;
   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges();
   bool SetEntry(unsigned int slot, ULong64_t entry);
   void SetNSlots(unsigned int nSlots);
   void Initialise();
   std::string GetLabel();
};

RInterface<RDFDetail::RLoopManager, RPodioDS> MakePodioDataFrame(ULong64_t size, bool skipEvenEntries = false);

} // ns RDF

} // ns ROOT

#endif
