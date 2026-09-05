#include <camera.h>
#include <main_state.h>
#include <glad/glad.h>
#include <math.h>

#include <rafgl.h>
#include <game_constants.h>
#include "geometry.h"

static GLfloat pod_vertices[] =
{
    -5, -1, -5,     0.5, 0.35, 0.2,
     5, -1, -5,     0.5, 0.35, 0.2,
     5, -1,  5,     0.5, 0.35, 0.2,

     5, -1,  5,     0.5, 0.35, 0.2,
    -5, -1,  5,     0.5, 0.35, 0.2,
    -5, -1, -5,     0.5, 0.35, 0.2,
}; //Da zamenim z umesto 5 da ide na 9

static GLfloat levi_zid_vertices[] =
{
    5, -1, -5,     0.7, 0.7, 0.7,
    5, -1,  5,     0.7, 0.7, 0.7,
    5,  3,  5,     0.7, 0.7, 0.7,

    5,  3,  5,     0.7, 0.7, 0.7,
    5,  3, -5,     0.7, 0.7, 0.7,
    5, -1, -5,     0.7, 0.7, 0.7,
};


static GLfloat desni_zid_vertices[] =
{
    -5, -1, -5,     0.7, 0.7, 0.7,
    -5, -1,  5,     0.7, 0.7, 0.7,
    -5,  3,  5,     0.7, 0.7, 0.7,

    -5,  3,  5,     0.7, 0.7, 0.7,
    -5,  3, -5,     0.7, 0.7, 0.7,
    -5, -1, -5,     0.7, 0.7, 0.7,
};

static GLfloat zadnji_zid_vertices[] =
{
    -5, -1, 5,     0.7, 0.7, 0.7,
     5, -1, 5,     0.7, 0.7, 0.7,
     5,  3, 5,     0.7, 0.7, 0.7,

     5,  3, 5,     0.7, 0.7, 0.7,
    -5,  3, 5,     0.7, 0.7, 0.7,
    -5, -1, 5,     0.7, 0.7, 0.7,
};

static GLfloat prednji_zid_vertices[] =
{
    -5, -1, -5,     0.7, 0.7, 0.7,
     5, -1, -5,     0.7, 0.7, 0.7,
     5,  3, -5,     0.7, 0.7, 0.7,
     5,  3, -5,     0.7, 0.7, 0.7,
    -5,  3, -5,     0.7, 0.7, 0.7,
    -5, -1, -5,     0.7, 0.7, 0.7,
};



static GLfloat plocica_vertices[] =
{
	-0.45f, -0.63f, 2.39f,       1.0f, 0.0f,
	 0.45f, -0.63f, 2.39f,       0.0f, 0.0f,
	 0.45f, -0.87f, 2.39f,       0.0f, 1.0f,
	-0.45f, -0.63f, 2.39f,       1.0f, 0.0f,
	 0.45f, -0.87f, 2.39f,       0.0f, 1.0f,
	-0.45f, -0.87f, 2.39f,       1.0f, 1.0f,
};


static GLfloat valjak_vertices[] =
{
    // GORNJI POKLOPAC
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.3500f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.4500f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.4500f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    2.6500f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.6500f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -2.1500f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -2.1500f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.3500f, 0.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,

    // BOCNE STRANE
    3.3500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.2475f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,
    3.3500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,
    3.3500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,

    3.2475f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.0000f, -1.0000f, -1.4500f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.4500f,   0.15f, 0.65f, 0.55f,
    3.2475f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.4500f,   0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,

    3.0000f, -1.0000f, -1.4500f,  0.15f, 0.65f, 0.55f,
    2.7525f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,
    3.0000f, -1.0000f, -1.4500f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -1.4500f,   0.15f, 0.65f, 0.55f,

    2.7525f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    2.6500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.6500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,
    2.7525f, -1.0000f, -1.5525f,  0.15f, 0.65f, 0.55f,
    2.6500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -1.5525f,   0.15f, 0.65f, 0.55f,

    2.6500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.7525f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,
    2.6500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,
    2.6500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,

    2.7525f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.0000f, -1.0000f, -2.1500f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -2.1500f,   0.15f, 0.65f, 0.55f,
    2.7525f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -2.1500f,   0.15f, 0.65f, 0.55f,
    2.7525f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,

    3.0000f, -1.0000f, -2.1500f,  0.15f, 0.65f, 0.55f,
    3.2475f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,
    3.0000f, -1.0000f, -2.1500f,  0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,
    3.0000f, 0.0000f, -2.1500f,   0.15f, 0.65f, 0.55f,

    3.2475f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.3500f, -1.0000f, -1.8000f,  0.15f, 0.65f, 0.55f,
    3.3500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,
    3.2475f, -1.0000f, -2.0475f,  0.15f, 0.65f, 0.55f,
    3.3500f, 0.0000f, -1.8000f,   0.15f, 0.65f, 0.55f,
    3.2475f, 0.0000f, -2.0475f,   0.15f, 0.65f, 0.55f,
};

static GLfloat kupa_vertices[] =
{
    3.2500f, -1.0000f, -0.5000f,  0.85f, 0.25f, 0.15f,
    3.0596f, -1.0000f, -0.0404f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    3.0596f, -1.0000f, -0.0404f,  0.85f, 0.25f, 0.15f,
    2.6000f, -1.0000f, 0.1500f,   0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    2.6000f, -1.0000f, 0.1500f,   0.85f, 0.25f, 0.15f,
    2.1404f, -1.0000f, -0.0404f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    2.1404f, -1.0000f, -0.0404f,  0.85f, 0.25f, 0.15f,
    1.9500f, -1.0000f, -0.5000f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    1.9500f, -1.0000f, -0.5000f,  0.85f, 0.25f, 0.15f,
    2.1404f, -1.0000f, -0.9596f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    2.1404f, -1.0000f, -0.9596f,  0.85f, 0.25f, 0.15f,
    2.6000f, -1.0000f, -1.1500f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    2.6000f, -1.0000f, -1.1500f,  0.85f, 0.25f, 0.15f,
    3.0596f, -1.0000f, -0.9596f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
    3.0596f, -1.0000f, -0.9596f,  0.85f, 0.25f, 0.15f,
    3.2500f, -1.0000f, -0.5000f,  0.85f, 0.25f, 0.15f,
    2.6000f, 0.7000f, -0.5000f,   0.85f, 0.25f, 0.15f,
};

static GLfloat kutija1_vertices[] =
{
    1.5f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -1.0f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    1.5f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -1.0f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -1.0f, 1.1f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.9f,  0.8f, 0.1f, 0.35f,
    2.3f, -0.4f, 1.1f,  0.8f, 0.1f, 0.35f,
};
static GLfloat kutija2_vertices[] =
{
    1.8f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, -0.4f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    1.8f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, -0.4f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, -0.4f, 1.15f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.65f,  0.95f, 0.5f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.95f, 0.5f, 0.1f,
};
static GLfloat kutija3_vertices[] =
{
    2.0f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.0f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.0f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.0f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.0f, 1.15f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.45f,  0.9f, 0.75f, 0.1f,
    2.3f, 0.25f, 1.15f,  0.9f, 0.75f, 0.1f,
};


static GLuint vao, vbo, shader_program_id, uni_M, uni_VP;
static GLuint uni_normal, uni_light_dir;
static GLuint levi_zid_vao, levi_zid_vbo;
static GLuint desni_zid_vao, desni_zid_vbo;
static GLuint zadnji_zid_vao, zadnji_zid_vbo;
static GLuint postolje_vao, postolje_vbo;
static GLuint kristal_vao, kristal_vbo;
static GLuint sprat_vao, sprat_vbo;
static GLuint uni_pod_sara;
GLuint cestica_vao, cestica_vbo;
GLuint prednji_zid_vao, prednji_zid_vbo;
GLuint uni_zid_sara;
GLuint plocica_vao, plocica_vbo;


GLuint kutija1_vao, kutija1_vbo;
GLuint kutija2_vao, kutija2_vbo;


GLuint kutija3_vao, kutija3_vbo;
GLuint kupa_vao, kupa_vbo;
GLuint valjak_vao, valjak_vbo;

rafgl_raster_t plocica_raster;
rafgl_texture_t plocica_tekstura;

GLuint plocica_shader_program_id;
GLint uni_plocica_M, uni_plocica_VP, uni_plocica_tekstura_loc;

//za post-procesing za vinjetu
rafgl_framebuffer_simple_t scena_fbo;
GLuint kvadrat_vao, kvadrat_vbo;
GLuint post_shader_program_id, uni_scena_tekstura, uni_jacina_vinjete;


//za zrnastu strukturu
rafgl_framebuffer_simple_t fbo_posle_vinjete;
GLuint zrno_shader_program_id, uni_zrno_scena_tekstura, uni_vreme, uni_jacina_zrna;

static float total_time = 0.0f;

mat4_t model;

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    camera_init();

    shader_program_id = rafgl_program_create_from_name("second_shader");
    uni_M = glGetUniformLocation(shader_program_id, "uni_M");
    uni_VP = glGetUniformLocation(shader_program_id, "uni_VP");

    uni_normal = glGetUniformLocation(shader_program_id, "uni_normal");
    uni_light_dir = glGetUniformLocation(shader_program_id, "uni_light_dir");

    uni_pod_sara = glGetUniformLocation(shader_program_id, "uni_pod_sara");

    uni_zid_sara = glGetUniformLocation(shader_program_id, "uni_zid_sara");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pod_vertices), pod_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

    model = m4_identity();

    //za levi zid
    glGenVertexArrays(1, &levi_zid_vao);
    glGenBuffers(1, &levi_zid_vbo);

    glBindVertexArray(levi_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, levi_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(levi_zid_vertices), levi_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //za desni zid

    glGenVertexArrays(1, &desni_zid_vao);
    glGenBuffers(1, &desni_zid_vbo);

    glBindVertexArray(desni_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, desni_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(desni_zid_vertices), desni_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //zadnji zid


    glGenVertexArrays(1, &zadnji_zid_vao);
    glGenBuffers(1, &zadnji_zid_vbo);

    glBindVertexArray(zadnji_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, zadnji_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(zadnji_zid_vertices), zadnji_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);




        //za postolje
    glGenVertexArrays(1, &postolje_vao);
    glGenBuffers(1, &postolje_vbo);
    glBindVertexArray(postolje_vao);
    glBindBuffer(GL_ARRAY_BUFFER, postolje_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(postolje_vertices), postolje_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //za kristal
    glGenVertexArrays(1, &kristal_vao);
    glGenBuffers(1, &kristal_vbo);
    glBindVertexArray(kristal_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kristal_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kristal_vertices), kristal_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    generisi_sprat();

    glGenVertexArrays(1, &sprat_vao);
    glGenBuffers(1, &sprat_vbo);
    glBindVertexArray(sprat_vao);
    glBindBuffer(GL_ARRAY_BUFFER, sprat_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprat_vertices), sprat_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //cestice
    glGenVertexArrays(1, &cestica_vao);
    glGenBuffers(1, &cestica_vbo);
    glBindVertexArray(cestica_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cestica_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cestica_vertices), cestica_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //poslednji zid
    glGenVertexArrays(1, &prednji_zid_vao);
    glGenBuffers(1, &prednji_zid_vbo);
    glBindVertexArray(prednji_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, prednji_zid_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(prednji_zid_vertices), prednji_zid_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);



    //post-procesing
    scena_fbo = rafgl_framebuffer_simple_create(width, height);

    GLfloat kvadrat_vertices[] =
    {
        /* pozicija (x,y) */  /* uv (u,v) */
        -1.0f, -1.0f,          0.0f, 0.0f,
        1.0f, -1.0f,          1.0f, 0.0f,
        1.0f,  1.0f,          1.0f, 1.0f,

        1.0f,  1.0f,          1.0f, 1.0f,
        -1.0f,  1.0f,          0.0f, 1.0f,
        -1.0f, -1.0f,          0.0f, 0.0f,
    };

    glGenVertexArrays(1, &kvadrat_vao);
    glGenBuffers(1, &kvadrat_vbo);
    glBindVertexArray(kvadrat_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kvadrat_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kvadrat_vertices), kvadrat_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    post_shader_program_id = rafgl_program_create_from_name("post_shader");
    uni_scena_tekstura = glGetUniformLocation(post_shader_program_id, "uni_scena_tekstura");
    uni_jacina_vinjete = glGetUniformLocation(post_shader_program_id, "uni_jacina_vinjete");

    //za jos jedan post-processing efekat
    fbo_posle_vinjete = rafgl_framebuffer_simple_create(width, height);

    zrno_shader_program_id = rafgl_program_create_from_name("zrno_shader");
    uni_zrno_scena_tekstura = glGetUniformLocation(zrno_shader_program_id, "uni_scena_tekstura");
    uni_vreme = glGetUniformLocation(zrno_shader_program_id, "uni_vreme");
    uni_jacina_zrna = glGetUniformLocation(zrno_shader_program_id, "uni_jacina_zrna");



    //za gui
    rafgl_raster_init(&plocica_raster, 420, 110);
    for (int py = 0; py < plocica_raster.height; py++)
    {
        for (int px = 0; px < plocica_raster.width; px++)
        {
            plocica_raster.data[py * plocica_raster.width + px].rgba = rafgl_RGB(235, 228, 210);
        }
    }


    int ukupno_piksela = plocica_raster.width * plocica_raster.height;
    for (int i = 0; i < ukupno_piksela / 2; i++)
    {
        rafgl_pixel_rgb_t tmp = plocica_raster.data[i];
        plocica_raster.data[i] = plocica_raster.data[ukupno_piksela - 1 - i];
        plocica_raster.data[ukupno_piksela - 1 - i] = tmp;
    }

    rafgl_raster_draw_string(&plocica_raster, "KRISTAL", 15, 10, rafgl_RGB(40, 35, 25), 2);

    rafgl_texture_init(&plocica_tekstura);
    rafgl_texture_load_from_raster(&plocica_tekstura, &plocica_raster);

    //za plocicu
    glGenVertexArrays(1, &plocica_vao);
    glBindVertexArray(plocica_vao);

    glGenBuffers(1, &plocica_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, plocica_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plocica_vertices), plocica_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);




    plocica_shader_program_id = rafgl_program_create_from_name("plocica_shader");
    uni_plocica_M = glGetUniformLocation(plocica_shader_program_id, "uni_M");
    uni_plocica_VP = glGetUniformLocation(plocica_shader_program_id, "uni_VP");
    uni_plocica_tekstura_loc = glGetUniformLocation(plocica_shader_program_id, "uni_plocica_tekstura");


    //za kutiju1
    glGenVertexArrays(1, &kutija1_vao);
    glGenBuffers(1, &kutija1_vbo);
    glBindVertexArray(kutija1_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kutija1_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kutija1_vertices), kutija1_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //za kutiju2
    glGenVertexArrays(1, &kutija2_vao);
    glGenBuffers(1, &kutija2_vbo);
    glBindVertexArray(kutija2_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kutija2_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kutija2_vertices), kutija2_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glGenVertexArrays(1, &kutija3_vao);
    glGenBuffers(1, &kutija3_vbo);
    glBindVertexArray(kutija3_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kutija3_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kutija3_vertices), kutija3_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    glGenVertexArrays(1, &kupa_vao);
    glGenBuffers(1, &kupa_vbo);
    glBindVertexArray(kupa_vao);
    glBindBuffer(GL_ARRAY_BUFFER, kupa_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kupa_vertices), kupa_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    glGenVertexArrays(1, &valjak_vao);
    glGenBuffers(1, &valjak_vbo);
    glBindVertexArray(valjak_vao);
    glBindBuffer(GL_ARRAY_BUFFER, valjak_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(valjak_vertices), valjak_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    camera_update(game_data, delta_time, game_data->raster_width, game_data->raster_height);

    total_time += delta_time;
}

void main_state_render(GLFWwindow *window, void *args)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program_id);

    glBindFramebuffer(GL_FRAMEBUFFER, scena_fbo.fbo_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform3f(uni_light_dir, -0.5f, -1.0f, -0.3f);


    //iscrtavanje
    glUniform3f(uni_normal, -1.0f, 0.0f, 0.0f);
    glBindVertexArray(levi_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    //crtanje desni zid

    glUniform3f(uni_normal, 1.0f, 0.0f, 0.0f);
    glBindVertexArray(desni_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    //crtanje zadnji zid
    glUniform1f(uni_zid_sara, 1.0f);
    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);
    glBindVertexArray(zadnji_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    glUniform1f(uni_zid_sara, 0.0f);



    // postolje - po stranama, radi pravog senčenja
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(postolje_vao);

    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);   // gornja strana
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);  // prednja strana
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glUniform3f(uni_normal, 0.0f, 0.0f, 1.0f);   // zadnja strana
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glUniform3f(uni_normal, -1.0f, 0.0f, 0.0f);  // leva strana
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glUniform3f(uni_normal, 1.0f, 0.0f, 0.0f);   // desna strana
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glBindVertexArray(0);





    mat4_t kristal_rotation = m4_rotation_y(total_time);

    mat4_t kristal_translation = m4_translation(vec3m(0.0f, 0.4f, 3.0f));
    mat4_t kristal_model = m4_mul(kristal_translation, kristal_rotation);


    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) kristal_model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(kristal_vao);

    // gornja piramida - 4 kose strane
    glUniform3f(uni_normal, 0.8f, 0.5f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUniform3f(uni_normal, 0.0f, 0.5f, -0.8f);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    glUniform3f(uni_normal, -0.8f, 0.5f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 6, 3);

    glUniform3f(uni_normal, 0.0f, 0.5f, 0.8f);
    glDrawArrays(GL_TRIANGLES, 9, 3);

    // donja piramida - iste normale kao gornja
    glUniform3f(uni_normal, 0.8f, -0.5f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 12, 3);

    glUniform3f(uni_normal, 0.0f, -0.5f, -0.8f);
    glDrawArrays(GL_TRIANGLES, 15, 3);

    glUniform3f(uni_normal, -0.8f, -0.5f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 18, 3);

    glUniform3f(uni_normal, 0.0f, -0.5f, 0.8f);
    glDrawArrays(GL_TRIANGLES, 21, 3);



    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(sprat_vao);
    glDrawArrays(GL_TRIANGLES, 0, SPRAT_TEMENA);
    glBindVertexArray(0);


    //cestice oko kristala
    float centar_cestica_x = 0.0f;
    float centar_cestica_y = 0.6f;
    float centar_cestica_z = 3.0f;
    float radijus_baza = 0.7f;
    float radijus_razbacanost = 0.6f;
    float visina_razbacanost = 0.35f;
    float brzina_kruzenja = 1.0f;
    float amplituda_lebdenja = 0.15f;

    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glBindVertexArray(cestica_vao);


    for(int i = 0; i < BROJ_CESTICA; i++)
    {
        float ugao = i * (2.0f * M_PIf / BROJ_CESTICA) + total_time * brzina_kruzenja;
        float radijus_cestica = radijus_baza + radijus_razbacanost * sinf(i * 3.0f); //2.4
        float visina_baza = centar_cestica_y + visina_razbacanost * cosf(i * 2.0f);//1.7

        float cestica_x = centar_cestica_x + radijus_cestica * cosf(ugao);
        float cestica_z = centar_cestica_z + radijus_cestica * sinf(ugao);
        float cestica_y = visina_baza + amplituda_lebdenja * sinf(total_time + i);

        mat4_t cestica_model = m4_translation(vec3m(cestica_x, cestica_y, cestica_z));

        glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) cestica_model.m);
        glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glBindVertexArray(0);

    //sara na podu
    glUniform1f(uni_pod_sara, 1.0f);
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUniform1f(uni_pod_sara, 0.0f);

    //crtanje prednji zid
    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);
    glBindVertexArray(prednji_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);




     glUseProgram(plocica_shader_program_id);

    model = m4_identity();
    glUniformMatrix4fv(uni_plocica_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_plocica_VP, 1, GL_FALSE, view_projection.m);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, plocica_tekstura.tex_id);
    glUniform1i(uni_plocica_tekstura_loc, 0);

    glBindVertexArray(plocica_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);



    glUseProgram(shader_program_id);

    //kutija1 (donja, veca)
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(kutija1_vao);
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);   // gornja strana
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);  // prednja strana
    glDrawArrays(GL_TRIANGLES, 6, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, 1.0f);   // zadnja strana
    glDrawArrays(GL_TRIANGLES, 12, 6);
    glUniform3f(uni_normal, -1.0f, 0.0f, 0.0f);  // leva strana
    glDrawArrays(GL_TRIANGLES, 18, 6);
    glUniform3f(uni_normal, 1.0f, 0.0f, 0.0f);   // desna strana
    glDrawArrays(GL_TRIANGLES, 24, 6);
    glBindVertexArray(0);

    //kutija2 (gornja, manja)
    glBindVertexArray(kutija2_vao);
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);
    glDrawArrays(GL_TRIANGLES, 6, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 12, 6);
    glUniform3f(uni_normal, -1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 18, 6);
    glUniform3f(uni_normal, 1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 24, 6);
    glBindVertexArray(0);




    //kutija3 (najgornja, najmanja)
    glBindVertexArray(kutija3_vao);
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, -1.0f);
    glDrawArrays(GL_TRIANGLES, 6, 6);
    glUniform3f(uni_normal, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 12, 6);
    glUniform3f(uni_normal, -1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 18, 6);
    glUniform3f(uni_normal, 1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 24, 6);
    glBindVertexArray(0);

    //kupa
    glBindVertexArray(kupa_vao);
    glUniform3f(uni_normal, 0.8758f, 0.3185f, 0.3628f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUniform3f(uni_normal, 0.3628f, 0.3185f, 0.8758f);
    glDrawArrays(GL_TRIANGLES, 3, 3);
    glUniform3f(uni_normal, -0.3628f, 0.3185f, 0.8758f);
    glDrawArrays(GL_TRIANGLES, 6, 3);
    glUniform3f(uni_normal, -0.8758f, 0.3185f, 0.3628f);
    glDrawArrays(GL_TRIANGLES, 9, 3);
    glUniform3f(uni_normal, -0.8758f, 0.3185f, -0.3628f);
    glDrawArrays(GL_TRIANGLES, 12, 3);
    glUniform3f(uni_normal, -0.3628f, 0.3185f, -0.8758f);
    glDrawArrays(GL_TRIANGLES, 15, 3);
    glUniform3f(uni_normal, 0.3628f, 0.3185f, -0.8758f);
    glDrawArrays(GL_TRIANGLES, 18, 3);
    glUniform3f(uni_normal, 0.8758f, 0.3185f, -0.3628f);
    glDrawArrays(GL_TRIANGLES, 21, 3);
    glBindVertexArray(0);

    //valjak
    glBindVertexArray(valjak_vao);
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glUniform3f(uni_normal, 0.9239f, 0.0f, 0.3827f);
    glDrawArrays(GL_TRIANGLES, 24, 6);
    glUniform3f(uni_normal, 0.3827f, 0.0f, 0.9239f);
    glDrawArrays(GL_TRIANGLES, 30, 6);
    glUniform3f(uni_normal, -0.3827f, 0.0f, 0.9239f);
    glDrawArrays(GL_TRIANGLES, 36, 6);
    glUniform3f(uni_normal, -0.9239f, 0.0f, 0.3827f);
    glDrawArrays(GL_TRIANGLES, 42, 6);
    glUniform3f(uni_normal, -0.9239f, 0.0f, -0.3827f);
    glDrawArrays(GL_TRIANGLES, 48, 6);
    glUniform3f(uni_normal, -0.3827f, 0.0f, -0.9239f);
    glDrawArrays(GL_TRIANGLES, 54, 6);
    glUniform3f(uni_normal, 0.3827f, 0.0f, -0.9239f);
    glDrawArrays(GL_TRIANGLES, 60, 6);
    glUniform3f(uni_normal, 0.9239f, 0.0f, -0.3827f);
    glDrawArrays(GL_TRIANGLES, 66, 6);
    glBindVertexArray(0);


    /* stanica 1: vinjeta, iz scena_fbo u fbo_posle_vinjete */
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_posle_vinjete.fbo_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(post_shader_program_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scena_fbo.tex_id);
    glUniform1i(uni_scena_tekstura, 0);
    glUniform1f(uni_jacina_vinjete, 1.0f);

    glBindVertexArray(kvadrat_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    /* stanica 2: filmska zrnavost, iz fbo_posle_vinjete na pravi ekran */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(zrno_shader_program_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_posle_vinjete.tex_id);
    glUniform1i(uni_zrno_scena_tekstura, 0);
    glUniform1f(uni_vreme, total_time);
    glUniform1f(uni_jacina_zrna, 0.09f);

    glBindVertexArray(kvadrat_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);



}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
