#include "geometry.h"
#include <math.h>

GLfloat sprat_vertices[SPRAT_BROJEVA];

// Postolje - svetske koordinate, stoji na podu (y od -1.0 do -0.5), kod zadnjeg zida (z oko 3)
GLfloat postolje_vertices[] = {
    // gornja strana (y = -0.5)
    -0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

    -0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

    // prednja strana (z = 2.4)
    -0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,

    -0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,

    // zadnja strana (z = 3.6)
    -0.6f, -1.0f, 3.6f,  0.4f, 0.4f, 0.45f,
     0.6f, -1.0f, 3.6f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

    -0.6f, -1.0f, 3.6f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

    // leva strana (x = -0.6)
    -0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
    -0.6f, -1.0f, 3.6f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

    -0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,
    -0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f,

    // desna strana (x = 0.6)
     0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -1.0f, 3.6f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,

     0.6f, -1.0f, 2.4f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 3.6f,  0.4f, 0.4f, 0.45f,
     0.6f, -0.5f, 2.4f,  0.4f, 0.4f, 0.45f
};

// Kristal - LOKALNE koordinate, centriran oko (0,0,0). Dve piramide spojene na osnovi (y=0).
GLfloat kristal_vertices[] = {
    // gornja piramida (vrh na y = 0.8)
     0.0f,  0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,

     0.0f,  0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,

     0.0f,  0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,

     0.0f,  0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,

    // donja piramida (vrh na y = -0.8)
     0.0f, -0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,

     0.0f, -0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,

     0.0f, -0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f, -0.5f,  0.4f, 0.75f, 0.9f,

     0.0f, -0.8f,  0.0f,  0.4f, 0.75f, 0.9f,
     0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,
    -0.5f,  0.0f,  0.5f,  0.4f, 0.75f, 0.9f,
};

void generisi_sprat(void)
{
    float radijus = 0.4f;
    float y_gore = -0.4f;
    float y_dole = -0.5f;
    float cx = 0.0f, cz = 3.0f;
    float r = 0.75f, g = 0.65f, b = 0.3f;
    float r2 = 0.55f, g2 = 0.45f, b2 = 0.2f;
    int i;

    for (i = 0; i < SPRAT_SEGMENTI; i++)
    {
        float ugao1 = i * (2.0f * 3.14159265f / SPRAT_SEGMENTI);
        float ugao2 = (i + 1) * (2.0f * 3.14159265f / SPRAT_SEGMENTI);
        float x1 = cx + radijus * cosf(ugao1);
        float z1 = cz + radijus * sinf(ugao1);
        float x2 = cx + radijus * cosf(ugao2);
        float z2 = cz + radijus * sinf(ugao2);

        int base = i * 18;

        sprat_vertices[base + 0] = cx;
        sprat_vertices[base + 1] = y_gore;
        sprat_vertices[base + 2] = cz;
        sprat_vertices[base + 3] = r;
        sprat_vertices[base + 4] = g;
        sprat_vertices[base + 5] = b;

        sprat_vertices[base + 6] = x1;
        sprat_vertices[base + 7] = y_gore;
        sprat_vertices[base + 8] = z1;
        sprat_vertices[base + 9] = r;
        sprat_vertices[base + 10] = g;
        sprat_vertices[base + 11] = b;

        sprat_vertices[base + 12] = x2;
        sprat_vertices[base + 13] = y_gore;
        sprat_vertices[base + 14] = z2;
        sprat_vertices[base + 15] = r;
        sprat_vertices[base + 16] = g;
        sprat_vertices[base + 17] = b;
    }

    int pocetak_bocnog = SPRAT_GORNJA_TEMENA * 6;

    for (i = 0; i < SPRAT_SEGMENTI; i++)
    {
        float ugao1 = i * (2.0f * 3.14159265f / SPRAT_SEGMENTI);
        float ugao2 = (i + 1) * (2.0f * 3.14159265f / SPRAT_SEGMENTI);
        float x1 = cx + radijus * cosf(ugao1);
        float z1 = cz + radijus * sinf(ugao1);
        float x2 = cx + radijus * cosf(ugao2);
        float z2 = cz + radijus * sinf(ugao2);

        int base = pocetak_bocnog + i * 36;

        sprat_vertices[base + 0] = x1;  sprat_vertices[base + 1] = y_gore; sprat_vertices[base + 2] = z1;
        sprat_vertices[base + 3] = r2;  sprat_vertices[base + 4] = g2;     sprat_vertices[base + 5] = b2;

        sprat_vertices[base + 6] = x2;  sprat_vertices[base + 7] = y_gore; sprat_vertices[base + 8] = z2;
        sprat_vertices[base + 9] = r2;  sprat_vertices[base + 10] = g2;    sprat_vertices[base + 11] = b2;

        sprat_vertices[base + 12] = x2; sprat_vertices[base + 13] = y_dole; sprat_vertices[base + 14] = z2;
        sprat_vertices[base + 15] = r2; sprat_vertices[base + 16] = g2;     sprat_vertices[base + 17] = b2;

        sprat_vertices[base + 18] = x1; sprat_vertices[base + 19] = y_gore; sprat_vertices[base + 20] = z1;
        sprat_vertices[base + 21] = r2; sprat_vertices[base + 22] = g2;     sprat_vertices[base + 23] = b2;

        sprat_vertices[base + 24] = x2; sprat_vertices[base + 25] = y_dole; sprat_vertices[base + 26] = z2;
        sprat_vertices[base + 27] = r2; sprat_vertices[base + 28] = g2;     sprat_vertices[base + 29] = b2;

        sprat_vertices[base + 30] = x1; sprat_vertices[base + 31] = y_dole; sprat_vertices[base + 32] = z1;
        sprat_vertices[base + 33] = r2; sprat_vertices[base + 34] = g2;     sprat_vertices[base + 35] = b2;
    }
}

GLfloat cestica_vertices[18] =
{
    0.0f,  0.05f, 0.0f,   1.0f, 0.85f, 0.4f,
   -0.04f, -0.03f, 0.0f,  1.0f, 0.85f, 0.4f,
    0.04f, -0.03f, 0.0f,  1.0f, 0.85f, 0.4f,
};
