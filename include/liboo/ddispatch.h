#ifndef DDISPATCH_H
#define DDISPATCH_H

/*
 * Layout of the created dynamic dispatch table (vtable):
 *
 * Default layout:
 *
 * _ZTVNxyzE:
 *   <vtable slot 0> addr(first method)
 *   ...
 *   <vtable slot n> addr(last method)
 *
 * More complicated layouts are possible, use ddispatch_set_vtable_layout(..).
 * The resulting vtable will look like this:
 *
 * _ZTVNxyzE:
 *   0               uninitialized*
 *   0               uninitialized*
 *   <vtable slot 0> uninitialized*     <-- vtable_vptr_points_to_index (e.g., == 2)
 *   <vtable slot 1> uninitialized*
 *   <vtable slot 2> addr(first method) <-- vtable_index_of_first_method (e.g., == 4)
 *   ...
 *   <vtable slot n> addr(last method)
 *
 *   *) use callback function vtable_init_slots to set ir_initializer_t's
 *      for the uninitialized slots.
 */

#include <libfirm/firm.h>

typedef enum { bind_unknown, bind_static, bind_dynamic, bind_interface } ddispatch_binding;

typedef struct {
	ir_entity **vptr;
	int needs_vtable;
} oo_type_info;

typedef struct {
	int include_in_vtable;
	int is_abstract;
	ddispatch_binding binding;
} oo_entity_info;

typedef void     (*init_vtable_slots_t)           (ir_type* klass, ir_initializer_t *vtable_init, unsigned vtable_size);
typedef ir_node* (*construct_interface_lookup_t)  (ir_node *objptr, ir_type *iface, ir_entity *method, ir_graph *irg, ir_node *block, ir_node **mem);
typedef void     (*construct_runtime_classinfo_t) (ir_type* klass);

#define get_class_info(klass)   (oo_type_info*)   get_type_link(klass)
#define get_entity_info(entity) (oo_entity_info*) get_entity_link(entity)

void ddispatch_init(void);
void ddispatch_setup_vtable(ir_type *klass);
void ddispatch_lower_Call(ir_node* call);
void ddispatch_prepare_new_instance(ir_type* klass, ir_node *objptr, ir_graph *irg, ir_node *block, ir_node **mem);
void ddispatch_construct_runtime_classinfo(ir_type *klass);

void ddispatch_set_vtable_layout(unsigned vptr_points_to_index, unsigned index_of_first_method, init_vtable_slots_t func);
void ddispatch_set_interface_lookup_constructor(construct_interface_lookup_t func);
void ddispatch_set_abstract_method_ident(ident* ami);
void ddispatch_set_runtime_classinfo_constructor(construct_runtime_classinfo_t func);

#endif
