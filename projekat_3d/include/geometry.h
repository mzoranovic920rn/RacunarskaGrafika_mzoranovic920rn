#ifndef GEOMETRY_H
#define GEOMETRY_H
#define SPRAT_SEGMENTI 16
#define SPRAT_GORNJA_TEMENA (SPRAT_SEGMENTI * 3)
#define SPRAT_BOCNA_TEMENA (SPRAT_SEGMENTI * 6)
#define SPRAT_TEMENA (SPRAT_GORNJA_TEMENA + SPRAT_BOCNA_TEMENA)
#define SPRAT_BROJEVA (SPRAT_TEMENA * 6)
#define BROJ_CESTICA 60


#include <rafgl.h>

extern GLfloat postolje_vertices[180];
extern GLfloat kristal_vertices[144];
extern GLfloat sprat_vertices[SPRAT_BROJEVA];
extern GLfloat cestica_vertices[18];


void generisi_sprat(void);

#endif


