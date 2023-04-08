#ifndef __DEVICETREE_H__
#define __DEVICETREE_H__

#include "devicetree_generated.h"

#define DT_PRIMITIVE_CAT(a, ...) a##__VA_ARGS__
#define DT_CAT(a, ...) DT_PRIMITIVE_CAT(a, __VA_ARGS__)

/**
 * @brief Get a node identifier for an instance of a compatible
 *
 * Nodes whose `compatible` property has multiple values are assigned
 * independent instance numbers for each compatible.
 *
 * @param inst instance number for compatible @p compat
 * @param compat lowercase-and-underscores compatible, without quotes
 * @return node identifier for the node with that instance number and
 *         compatible
 */
#define DT_INST(inst, compat) DT_CAT(DT_INST_ ## inst ## _,  compat)

/**
 * @brief Get a `DT_DRV_COMPAT` instance property
 * @param inst instance number
 * @param prop lowercase-and-underscores property name
 * @return a representation of the property's value
 */
#define DT_INST_PROP(inst, prop) DT_CAT(DT_INST(inst, DT_DRV_COMPAT), _P_ ## prop)

/**
 * @brief Get the number of instances of a given compatible with
 *        status `okay`
 * @return Number of instances with status `okay`
 */
#define DT_NUM_INST_STATUS_OKAY()	DT_CAT(DT_CAT(DT_INST_, DT_DRV_COMPAT), _NUM_INSTANCES)

/**
 * @brief Call @p fn on all nodes with compatible `DT_DRV_COMPAT`
 *        and status `okay`
 *
 * Example usage:
 *
 * @code{.c}
 *     #define DT_DRV_COMPAT vnd_device
 *     #define MY_FN(inst) DT_INST_PROP(inst, foobar),
 *
 *     DT_INST_FOREACH_STATUS_OKAY(MY_FN)
 * @endcode
 *
 * This expands to:
 *
 * @code{.c}
 *     MY_FN(0) MY_FN(1)
 * @endcode
 *
 * and from there, to either this:
 *
 *     "DEV_A", "DEV_B",
 *
 * or this:
 *
 *     "DEV_B", "DEV_A",
 *
 * No guarantees are made about the order that a and b appear in the
 * expansion.
 *
 * Note that @p fn is responsible for adding commas, semicolons, or
 * other separators or terminators.
 *
 * Device drivers should use this macro whenever possible to
 * instantiate a struct device for each enabled node in the devicetree
 * of the driver's compatible `DT_DRV_COMPAT`.
 *
 * @param fn Macro to call for each enabled node. Must accept an
 *           instance number as its only parameter.
 */
#define DT_INST_FOREACH_STATUS_OKAY(fn) DT_CAT(DT_FOREACH_OKAY_INST_, DT_DRV_COMPAT)(fn)

#endif // __DEVICETREE_H__