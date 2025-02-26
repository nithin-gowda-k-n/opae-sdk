## Copyright(c) 2020-2022, Intel Corporation
##
## Redistribution  and  use  in source  and  binary  forms,  with  or  without
## modification, are permitted provided that the following conditions are met:
##
## * Redistributions of  source code  must retain the  above copyright notice,
##   this list of conditions and the following disclaimer.
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer in the documentation
##   and/or other materials provided with the distribution.
## * Neither the name  of Intel Corporation  nor the names of its contributors
##   may be used to  endorse or promote  products derived  from this  software
##   without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
## IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
## ARE DISCLAIMED.  IN NO EVENT  SHALL THE COPYRIGHT OWNER  OR CONTRIBUTORS BE
## LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
## CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED  TO,  PROCUREMENT  OF
## SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE,  DATA, OR PROFITS;  OR BUSINESS
## INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY  OF LIABILITY,  WHETHER IN
## CONTRACT,  STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE  OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  EVEN IF ADVISED OF THE
## POSSIBILITY OF SUCH DAMAGE.

opae_test_add_static_lib(TARGET bitstream-static
    SOURCE 
        ${OPAE_LIB_SOURCE}/libbitstream/bitstream.c
	${OPAE_LIB_SOURCE}/libbitstream/bits_utils.c
	${OPAE_LIB_SOURCE}/libbitstream/metadatav1.c
    LIBS
        opae-c
        ${libjson-c_LIBRARIES}
        ${libuuid_LIBRARIES}
)

opae_test_add(TARGET test_bitstream_bitstream_c
    SOURCE test_bitstream_c.cpp
    LIBS bitstream-static
)

opae_test_add(TARGET test_bitstream_bits_utils_c
    SOURCE test_bits_utils_c.cpp
    LIBS bitstream-static
)

opae_test_add(TARGET test_bitstream_metadatav1_c
    SOURCE test_metadatav1_c.cpp
    LIBS bitstream-static
)
