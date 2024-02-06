#ifndef EXTERN_GUARDIAN
#define EXTERN_GUARDIAN

extern int planes_count; // All planes count
extern int planes_active; // Count exclude free cells
extern int planes_id[]; // Only IDs for quick operation about them
extern int planes_current_free_id; // First free id in queue
extern plane planes_arr[]; // Base plane array

#endif