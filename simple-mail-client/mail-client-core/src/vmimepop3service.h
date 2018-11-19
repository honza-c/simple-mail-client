#ifndef VMIMEPOP3SERVICE_H
#define VMIMEPOP3SERVICE_H

#include "src/vmimeinboxservice.h"

class VmimePop3Service : public VmimeInboxService
{
public:
    VmimePop3Service(QObject *parent = nullptr)
        : VmimeInboxService(parent) {}

private:
    vmime::utility::url getStoreUrl() const;
};

#endif // VMIMEPOP3SERVICE_H
