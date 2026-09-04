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

   /* glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glBindVertexArray(vao);
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);*/


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

/*
        glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(postolje_vao);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glBindVertexArray(0);

    mat4_t kristal_model = m4_translation(vec3m(0.0f, 0.3f, 3.0f));
    glUniform3f(uni_normal, 0.0f, 1.0f, 0.0f);
    glUniformMatrix4fv(uni_M, 1, GL_FALSE, (void*) kristal_model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, (void*) view_projection.m);
    glBindVertexArray(kristal_vao);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glBindVertexArray(0);*/



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



    //mat4_t kristal_model = m4_translation(vec3m(0.0f, 0.3f, 3.0f));

    mat4_t kristal_rotation = m4_rotation_y(total_time);
   // mat4_t kristal_translation = m4_translation(vec3m(0.0f, 0.3f, 3.0f));
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

       // donja piramida - iste normale kao gornja (simetrican sjaj)
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
