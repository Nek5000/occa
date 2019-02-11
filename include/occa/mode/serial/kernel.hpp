#ifndef OCCA_MODES_SERIAL_KERNEL_HEADER
#define OCCA_MODES_SERIAL_KERNEL_HEADER

#include <vector>

#include <occa/defines.hpp>
#include <occa/core/kernel.hpp>
#include <occa/tools/sys.hpp>

namespace occa {
  namespace serial {
    class device;

    class kernel : public occa::modeKernel_t {
    protected:
      void *dlHandle;
      functionPtr_t function;
      mutable std::vector<void*> vArgs;

    public:
      bool isLauncherKernel;

      kernel(modeDevice_t *modeDevice_,
             const std::string &name_,
             const std::string &sourceFilename_,
             const occa::properties &properties_);
      ~kernel();

      int maxDims() const;
      dim maxOuterDims() const;
      dim maxInnerDims() const;

      void run() const;

      friend class device;
    };
  }
}
#endif
