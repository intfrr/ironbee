/*****************************************************************************
 * Licensed to Qualys, Inc. (QUALYS) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * QUALYS licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef _IB_UTIL_PRIVATE_H_
#define _IB_UTIL_PRIVATE_H_

/**
 * @file
 * @brief IronBee - Private Utility Declarations
 *
 * @author Brian Rectanus <brectanus@qualys.com>
 */

#include <apr_lib.h>
#include <apr_hash.h>

#include <ironbee/util.h>

/**
 * @internal
 * Memory pool structure.
 */
struct ib_mpool_t {
    apr_pool_t        *pool;          /**< The real pool handle */
};

/**
 * @internal
 * Dynamic Shared Object (DSO) structure.
 */
struct ib_dso_t {
    ib_mpool_t        *mp;            /**< Memory pool */
    void              *handle;        /**< Real DSO handle */
};

/**
 * @internal
 * Hashtable structure.
 */
struct ib_hash_t {
    ib_mpool_t        *mp;            /**< Memory pool */
    apr_hash_t        *data;          /**< The real hash table */
};

/**
 * @internal
 * Field value structure.
 *
 * This allows for multiple types of values to be stored within a field.
 */
struct ib_field_val_t {
    ib_field_get_fn_t  fn_get;        /**< Function to get a value. */
#if 0
    ib_field_set_fn_t  fn_set;        /**< Function to set a value. */
    ib_field_rset_fn_t fn_rset;       /**< Function to set a relative value. */
#endif
    void              *fndata;        /**< Data passed to function calls. */
    void               *pval;         /**< Address where value is stored */
    union {
        ib_num_t       num;           /**< Generic numeric value */
        ib_unum_t      unum;          /**< Generic unsigned numeric value */
        ib_bytestr_t  *bytestr;       /**< Byte string value */
        char          *nulstr;        /**< NUL string value */
        ib_list_t     *list;          /**< List of fields */
        void          *ptr;           /**< Pointer value */
    } u;
};

/**
 * @internal
 * Dynamic array structure.
 */
struct ib_array_t {
    ib_mpool_t       *mp;
    size_t            ninit;
    size_t            nextents;
    size_t            nelts;
    size_t            size;
    void             *extents;
};

/**
 * @internal
 * Calculate the extent index from the array index for an array.
 *
 * @param arr Array
 * @param idx Array index
 *
 * @returns Extent index where data resides
 */
#define IB_ARRAY_EXTENT_INDEX(arr,idx) ((idx) / (arr)->ninit)

/**
 * @internal
 * Calculate the data index from the array and extent indexes for an array.
 *
 * @param arr Array
 * @param idx Array index
 * @param extent_idx Extent index (via @ref IB_ARRAY_EXTENT_INDEX)
 *
 * @returns Data index where data resides within the given extent
 */
#define IB_ARRAY_DATA_INDEX(arr,idx,extent_idx) ((idx) - ((extent_idx) * (arr)->ninit))

/**
 * @internal
 * List node structure.
 */
struct ib_list_node_t {
    IB_LIST_NODE_REQ_FIELDS(ib_list_node_t);  /* Required fields */
    void              *data;                  /**< Node data */
};

/**
 * @internal
 * List structure.
 */
struct ib_list_t {
    ib_mpool_t       *mp;
    IB_LIST_REQ_FIELDS(ib_list_node_t);       /* Required fields */
};

#endif /* IB_UTIL_PRIVATE_H_ */

