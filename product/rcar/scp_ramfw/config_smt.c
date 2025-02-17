/*
 * Renesas SCP/MCP Software
 * Copyright (c) 2020-2022, Renesas Electronics Corporation. All rights
 * reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <config_power_domain.h>
#include <rcar_core.h>
#include <rcar_mfismh.h>
#include <rcar_scmi.h>
#include <software_mmap.h>

#include <mod_power_domain.h>
#include <mod_smt.h>
#include <mod_rcar_pd_sysc.h>

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>

#include <stdint.h>

static const struct fwk_element smt_element_table[] = {
    /* RCAR_SCMI_SERVICE_IDX_PSCI */
    { .name = "PSCI",
      .data = &((struct mod_smt_channel_config){
          .type = MOD_SMT_CHANNEL_TYPE_COMPLETER,
          .policies = MOD_SMT_POLICY_INIT_MAILBOX | MOD_SMT_POLICY_SECURE,
          .mailbox_address = (uintptr_t)SCMI_PAYLOAD_S_A2P_BASE,
          .mailbox_size = SCMI_PAYLOAD_SIZE,
          .driver_id = FWK_ID_SUB_ELEMENT_INIT(
              FWK_MODULE_IDX_RCAR_MFISMH,
              RCAR_MFISMH_DEVICE_IDX_S,
              0),
          .driver_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_RCAR_MFISMH, 0),
      }) },
    /* RCAR_SCMI_SERVICE_IDX_OSPM */
    { .name = "OSPM",
      .data = &((struct mod_smt_channel_config){
          .type = MOD_SMT_CHANNEL_TYPE_COMPLETER,
          .policies = MOD_SMT_POLICY_INIT_MAILBOX,
          .mailbox_address = (uintptr_t)SCMI_PAYLOAD0_NS_A2P_BASE,
          .mailbox_size = SCMI_PAYLOAD_SIZE,
          .driver_id = FWK_ID_SUB_ELEMENT_INIT(
              FWK_MODULE_IDX_RCAR_MFISMH,
              RCAR_MFISMH_DEVICE_IDX_NS_1,
              0),
          .driver_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_RCAR_MFISMH, 0),
      }) },
    /* RCAR_SCMI_SERVICE_IDX_VMM */
    { .name = "VMM",
      .data = &((struct mod_smt_channel_config){
          .type = MOD_SMT_CHANNEL_TYPE_COMPLETER,
          .policies = MOD_SMT_POLICY_INIT_MAILBOX,
          .mailbox_address = (uintptr_t)SCMI_PAYLOAD0_NS_A2P_VMM,
          .mailbox_size = SCMI_PAYLOAD_SIZE,
          .driver_id = FWK_ID_SUB_ELEMENT_INIT(
              FWK_MODULE_IDX_RCAR_MFISMH,
              RCAR_MFISMH_DEVICE_IDX_NS_2,
              0),
          .driver_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_RCAR_MFISMH, 0),
      }) },
    /* RCAR_SCMI_SERVICE_IDX_VM1 */
    { .name = "VM1",
      .data = &((struct mod_smt_channel_config){
          .type = MOD_SMT_CHANNEL_TYPE_COMPLETER,
          .policies = MOD_SMT_POLICY_INIT_MAILBOX,
          .mailbox_address = (uintptr_t)SCMI_PAYLOAD0_NS_A2P_VM1,
          .mailbox_size = SCMI_PAYLOAD_SIZE,
          .driver_id = FWK_ID_SUB_ELEMENT_INIT(
              FWK_MODULE_IDX_RCAR_MFISMH,
              RCAR_MFISMH_DEVICE_IDX_NS_3,
              0),
          .driver_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_RCAR_MFISMH, 0),
      }) },
    /* RCAR_SCMI_SERVICE_IDX_VM2 */
    { .name = "VM2",
      .data = &((struct mod_smt_channel_config){
          .type = MOD_SMT_CHANNEL_TYPE_COMPLETER,
          .policies = MOD_SMT_POLICY_INIT_MAILBOX,
          .mailbox_address = (uintptr_t)SCMI_PAYLOAD0_NS_A2P_VM2,
          .mailbox_size = SCMI_PAYLOAD_SIZE,
          .driver_id = FWK_ID_SUB_ELEMENT_INIT(
              FWK_MODULE_IDX_RCAR_MFISMH,
              RCAR_MFISMH_DEVICE_IDX_NS_4,
              0),
          .driver_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_RCAR_MFISMH, 0),
      }) },
    [RCAR_SCMI_SERVICE_IDX_COUNT] = { 0 },
};

static const struct fwk_element *smt_get_element_table(fwk_id_t module_id)
{
    unsigned int idx;
    struct mod_smt_channel_config *config;

    for (idx = 0; idx < RCAR_SCMI_SERVICE_IDX_COUNT; idx++) {
        config = (struct mod_smt_channel_config *)(smt_element_table[idx].data);
        config->pd_source_id = (fwk_id_t)FWK_ID_ELEMENT_INIT(
            FWK_MODULE_IDX_POWER_DOMAIN,
            CONFIG_POWER_DOMAIN_CHILD_ALWAYS_ON
            + rcar_core_get_count() + rcar_cluster_get_count());
    }

    return smt_element_table;
}

struct fwk_module_config config_smt = {
    .elements = FWK_MODULE_DYNAMIC_ELEMENTS(smt_get_element_table),
};
