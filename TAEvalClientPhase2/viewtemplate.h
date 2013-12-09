#ifndef VIEWTEMPLATE_H
#define VIEWTEMPLATE_H
#include "types.h"
class ViewListDialog;
class ViewIndividualDialog;
class viewTemplate{
public:
    virtual void closeListDialog(ViewListDialog*) = 0;
    virtual void closeIndividualDialog(ViewIndividualDialog*) = 0;
    virtual void listReq(viewIndividualType listReq, std::string)=0;
    virtual void setSave(bool) = 0;
};

#endif // VIEWTEMPLATE_H
