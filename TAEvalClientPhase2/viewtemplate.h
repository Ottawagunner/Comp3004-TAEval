#ifndef VIEWTEMPLATE_H
#define VIEWTEMPLATE_H
#include "types.h"
#include <string>
class ViewListDialog;
class ViewIndividualDialog;
class viewTemplate{
public:
    virtual void closeListDialog(ViewListDialog*) = 0;
    virtual void closeIndividualDialog(ViewIndividualDialog*) = 0;
    virtual void listReq(viewIndividualType listReq, std::string, std::string,std::string)=0;
    virtual void setSave(bool) = 0;
    virtual void switchToTask(std::string s, ViewListDialog* v) = 0;
};

#endif // VIEWTEMPLATE_H
