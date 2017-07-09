#include <pulse/pulseaudio.h>
#include <math.h>

#define factor 0.3
#define ledAmount 60.0

static pa_sample_spec ss;
int sockfd, portno, n;
char message [5];

pa_mainloop *pa_ml;
pa_mainloop_api *pa_mlapi;
pa_context *pa_ctx;
pa_stream *recordstream;
pa_stream_flags_t flags;


void sendVol(int v);
void connectSocket();
void runPulse();
void* decay();

