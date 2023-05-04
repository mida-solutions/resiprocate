
#include "PyRouteMessageHandler.hxx"
#include "PyRouteWorker.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace repro;

PyRouteMessageHandler::PyRouteMessageHandler(Dispatcher& dispatcher) :
   mDispatcher(dispatcher)
{
}

PyRouteMessageHandler::~PyRouteMessageHandler()
{
}

void
PyRouteMessageHandler::outboundMessage(const Tuple &source, const Tuple &destination, const SipMessage &msg)
{
   onMessage(true, source, destination, msg);
}

void
PyRouteMessageHandler::inboundMessage(const Tuple& source, const Tuple& destination, const SipMessage &msg)
{
   onMessage(false, source, destination, msg);
}

void
PyRouteMessageHandler::onMessage(bool outbound, const Tuple &source, const Tuple &destination, const SipMessage &msg)
{
   DebugLog(<< "onMessage: PyRoute");

   auto work = new PyRouteMessageHandlerWork(msg);
   std::unique_ptr<ApplicationMessage> app(work);
   if(mDispatcher.post(app))
   {
      return;
   }
   else
   {
      ErrLog(<<"mDispatcher.post failed, maybe not accepting work");
      return;
   }
}

/* ====================================================================
 *
 * Copyright (c) 2022, Software Freedom Institute https://softwarefreedom.institute
 * Copyright (c) 2022, Daniel Pocock https://danielpocock.com
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
 * 3. Neither the name of the author(s) nor the names of any contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ====================================================================
 *
 *
 */

