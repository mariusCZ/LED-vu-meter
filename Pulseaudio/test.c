#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pulse/pulseaudio.h>


static pa_sample_spec ss;
int hist = 0;
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;


// This callback gets called when our context changes state.  We really only
// care about when it's ready or if it has failed
void pa_state_cb(pa_context *c, void *userdata) {
  pa_context_state_t state;
  int *pa_ready = userdata;
  state = pa_context_get_state(c);
  switch  (state) {
    // These are just here for reference
  case PA_CONTEXT_UNCONNECTED:
  case PA_CONTEXT_CONNECTING:
  case PA_CONTEXT_AUTHORIZING:
  case PA_CONTEXT_SETTING_NAME:
  default:
    break;
  case PA_CONTEXT_FAILED:
  case PA_CONTEXT_TERMINATED:
    *pa_ready = 2;
    break;
  case PA_CONTEXT_READY:
    *pa_ready = 1;
    break;
  }
}

// Function to send volume to socket
void sendVol(int v) {
  char numb[20];
  sprintf(numb, "%d", v);
  write(sockfd,numb,strlen(numb));
}

// Function to read the volume
static void stream_read_cb(pa_stream *s, size_t length, void *userdata) { 
  const void *data;
  char command[20], numb[2];
  double v;
  int k;
  if (pa_stream_peek(s, &data, &length) < 0) {
	printf("%s", "Shit not reading");
	return;
  }
  if (!data) {
	if (length)
		pa_stream_drop(s);
	return;
  }
  assert(length > 0);
  assert(length % sizeof(float) == 0);
  v = ((const float*) data)[length / sizeof(float) -1];
  k = (((float)v * 100) / (float)100) * 10;
  if (k != hist) {
	sendVol(k);
	printf("%i\n", k);
	hist = k; 
  }
  pa_stream_drop(s);
}

int main(int argc, char *argv[]) {
  pa_mainloop *pa_ml;
  pa_mainloop_api *pa_mlapi;
  pa_context *pa_ctx;
  pa_stream *recordstream;
  pa_stream_flags_t flags;
  int r;
  int pa_ready = 0;
  int retval = 0;
  unsigned int a;
  double amp;
  //Create a client connection to socket server
  portno = atoi("30000");
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server = gethostbyname("littlealtar");
  if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
       (char *)&serv_addr.sin_addr.s_addr,
       server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	printf("%s", "SHIT IS BROKEN DAWG");
  //-----
  // Create a mainloop API and connection to the default server
  pa_ml = pa_mainloop_new();
  pa_mlapi = pa_mainloop_get_api(pa_ml);
  pa_ctx = pa_context_new(pa_mlapi, "Peak Meter");
  pa_context_connect(pa_ctx, NULL, 0, NULL);

  // Set the record flags
  flags = (pa_stream_flags_t) (PA_STREAM_DONT_MOVE | PA_STREAM_PEAK_DETECT | PA_STREAM_ADJUST_LATENCY |
                               PA_STREAM_DONT_INHIBIT_AUTO_SUSPEND | PA_STREAM_NOFLAGS);

  // This function defines a callback so the server will tell us it's state.
  // Our callback will wait for the state to be ready.  The callback will
  // modify the variable to 1 so we know when we have a connection and it's
  // ready.
  // If there's an error, the callback will set pa_ready to 2
  pa_context_set_state_callback(pa_ctx, pa_state_cb, &pa_ready);

  // We can't do anything until PA is ready, so just iterate the mainloop
  // and continue

  while (pa_ready == 0) {
    printf("%s", "Fix yo shit");
    pa_mainloop_iterate(pa_ml, 1, NULL);
  }
  
  if (pa_ready == 2) {
    retval = -1;
    goto exit;
  }

  // Create a new stream
  ss.rate = 441;
  ss.channels = 2;
  ss.format = PA_SAMPLE_FLOAT32;
  recordstream = pa_stream_new(pa_ctx, "Record", &ss, NULL);
  if (!recordstream) {
    printf("pa_stream_new failed\n");
  }

  // Connect the stream to record and start reading volume
  pa_stream_set_read_callback(recordstream, stream_read_cb, NULL);
  r = pa_stream_connect_record(recordstream, NULL, NULL, flags);
  if (r < 0) {
    printf("pa_stream_connect_record failed\n");
    retval = -1;
    goto exit;
  }

  // Run the mainloop until pa_mainloop_quit() is called
  // (this example never calls it, so the mainloop runs forever).
  // printf("%s", "Running Loop");

  pa_mainloop_run(pa_ml, NULL);

exit:
  // clean up and disconnect
  pa_context_disconnect(pa_ctx);
  pa_context_unref(pa_ctx);
  pa_mainloop_free(pa_ml);
  return retval;
}