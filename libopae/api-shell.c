// Copyright(c) 2018, Intel Corporation
//
// Redistribution  and  use  in source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of  source code  must retain the  above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name  of Intel Corporation  nor the names of its contributors
//   may be used to  endorse or promote  products derived  from this  software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
// IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT  SHALL THE COPYRIGHT OWNER  OR CONTRIBUTORS BE
// LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
// CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED  TO,  PROCUREMENT  OF
// SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE,  DATA, OR PROFITS;  OR BUSINESS
// INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY  OF LIABILITY,  WHETHER IN
// CONTRACT,  STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE  OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include "opae_int.h"
#include "pluginmgr.h"

fpga_result fpgaInitialize(const char *config_file)
{
	return opae_plugin_mgr_initialize(config_file) ? FPGA_EXCEPTION : FPGA_OK;
}

fpga_result fpgaOpen(fpga_token token, fpga_handle *handle, int flags)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (!handle) {
		OPAE_ERR("NULL handle");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaOpen) {
		fpga_handle opae_handle = NULL;
		opae_wrapped_handle *wh;

		res = wt->adapter_table->fpgaOpen(wt->opae_token,
						  &opae_handle,
						  flags);

		if (res != FPGA_OK)
			return res;

		wh = opae_allocate_wrapped_handle(wt,
						  opae_handle,
						  wt->adapter_table);

		if (!wh) {
			OPAE_ERR("malloc() failed");
			return FPGA_NO_MEMORY;
		}

		*handle = wh;

	} else
		OPAE_MSG("NULL fpgaOpen in adapter");

	return res;
}

fpga_result fpgaClose(fpga_handle handle)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaClose)
		res = wh->adapter_table->fpgaClose(wh->opae_handle);
	else
		OPAE_MSG("NULL fpgaClose in adapter");

	opae_destroy_wrapped_handle(wh);

	return res;
}

fpga_result fpgaReset(fpga_handle handle)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaReset)
		res = wh->adapter_table->fpgaReset(wh->opae_handle);
	else
		OPAE_MSG("NULL fpgaReset in adapter");

	return res;
}

fpga_result fpgaGetPropertiesFromHandle(fpga_handle handle,
					fpga_properties *prop)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaGetProperties(fpga_token token, fpga_properties *prop)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaUpdateProperties(fpga_token token, fpga_properties prop)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaClearProperties(fpga_properties prop)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaCloneProperties(fpga_properties src, fpga_properties *dst)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaDestroyProperties(fpga_properties *prop)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetParent(const fpga_properties prop,
				    fpga_token *parent)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetParent(fpga_properties prop, fpga_token parent)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetObjectType(const fpga_properties prop,
					fpga_objtype *objtype)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetObjectType(fpga_properties prop,
					fpga_objtype objtype)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetSegment(const fpga_properties prop,
				     uint16_t *segment)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetSegment(fpga_properties prop, uint16_t segment)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetBus(const fpga_properties prop, uint8_t *bus)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetBus(fpga_properties prop, uint8_t bus)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetDevice(const fpga_properties prop, uint8_t *device)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetDevice(fpga_properties prop, uint8_t device)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetFunction(const fpga_properties prop,
				      uint8_t *function)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetFunction(fpga_properties prop, uint8_t function)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetSocketID(const fpga_properties prop,
				      uint8_t *socket_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetSocketID(fpga_properties prop, uint8_t socket_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetDeviceID(const fpga_properties prop,
				      uint16_t *device_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetDeviceID(fpga_properties prop, uint16_t device_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetNumSlots(const fpga_properties prop,
				      uint32_t *num_slots)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetNumSlots(fpga_properties prop, uint32_t num_slots)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetBBSID(const fpga_properties prop, uint64_t *bbs_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetBBSID(fpga_properties prop, uint64_t bbs_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetBBSVersion(const fpga_properties prop,
					fpga_version *bbs_version)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetBBSVersion(fpga_properties prop,
					fpga_version version)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetVendorID(const fpga_properties prop,
				      uint16_t *vendor_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetVendorID(fpga_properties prop, uint16_t vendor_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetModel(const fpga_properties prop, char *model)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetModel(fpga_properties prop, char *model)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetLocalMemorySize(const fpga_properties prop,
					     uint64_t *lms)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetLocalMemorySize(fpga_properties prop, uint64_t lms)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetCapabilities(const fpga_properties prop,
					  uint64_t *capabilities)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetCapabilities(fpga_properties prop,
					  uint64_t capabilities)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetGUID(const fpga_properties prop, fpga_guid *guid)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetGUID(fpga_properties prop, fpga_guid guid)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetNumMMIO(const fpga_properties prop,
				     uint32_t *mmio_spaces)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetNumMMIO(fpga_properties prop, uint32_t mmio_spaces)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetNumInterrupts(const fpga_properties prop,
					   uint32_t *num_interrupts)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetNumInterrupts(fpga_properties prop,
					   uint32_t num_interrupts)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetAcceleratorState(const fpga_properties prop,
					      fpga_accelerator_state *state)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetAcceleratorState(fpga_properties prop,
					      fpga_accelerator_state state)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetObjectID(const fpga_properties prop,
				      uint64_t *object_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetObjectID(const fpga_properties prop,
				      uint64_t object_id)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesGetNumErrors(const fpga_properties prop,
				       uint32_t *num_errors)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaPropertiesSetNumErrors(const fpga_properties prop,
				       uint32_t num_errors)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaWriteMMIO64(fpga_handle handle, uint32_t mmio_num,
			    uint64_t offset, uint64_t value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaWriteMMIO64)
		res = wh->adapter_table->fpgaWriteMMIO64(
			wh->opae_handle, mmio_num, offset, value);
	else
		OPAE_MSG("NULL fpgaWriteMMIO64 in adapter");

	return res;
}

fpga_result fpgaReadMMIO64(fpga_handle handle, uint32_t mmio_num,
			   uint64_t offset, uint64_t *value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaReadMMIO64)
		res = wh->adapter_table->fpgaReadMMIO64(
			wh->opae_handle, mmio_num, offset, value);
	else
		OPAE_MSG("NULL fpgaReadMMIO64 in adapter");

	return res;
}

fpga_result fpgaWriteMMIO32(fpga_handle handle, uint32_t mmio_num,
			    uint64_t offset, uint32_t value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaWriteMMIO32)
		res = wh->adapter_table->fpgaWriteMMIO32(
			wh->opae_handle, mmio_num, offset, value);
	else
		OPAE_MSG("NULL fpgaWriteMMIO32 in adapter");

	return res;
}

fpga_result fpgaReadMMIO32(fpga_handle handle, uint32_t mmio_num,
			   uint64_t offset, uint32_t *value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaReadMMIO32)
		res = wh->adapter_table->fpgaReadMMIO32(
			wh->opae_handle, mmio_num, offset, value);
	else
		OPAE_MSG("NULL fpgaReadMMIO32 in adapter");

	return res;
}

fpga_result fpgaMapMMIO(fpga_handle handle, uint32_t mmio_num,
			uint64_t **mmio_ptr)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaMapMMIO)
		res = wh->adapter_table->fpgaMapMMIO(wh->opae_handle, mmio_num,
						     mmio_ptr);
	else
		OPAE_MSG("NULL fpgaMapMMIO in adapter");

	return res;
}

fpga_result fpgaUnmapMMIO(fpga_handle handle, uint32_t mmio_num)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaUnmapMMIO)
		res = wh->adapter_table->fpgaUnmapMMIO(wh->opae_handle,
						       mmio_num);
	else
		OPAE_MSG("NULL fpgaUnmapMMIO in adapter");

	return res;
}

typedef struct _opae_enumeration_context {
	// <verbatim from fpgaEnumerate>
	const fpga_properties *filters;
	uint32_t num_filters;
	fpga_token *wrapped_tokens;
	uint32_t max_wrapped_tokens;
	uint32_t *num_matches;
	// </verbatim from fpgaEnumerate>

	fpga_token *adapter_tokens;
	uint32_t num_wrapped_tokens;
	uint32_t errors;
} opae_enumeration_context;

static int opae_enumerate(const opae_api_adapter_table *adapter, void *context)
{
	opae_enumeration_context *ctx = (opae_enumeration_context *) context;
	fpga_result res;
	uint32_t num_matches = 0;
	uint32_t i;
	uint32_t space_remaining;

	// TODO: accept/reject this adapter, based on device support
	if (adapter->supports_device) {

	}

	// TODO: accept/reject this adapter, based on host support
	if (adapter->supports_host) {

	}

	space_remaining = ctx->max_wrapped_tokens - ctx->num_wrapped_tokens;

	if (ctx->wrapped_tokens && !space_remaining)
		return OPAE_ENUM_STOP;

	if (!adapter->fpgaEnumerate) {
		OPAE_MSG("NULL fpgaEnumerate in adapter \"%s\"",
				adapter->plugin.path);
		return OPAE_ENUM_CONTINUE;
	}

	res = adapter->fpgaEnumerate(ctx->filters,
				     ctx->num_filters,
				     ctx->adapter_tokens,
				     space_remaining,
				     &num_matches);

	if (res != FPGA_OK) {
		OPAE_ERR("fpgaEnumerate() failed for \"%s\"",
				adapter->plugin.path);
		++ctx->errors;
		return OPAE_ENUM_CONTINUE;
	}

	*ctx->num_matches += num_matches;

	if (!ctx->adapter_tokens) {
		// requesting token count, only.
		return OPAE_ENUM_CONTINUE;
	}

	for (i = 0 ; i < space_remaining ; ++i) {
		opae_wrapped_token *wt =
			opae_allocate_wrapped_token(ctx->adapter_tokens[i],
						    adapter);
		if (!wt) {
			++ctx->errors;
			return OPAE_ENUM_STOP;
		}

		ctx->wrapped_tokens[ctx->num_wrapped_tokens++] = wt;
	}

	return ctx->num_wrapped_tokens == ctx->max_wrapped_tokens ?
		OPAE_ENUM_STOP : OPAE_ENUM_CONTINUE;
}

fpga_result fpgaEnumerate(const fpga_properties *filters, uint32_t num_filters,
			  fpga_token *tokens, uint32_t max_tokens,
			  uint32_t *num_matches)
{
	fpga_result res = FPGA_EXCEPTION;
	fpga_token *adapter_tokens = NULL;

	opae_enumeration_context enum_context;


	ASSERT_NOT_NULL(num_matches);

	if ((max_tokens > 0) && !tokens) {
		OPAE_ERR("max_tokens > 0 with NULL tokens");
		return FPGA_INVALID_PARAM;
	}

	if ((num_filters > 0) && !filters) {
		OPAE_ERR("num_filters > 0 with NULL filters");
		return FPGA_INVALID_PARAM;
	}

	if ((num_filters == 0) && (filters != NULL)) {
		OPAE_ERR("num_filters == 0 with non-NULL filters");
		return FPGA_INVALID_PARAM;
	}

	*num_matches = 0;

	enum_context.filters = filters;
	enum_context.num_filters = num_filters;
	enum_context.wrapped_tokens = tokens;
	enum_context.max_wrapped_tokens = max_tokens;
	enum_context.num_matches = num_matches;

	if (tokens) {
		adapter_tokens = (fpga_token *) calloc(max_tokens, sizeof(fpga_token));
		if (!adapter_tokens) {
			OPAE_ERR("out of memory");
			return FPGA_NO_MEMORY;
		}
	}

	enum_context.adapter_tokens = adapter_tokens;
	enum_context.num_wrapped_tokens = 0;
	enum_context.errors = 0;

	opae_plugin_mgr_for_each_adapter(opae_enumerate, &enum_context);

	res = (enum_context.errors > 0) ? FPGA_EXCEPTION : FPGA_OK;

	if (adapter_tokens)
		free(adapter_tokens);

	return res;
}

fpga_result fpgaCloneToken(fpga_token src, fpga_token *dst)
{
	fpga_token cloned_token = NULL;
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(src);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (!dst) {
		OPAE_ERR("NULL output parameter");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaCloneToken) {
		res = wt->adapter_table->fpgaCloneToken(wt->opae_token,
							&cloned_token);

		if (res != FPGA_OK)
			return res;

		wt = opae_allocate_wrapped_token(cloned_token,
						 wt->adapter_table);

		if (!wt) {
			OPAE_ERR("malloc failed");
			res = FPGA_NO_MEMORY;
		} else
			*dst = wt;

	} else
		OPAE_MSG("NULL fpgaCloneToken in adapter");

	return res;
}

fpga_result fpgaDestroyToken(fpga_token *token)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt;

	if (!token) {
		OPAE_ERR("NULL wrapped token");
		return FPGA_INVALID_PARAM;
	}

	wt = opae_validate_wrapped_token(*token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaDestroyToken)
		res = wt->adapter_table->fpgaDestroyToken(&wt->opae_token);
	else
		OPAE_MSG("NULL fpgaDestroyToken in adapter");

	opae_destroy_wrapped_token(wt);

	return res;
}

fpga_result fpgaGetNumUmsg(fpga_handle handle, uint64_t *value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaGetNumUmsg)
		res = wh->adapter_table->fpgaGetNumUmsg(wh->opae_handle, value);
	else
		OPAE_MSG("NULL fpgaGetNumUmsg in adapter");

	return res;
}

fpga_result fpgaSetUmsgAttributes(fpga_handle handle, uint64_t value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaSetUmsgAttributes)
		res = wh->adapter_table->fpgaSetUmsgAttributes(wh->opae_handle,
							       value);
	else
		OPAE_MSG("NULL fpgaSetUmsgAttributes in adapter");

	return res;
}

fpga_result fpgaTriggerUmsg(fpga_handle handle, uint64_t value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaTriggerUmsg)
		res = wh->adapter_table->fpgaTriggerUmsg(wh->opae_handle,
							 value);
	else
		OPAE_MSG("NULL fpgaTriggerUmsg in adapter");

	return res;
}

fpga_result fpgaGetUmsgPtr(fpga_handle handle, uint64_t **umsg_ptr)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaGetUmsgPtr)
		res = wh->adapter_table->fpgaGetUmsgPtr(wh->opae_handle,
							umsg_ptr);
	else
		OPAE_MSG("NULL fpgaGetUmsgPtr in adapter");

	return res;
}

fpga_result fpgaPrepareBuffer(fpga_handle handle, uint64_t len, void **buf_addr,
			      uint64_t *wsid, int flags)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaPrepareBuffer)
		res = wh->adapter_table->fpgaPrepareBuffer(
			wh->opae_handle, len, buf_addr, wsid, flags);
	else
		OPAE_MSG("NULL fpgaPrepareBuffer in adapter");

	return res;
}

fpga_result fpgaReleaseBuffer(fpga_handle handle, uint64_t wsid)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaReleaseBuffer)
		res = wh->adapter_table->fpgaReleaseBuffer(wh->opae_handle,
							   wsid);
	else
		OPAE_MSG("NULL fpgaReleaseBuffer in adapter");

	return res;
}

fpga_result fpgaGetIOAddress(fpga_handle handle, uint64_t wsid,
			     uint64_t *ioaddr)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(handle);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaGetIOAddress)
		res = wh->adapter_table->fpgaGetIOAddress(wh->opae_handle, wsid,
							  ioaddr);
	else
		OPAE_MSG("NULL fpgaGetIOAddress in adapter");

	return res;
}

fpga_result fpgaGetOPAECVersion(fpga_version *version)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaGetOPAECVersionString(char *version_str, size_t len)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaGetOPAECBuildString(char *build_str, size_t len)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaReadError(fpga_token token, uint32_t error_num, uint64_t *value)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaReadError)
		res = wt->adapter_table->fpgaReadError(wt->opae_token,
						       error_num, value);
	else
		OPAE_MSG("NULL fpgaReadError in adapter");

	return res;
}

fpga_result fpgaClearError(fpga_token token, uint32_t error_num)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaClearError)
		res = wt->adapter_table->fpgaClearError(wt->opae_token,
							error_num);
	else
		OPAE_MSG("NULL fpgaClearError in adapter");

	return res;
}

fpga_result fpgaClearAllErrors(fpga_token token)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaClearAllErrors)
		res = wt->adapter_table->fpgaClearAllErrors(wt->opae_token);
	else
		OPAE_MSG("NULL fpgaClearAllErrors in adapter");

	return res;
}

fpga_result fpgaGetErrorInfo(fpga_token token, uint32_t error_num,
			     struct fpga_error_info *error_info)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_token *wt = opae_validate_wrapped_token(token);

	if (!wt) {
		OPAE_ERR("invalid wrapped token");
		return FPGA_INVALID_PARAM;
	}

	if (wt->adapter_table->fpgaGetErrorInfo)
		res = wt->adapter_table->fpgaGetErrorInfo(
			wt->opae_token, error_num, error_info);
	else
		OPAE_MSG("NULL fpgaGetErrorInfo in adapter");

	return res;
}

const char *fpgaErrStr(fpga_result e)
{
	switch (e) {
	case FPGA_OK:
		return "success";
	case FPGA_INVALID_PARAM:
		return "invalid parameter";
	case FPGA_BUSY:
		return "resource busy";
	case FPGA_EXCEPTION:
		return "exception";
	case FPGA_NOT_FOUND:
		return "not found";
	case FPGA_NO_MEMORY:
		return "no memory";
	case FPGA_NOT_SUPPORTED:
		return "not supported";
	case FPGA_NO_DRIVER:
		return "no driver available";
	case FPGA_NO_DAEMON:
		return "no fpga daemon running";
	case FPGA_NO_ACCESS:
		return "insufficient privileges";
	case FPGA_RECONF_ERROR:
		return "reconfiguration error";
	default:
		return "unknown error";
	}
}

fpga_result fpgaCreateEventHandle(fpga_event_handle *event_handle)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaDestroyEventHandle(fpga_event_handle *event_handle)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaGetOSObjectFromEventHandle(const fpga_event_handle eh, int *fd)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaRegisterEvent(fpga_handle handle, fpga_event_type event_type,
			      fpga_event_handle event_handle, uint32_t flags)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaUnregisterEvent(fpga_handle handle, fpga_event_type event_type,
				fpga_event_handle event_handle)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaAssignPortToInterface(fpga_handle fpga, uint32_t interface_num,
				      uint32_t slot_num, int flags)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaAssignToInterface(fpga_handle fpga, fpga_token accelerator,
				  uint32_t host_interface, int flags)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaReleaseFromInterface(fpga_handle fpga, fpga_token accelerator)
{

	return FPGA_NOT_SUPPORTED;
}

fpga_result fpgaReconfigureSlot(fpga_handle fpga, uint32_t slot,
				const uint8_t *bitstream, size_t bitstream_len,
				int flags)
{
	fpga_result res = FPGA_NOT_SUPPORTED;
	opae_wrapped_handle *wh = opae_validate_wrapped_handle(fpga);

	if (!wh) {
		OPAE_ERR("invalid wrapped handle");
		return FPGA_INVALID_PARAM;
	}

	if (wh->adapter_table->fpgaReconfigureSlot)
		res = wh->adapter_table->fpgaReconfigureSlot(
			wh->opae_handle, slot, bitstream, bitstream_len, flags);
	else
		OPAE_MSG("NULL fpgaReconfigureSlot in adapter");

	return res;
}
