#include "DialogSet.hxx"

using namespace resip;
using namespace std;

DialogSet::DialogSet(const BaseCreator *creator) : 
    mDialogs(),
    mCreator(creator)
{
   Dialog* dialog = new Dialog(*this, request);
   addDialog(dialog);
   dialog->dispatch(request);
}

DialogSet::DialogSet(const SipMessage& request)
   mDialogs(),
   mCreator(NULL),
   mId(request)
{
   assert(request.isRequest());
}

DialogSet::~DialogSet()
{
}

DialogSetId
Dialogset::getId()
{
   return mId;
}

void
DialogSet::addDialog(Dialog *dialog)
{
   mDialogs.push_back(dialog);
}

void 
DialogSet::removeDialog(const Dialog *dialog)
{
    mDialogs.remove(dialog);
}

DialogIdSet 
DialogSet::getDialogs() const
{
    /** @todo Implment this method */
}

Dialog* 
DialogSet::findDialog(const DialogId id)
{
    std::list<Dialog*>::iterator it = mDialogs.start();
    Dialog *dialog;
    while (it != mDialogs.end())
    {
        dialog  = it->next();
        if (dialog->getId() == id)
        {
            return dialog;
        }
    }
    return NULL;
}

Dialog*
Dialogset::findDialog( const Data& otherTag )
{
    std::list<Dialog*>::iterator it = mDialogs.start();
    Dialog *dialog;
    while (it != mDialogs.end())
    {
        dialog  = it->next();
        if (dialog->getId() == otherTag)
        {
            return dialog;
        }
    }
    return NULL;
}

Dialog* findDialog(SipMessage& msg)
{
    std::list<Dialog*>::iterator it = mDialogs.start();
    Dialog *dialog;
    while (it != mDialogs.end())
    {
        dialog = it->next();
        if (dialog->getId() == msg)
        {
            return dialog;
        }
    }
    return NULL;
}

BaseCreator* 
DialogSet::getCreator()
{
    return mCreator;
}
    
void
DialogSet::dispatch(const SipMessage& msg)
{
   assert(msg.isRequest() || msg.isResponse());
   Dialog* dialog = findDialog(msg);
   if (dialog == 0)
   {
      dialog = new Dialog(mDum, msg);
      this->addDialog(dialog);
   }
   dialog->dispatch(msg);
}

bool
DialogSet::mergeRequest(const SipMessage& request)
{
   for (DialogSet::const_iterator i = dialogs.begin(); i != dialogs.end(); ++i)
   {
      if (i->shouldMerge(request))
      {
         InfoLog (<< "Merging request for: " << request.brief());
         return true;
      }
   }
}

bool
DialogSet::empty() const
{
   return mDialogs.empty();
}

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
