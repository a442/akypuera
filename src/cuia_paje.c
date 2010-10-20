#include <stdio.h>
#include <cuia.h>
#include <rastro.h>

static timestamp_t first_timestamp = -1;

static s_paje_event_t paje_events[] = {
  {"PajeDefineContainerType",
   "% Alias string\n"
   "% ContainerType string\n"
   "% Name string",
   -1},
  {"PajeDefineStateType",
   "% Alias string\n"
   "% ContainerType string\n"
   "% Name string",
   -1},
  {"PajeCreateContainer",
   "% Time string\n"
   "% Alias string\n"
   "% Type string\n"
   "% Container string\n"
   "% Name string",
   -1},
  {"PajeDestroyContainer",
   "% Time string\n"
   "% Type string\n"
   "% Container string",
   -1},
  {"PajeSetState",
   "% Time string\n"
   "% Container string\n"
   "% EntityType string\n"
   "% Value string",
   -1},
  {NULL, NULL, -1}
};

static int paje_event_id (const char *name)
{
  int i;
  for (i = 0; paje_events[i].name; i++)
    if (strcmp (name, paje_events[i].name) == 0)
      return paje_events[i].id;
  return -1;
}

static timestamp_t paje_event_timestamp (timestamp_t timestamp)
{
  if (first_timestamp == -1){
    first_timestamp = timestamp;
  }
  return timestamp - first_timestamp;
}

void pajeDefineContainerType (const char *alias,
    const char *containerType,
    const char *name)
{
  printf ("%d %s %s %s\n",
    paje_event_id ("PajeDefineContainerType"),
    alias, containerType, name);
}

void pajeDefineStateType (const char *alias,
    const char *containerType,
    const char *name)
{
  printf ("%d %s %s %s\n",
    paje_event_id ("PajeDefineStateType"),
    alias, containerType, name);
}

void pajeCreateContainer (timestamp_t timestamp,
    const char *alias,
    const char *type,
    const char *container,
    const char *name)
{
  printf ("%d %lld %s %s %s %s\n",
      paje_event_id ("PajeCreateContainer"),
      paje_event_timestamp (timestamp),
      alias, type, container, name);
}

void pajeDestroyContainer (timestamp_t timestamp,
    const char *type,
    const char *container)
{
  printf ("%d %lld %s %s\n",
      paje_event_id ("PajeDestroyContainer"),
      paje_event_timestamp (timestamp),
      type, container);
}

void pajeSetState (timestamp_t timestamp,
    const char *container,
    const char *type,
    const char *value)
{
  printf ("%d %lld %s %s %s\n",
      paje_event_id ("PajeSetState"),
      paje_event_timestamp (timestamp),
      container, type, value);
}

void paje_header (void)
{
  int i;
  for (i = 0; paje_events[i].name; i++){
    paje_events[i].id = i;
    printf ("%%EventDef %s %d\n%s\n%%EndEventDef\n",
       paje_events[i].name, paje_events[i].id, paje_events[i].description);
  }
}

void paje_hierarchy (void)
{
  pajeDefineContainerType ("PROCESS", "0", "PROCESS");
  pajeDefineStateType ("STATE", "PROCESS", "STATE");
}
