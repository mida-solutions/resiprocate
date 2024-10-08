
#include <iostream>
#include <fstream>

#include "media/samples/playback_prompt.h"
#include "media/samples/record_prompt.h"

using namespace std;

void write_out(const unsigned char* data, size_t count, const char *filename)
{
   ofstream o;
   o.open(filename);
   o.write((const char *)data, count);
   o.close();
}

int main(int argc, char* argv[])
{
   // 1 channel, 8kHz 16bit PCM
   //
   // To play it back:
   //
   //    aplay -c 1 -f S16_LE -r 8000 /tmp/playback_prompt.raw
   //
   // To convert from raw to WAV:
   //
   //    sox -r 8k -e signed -b 16 -c 1 /tmp/playback_prompt.raw /tmp/playback_prompt.wav

   write_out(playback_prompt, sizeof(playback_prompt), "/tmp/playback_prompt.raw");
   write_out(record_prompt, sizeof(record_prompt), "/tmp/record_prompt.raw");

   return 0;
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

