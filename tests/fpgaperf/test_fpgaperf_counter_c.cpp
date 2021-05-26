// Original work Copyright(c) 2019-2020, Intel Corporation
// Modifications Copyright(c) 2021, Silicom Denmark A/S
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

#include <opae/fpga.h>

extern "C" {

#include <dirent.h>
#include <linux/perf_event.h>
#include <glob.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EVENT_FILTER		{(char *)"clock", (char *)"fab_port_mmio_read", (char *)"fab_port_mmio_write", (char *)"fab_port_pcie0_read", (char *)"fab_port_pcie0_write"}

#define DFL_PERF_STR_MAX	256

#define DFL_BUFSIZ_MAX		512
/**
 * Initilaize the fpga_perf_counter structure. Dynamically enumerate sysfs path 
 * and get the device type, cpumask, format and generic events.
 * Reset the counter to 0 and enable the counters to get workload instructions.
 */
fpga_result fpgaPerfCounterEnum(fpga_token token);

/* 
 * Enable the performance counter, read the start value and update
 * the fpga_perf_counter start value.
 */
fpga_result fpgaPerfCounterStartRecord(void);

/*
 * Disable the performance counter, read the stop value and update
 * the fpga_perf_counter stop value.
 */
fpga_result fpgaPerfCounterStopRecord(void);

/*print the performance counter values */
fpga_result fpgaPerfCounterPrint(FILE *file);

/* parse the events and format value using sysfs_path */
fpga_result fpga_Perf_Events(char* perf_sysfs_path);

/* parse the events for the perticular device directory */
fpga_result parse_Perf_Event(DIR *dir, char **filter, int filter_size, char *dir_name);

/* parse the each format and get the shift val */
fpga_result parse_Perf_Format(DIR *dir, char *dir_name);

/*free the allocated memory */
fpga_result fpgaPerfCounterFree(void);

}

#include "intel-fpga.h"
#include <linux/ioctl.h>

#include <cstdlib>
#include <string>
#include <opae/properties.h>
#include <opae/utils.h>
#include <opae/fpga.h>
#include "gtest/gtest.h"
#include "mock/test_system.h"


using namespace opae::testing;

class fpgaperf_counter_c_p : public ::testing::TestWithParam<std::string> {
protected:
        fpgaperf_counter_c_p(): tokens_{ {nullptr, nullptr} } {}

        virtual void SetUp() override 
        {
		ASSERT_TRUE(test_platform::exists(GetParam()));
		platform_ = test_platform::get(GetParam());
		system_ = test_system::instance();
		system_->initialize();
		system_->prepare_syfs(platform_);

		filter_ = nullptr;
		ASSERT_EQ(fpgaInitialize(NULL), FPGA_OK);
		ASSERT_EQ(fpgaGetProperties(nullptr, &filter_), FPGA_OK);
		ASSERT_EQ(fpgaPropertiesSetObjectType(filter_, FPGA_DEVICE), FPGA_OK);
		num_matches_ = 0;
		ASSERT_EQ(fpgaEnumerate(&filter_, 1, tokens_.data(), tokens_.size(),
			&num_matches_), FPGA_OK);
		EXPECT_GT(num_matches_, 0);
		dev_ = nullptr;
		ASSERT_EQ(fpgaOpen(tokens_[0], &dev_, 0), FPGA_OK);
        }

        virtual void TearDown() override {
		EXPECT_EQ(fpgaDestroyProperties(&filter_), FPGA_OK);
		if (dev_) {
			EXPECT_EQ(fpgaClose(dev_), FPGA_OK);
			dev_ = nullptr;
		}
		for (auto &t : tokens_) {
			if (t) {
				EXPECT_EQ(fpgaDestroyToken(&t), FPGA_OK);
				t = nullptr;
			}
		}
		fpgaFinalize();
		system_->finalize();
	}
		
	std::array<fpga_token, 2> tokens_;
	fpga_properties filter_;
	fpga_handle dev_;
	test_platform platform_;
	uint32_t num_matches_;
	test_system *system_;
};

/**
* @test       fpgaperf_0
* @brief      Tests: fpgaPerfCounterEnum
* @details    Validates the dfl-fme device path based on token
* 		and parse events and formats <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_0) {
	
	EXPECT_EQ(fpgaPerfCounterEnum(tokens_[0]), FPGA_OK);
}

/**
* @test       fpgaperf_1
* @brief      Tests: fpgaPerfCounterStartRecord
* @details    Validates fpga perf counter start  <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_1) {
	
	EXPECT_EQ(fpgaPerfCounterStartRecord(), FPGA_OK);
}

/**
* @test       fpgaperf_2
* @brief      Tests: fpgaPerfCounterStopRecord
* @details    Validates fpga perf counter stop  <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_2) {

	EXPECT_EQ(fpgaPerfCounterStopRecord(), FPGA_OK);
}
/**
* @test       fpgaperf_3
* @brief      Tests: fpgaPerfCounterPrint
* @details    Validates performance counter prints  <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_3) {

	FILE *f = stdout;

	EXPECT_EQ(fpgaPerfCounterPrint(f), FPGA_OK);
}

/**
* @test       fpgaperf_4
* @brief      Tests: fpga_Perf_Events
* @details    Validates parse the evnts and format <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_4) {

	char sysfs_path[DFL_PERF_STR_MAX] = "/sys/bus/event_source/devices";

	EXPECT_EQ(fpga_Perf_Events(sysfs_path), FPGA_OK);
	EXPECT_EQ(fpga_Perf_Events(NULL), FPGA_INVALID_PARAM);
}
/**
* @test       fpgaperf_5
* @brief      Tests: parse_Perf_Event
* @details    Validates events values  <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_5) {	
	DIR *event_dir = NULL;

	char dir_name[DFL_PERF_STR_MAX] = "/sys/bus/event_source/devices/dfl_fme0";
	char event_name[DFL_BUFSIZ_MAX] = "";
	char *event_filter[] =  EVENT_FILTER;
	uint64_t size = 0;
	
	size = sizeof(event_filter) / sizeof(event_filter[0]);

	snprintf(event_name, sizeof(event_name), "%s/events", dir_name);
	event_dir = opendir(event_name);

	EXPECT_EQ(parse_Perf_Event(event_dir, event_filter, size, dir_name), FPGA_OK);
	EXPECT_EQ(parse_Perf_Event(NULL, event_filter, size, dir_name), FPGA_INVALID_PARAM);
	EXPECT_EQ(parse_Perf_Event(event_dir, event_filter, size, NULL), FPGA_INVALID_PARAM);	
}
/**
* @test fpgaperf_6
* @brief Tests: parse_Perf_Format
* @details    Validates format value <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_6) {	
	DIR *format_dir = NULL;

        char dir_name[DFL_PERF_STR_MAX] = "/sys/bus/event_source/devices/dfl_fme0";
	char format_name[DFL_BUFSIZ_MAX] = "";

	snprintf(format_name, sizeof(format_name), "%s/format", dir_name);
        format_dir = opendir(format_name);

	EXPECT_EQ(parse_Perf_Format(format_dir, dir_name), FPGA_OK);
	EXPECT_EQ(parse_Perf_Format(NULL, dir_name), FPGA_INVALID_PARAM);
	EXPECT_EQ(parse_Perf_Format(format_dir, NULL), FPGA_INVALID_PARAM);
}
/**
* @test       fpgaperf_7
* @brief      Tests: fpgaPerfCounterFree
* @details    Validates frees a memory <br>
*/
TEST_P(fpgaperf_counter_c_p, fpgaperf_7) {	

	EXPECT_EQ(fpgaPerfCounterFree(), FPGA_OK);
}

INSTANTIATE_TEST_CASE_P(fpgaperf_counter_c, fpgaperf_counter_c_p,
	::testing::ValuesIn(test_platform::hw_platforms({ "dfl-n3000","dfl-d5005" })));
