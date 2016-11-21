#undef TRACE_SYSTEM
#define TRACE_SYSTEM fs_dax

#if !defined(_TRACE_FS_DAX_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_FS_DAX_H

#include <linux/tracepoint.h>

DECLARE_EVENT_CLASS(dax_pmd_fault_class,
	TP_PROTO(struct vm_area_struct *vma, unsigned long address,
		unsigned int flags, pgoff_t pgoff, pgoff_t max_pgoff,
		int result),
	TP_ARGS(vma, address, flags, pgoff, max_pgoff, result),
	TP_STRUCT__entry(
		__field(unsigned long, vm_start)
		__field(unsigned long, vm_end)
		__field(unsigned long, vm_flags)
		__field(unsigned long, address)
		__field(unsigned int, flags)
		__field(pgoff_t, pgoff)
		__field(pgoff_t, max_pgoff)
		__field(int, result)
	),
	TP_fast_assign(
		__entry->vm_start = vma->vm_start;
		__entry->vm_end = vma->vm_end;
		__entry->vm_flags = vma->vm_flags;
		__entry->address = address;
		__entry->flags = flags;
		__entry->pgoff = pgoff;
		__entry->max_pgoff = max_pgoff;
		__entry->result = result;
	),
	TP_printk("%s mapping %s address %#lx vm_start %#lx vm_end %#lx "
		"pgoff %#lx max_pgoff %#lx %s",
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__entry->flags & FAULT_FLAG_WRITE ? "write" : "read",
		__entry->address,
		__entry->vm_start,
		__entry->vm_end,
		__entry->pgoff,
		__entry->max_pgoff,
		__print_flags(__entry->result, "|", VM_FAULT_RESULT_TRACE)
	)
)

#define DEFINE_PMD_FAULT_EVENT(name) \
DEFINE_EVENT(dax_pmd_fault_class, name, \
	TP_PROTO(struct vm_area_struct *vma, unsigned long address, \
		unsigned int flags, pgoff_t pgoff, pgoff_t max_pgoff, \
		int result), \
	TP_ARGS(vma, address, flags, pgoff, max_pgoff, result))

DEFINE_PMD_FAULT_EVENT(dax_pmd_fault);
DEFINE_PMD_FAULT_EVENT(dax_pmd_fault_done);

DECLARE_EVENT_CLASS(dax_pmd_load_hole_class,
	TP_PROTO(struct vm_area_struct *vma, unsigned long address,
		struct page *zero_page, void *radix_entry),
	TP_ARGS(vma, address, zero_page, radix_entry),
	TP_STRUCT__entry(
		__field(unsigned long, vm_flags)
		__field(unsigned long, address)
		__field(struct page *, zero_page)
		__field(void *, radix_entry)
	),
	TP_fast_assign(
		__entry->vm_flags = vma->vm_flags;
		__entry->address = address;
		__entry->zero_page = zero_page;
		__entry->radix_entry = radix_entry;
	),
	TP_printk("%s mapping read address %#lx zero_page %p radix_entry %#lx",
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__entry->address,
		__entry->zero_page,
		(unsigned long)__entry->radix_entry
	)
)

#define DEFINE_PMD_LOAD_HOLE_EVENT(name) \
DEFINE_EVENT(dax_pmd_load_hole_class, name, \
	TP_PROTO(struct vm_area_struct *vma, unsigned long address, \
		struct page *zero_page, void *radix_entry), \
	TP_ARGS(vma, address, zero_page, radix_entry))

DEFINE_PMD_LOAD_HOLE_EVENT(dax_pmd_load_hole);
DEFINE_PMD_LOAD_HOLE_EVENT(dax_pmd_load_hole_fallback);

#endif /* _TRACE_FS_DAX_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
