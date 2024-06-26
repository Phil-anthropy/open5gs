/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TEST_ESM_HANDLE_H
#define TEST_ESM_HANDLE_H

#ifdef __cplusplus
extern "C" {
#endif

void testesm_handle_esm_information_request(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_pdn_connectivity_reject(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_activate_default_eps_bearer_context_request(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_activate_dedicated_eps_bearer_context_request(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_modify_eps_bearer_context_request(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_deactivate_eps_bearer_context_request(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_bearer_resource_allocation(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);
void testesm_handle_bearer_resource_modification(
        test_ue_t *test_ue, ogs_nas_eps_message_t *message);

#ifdef __cplusplus
}
#endif

#endif /* TEST_ESM_HANDLE_H */
