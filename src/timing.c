#include "timing.h"
#include "types.h"

timing_t timing_init (void) {
    return (timing_t) {
        .dt = {
            .frame = 0.0000000000001,
        }
    };
}
