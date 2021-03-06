#include <stdbool.h>
#include "../adt/error.h"
#include "rt.h"

bool oo_rt_instanceof(const class_info_t *objclass,
                      const class_info_t *refclass)
{
	if (objclass == refclass)
		return true;

	if (objclass->superclass && oo_rt_instanceof(objclass->superclass, refclass))
		return true;

	if (objclass->n_interfaces > 0) {
		for (uint32_t i = 0; i < objclass->n_interfaces; i++) {
			class_info_t *ci = objclass->interfaces[i];
			if (oo_rt_instanceof(ci, refclass))
				return true;
		}
	}

	return false;
}
