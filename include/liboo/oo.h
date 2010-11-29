#ifndef OO_H
#define OO_H

/*
 * Aggregate header file for liboo.
 */

#include <liboo/ddispatch.h>
#include <liboo/dmemory.h>
#include <liboo/mangle.h>
#include <liboo/rtti.h>
#include <libfirm/firm.h>

void oo_init(void);
void oo_deinit(void);
void lower_oo(void);

int   get_class_needs_vtable(ir_type *classtype);
void  set_class_needs_vtable(ir_type *classtype, int needs_vtable);
ir_entity **get_class_vptr_entity_ptr(ir_type *classtype);
void  set_class_vptr_entity_ptr(ir_type *classtype, ir_entity **vptr);
void *get_oo_type_link(ir_type *type);
void  set_oo_type_link(ir_type *type, void* link);
int   get_method_include_in_vtable(ir_entity *method);
void  set_method_include_in_vtable(ir_entity *method, int include_in_vtable);
int   get_method_is_abstract(ir_entity *method);
void  set_method_is_abstract(ir_entity *method, int is_abstract);
ddispatch_binding get_method_binding(ir_entity *method);
void  set_method_binding(ir_entity *method, ddispatch_binding binding);
void *get_oo_entity_link(ir_entity *entity);
void  set_oo_entity_link(ir_entity *entity, void* link);

#endif