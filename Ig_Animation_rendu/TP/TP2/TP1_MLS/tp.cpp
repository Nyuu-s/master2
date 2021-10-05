// -------------------------------------------
// gMini : a minimal OpenGL/GLUT application
// for 3D graphics.
// Copyright (C) 2006-2008 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <algorithm>
#include <GL/glut.h>
#include <float.h>
#include "src/Vec3.h"
#include "src/Camera.h"
#include "src/jmkdtree.h"




std::vector< Vec3 > positions;
std::vector< Vec3 > normals;

std::vector< Vec3 > positions2;
std::vector< Vec3 > normals2;

std::vector<Vec3> outputPoints;
std::vector<Vec3> outputNormals;


// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;
static unsigned int SCREENWIDTH = 640;
static unsigned int SCREENHEIGHT = 480;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static bool fullScreen = false;




// ------------------------------------------------------------------------------------------------------------
// i/o and some stuff
// ------------------------------------------------------------------------------------------------------------
void loadPN (const std::string & filename , std::vector< Vec3 > & o_positions , std::vector< Vec3 > & o_normals ) {
    unsigned int surfelSize = 6;
    FILE * in = fopen (filename.c_str (), "rb");
    if (in == NULL) {
        std::cout << filename << " is not a valid PN file." << std::endl;
        return;
    }
    size_t READ_BUFFER_SIZE = 1000; // for example...
    float * pn = new float[surfelSize*READ_BUFFER_SIZE];
    o_positions.clear ();
    o_normals.clear ();
    while (!feof (in)) {
        unsigned numOfPoints = fread (pn, 4, surfelSize*READ_BUFFER_SIZE, in);
        for (unsigned int i = 0; i < numOfPoints; i += surfelSize) {
            o_positions.push_back (Vec3 (pn[i], pn[i+1], pn[i+2]));
            o_normals.push_back (Vec3 (pn[i+3], pn[i+4], pn[i+5]));
        }

        if (numOfPoints < surfelSize*READ_BUFFER_SIZE) break;
    }
    fclose (in);
    delete [] pn;
}
void savePN (const std::string & filename , std::vector< Vec3 > const & o_positions , std::vector< Vec3 > const & o_normals ) {
    if ( o_positions.size() != o_normals.size() ) {
        std::cout << "The pointset you are trying to save does not contain the same number of points and normals." << std::endl;
        return;
    }
    FILE * outfile = fopen (filename.c_str (), "wb");
    if (outfile == NULL) {
        std::cout << filename << " is not a valid PN file." << std::endl;
        return;
    }
    for(unsigned int pIt = 0 ; pIt < o_positions.size() ; ++pIt) {
        fwrite (&(o_positions[pIt]) , sizeof(float), 3, outfile);
        fwrite (&(o_normals[pIt]) , sizeof(float), 3, outfile);
    }
    fclose (outfile);
}
void scaleAndCenter( std::vector< Vec3 > & io_positions ) {
    Vec3 bboxMin( FLT_MAX , FLT_MAX , FLT_MAX );
    Vec3 bboxMax( FLT_MIN , FLT_MIN , FLT_MIN );
    for(unsigned int pIt = 0 ; pIt < io_positions.size() ; ++pIt) {
        for( unsigned int coord = 0 ; coord < 3 ; ++coord ) {
            bboxMin[coord] = std::min<float>( bboxMin[coord] , io_positions[pIt][coord] );
            bboxMax[coord] = std::max<float>( bboxMax[coord] , io_positions[pIt][coord] );
        }
    }
    Vec3 bboxCenter = (bboxMin + bboxMax) / 2.f;
    float bboxLongestAxis = std::max<float>( bboxMax[0]-bboxMin[0] , std::max<float>( bboxMax[1]-bboxMin[1] , bboxMax[2]-bboxMin[2] ) );
    for(unsigned int pIt = 0 ; pIt < io_positions.size() ; ++pIt) {
        io_positions[pIt] = (io_positions[pIt] - bboxCenter) / bboxLongestAxis;
    }
}

void applyRandomRigidTransformation( std::vector< Vec3 > & io_positions , std::vector< Vec3 > & io_normals ) {
    srand(time(NULL));
    Mat3 R = Mat3::RandRotation();
    Vec3 t = Vec3::Rand(1.f);
    for(unsigned int pIt = 0 ; pIt < io_positions.size() ; ++pIt) {
        io_positions[pIt] = R * io_positions[pIt] + t;
        io_normals[pIt] = R * io_normals[pIt];
    }
}

void subsample( std::vector< Vec3 > & i_positions , std::vector< Vec3 > & i_normals , float minimumAmount = 0.1f , float maximumAmount = 0.2f ) {
    std::vector< Vec3 > newPos , newNormals;
    std::vector< unsigned int > indices(i_positions.size());
    for( unsigned int i = 0 ; i < indices.size() ; ++i ) indices[i] = i;
    srand(time(NULL));
    std::random_shuffle(indices.begin() , indices.end());
    unsigned int newSize = indices.size() * (minimumAmount + (maximumAmount-minimumAmount)*(float)(rand()) / (float)(RAND_MAX));
    newPos.resize( newSize );
    newNormals.resize( newSize );
    for( unsigned int i = 0 ; i < newPos.size() ; ++i ) {
        newPos[i] = i_positions[ indices[i] ];
        newNormals[i] = i_normals[ indices[i] ];
    }
    i_positions = newPos;
    i_normals = newNormals;
}

bool save( const std::string & filename , std::vector< Vec3 > & vertices , std::vector< unsigned int > & triangles ) {
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open()) {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "OFF" << std::endl;

    unsigned int n_vertices = vertices.size() , n_triangles = triangles.size()/3;
    myfile << n_vertices << " " << n_triangles << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v ) {
        myfile << vertices[v][0] << " " << vertices[v][1] << " " << vertices[v][2] << std::endl;
    }
    for( unsigned int f = 0 ; f < n_triangles ; ++f ) {
        myfile << 3 << " " << triangles[3*f] << " " << triangles[3*f+1] << " " << triangles[3*f+2];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}



// ------------------------------------------------------------------------------------------------------------
// rendering.
// ------------------------------------------------------------------------------------------------------------

void initLight () {
    GLfloat light_position1[4] = {22.0f, 16.0f, 50.0f, 0.0f};
    GLfloat direction1[3] = {-52.0f,-16.0f,-50.0f};
    GLfloat color1[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat ambient[4] = {0.3f, 0.3f, 0.3f, 0.5f};

    glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, color1);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
}

void init () {
    camera.resize (SCREENWIDTH, SCREENHEIGHT);
    initLight ();
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
    glClearColor (0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
}



void drawTriangleMesh( std::vector< Vec3 > const & i_positions , std::vector< unsigned int > const & i_triangles ) {
    glBegin(GL_TRIANGLES);
    for(unsigned int tIt = 0 ; tIt < i_triangles.size() / 3 ; ++tIt) {
        Vec3 p0 = i_positions[3*tIt];
        Vec3 p1 = i_positions[3*tIt+1];
        Vec3 p2 = i_positions[3*tIt+2];
        Vec3 n = Vec3::cross(p1-p0 , p2-p0);
        n.normalize();
        glNormal3f( n[0] , n[1] , n[2] );
        glVertex3f( p0[0] , p0[1] , p0[2] );
        glVertex3f( p1[0] , p1[1] , p1[2] );
        glVertex3f( p2[0] , p2[1] , p2[2] );
    }
    glEnd();
}

void drawPointSet( std::vector< Vec3 > const & i_positions , std::vector< Vec3 > const & i_normals ) {
    glBegin(GL_POINTS);
    for(unsigned int pIt = 0 ; pIt < i_positions.size() ; ++pIt) {
        glNormal3f( i_normals[pIt][0] , i_normals[pIt][1] , i_normals[pIt][2] );
        glVertex3f( i_positions[pIt][0] , i_positions[pIt][1] , i_positions[pIt][2] );
    }
    glEnd();
}

void draw () {
    glPointSize(2); // for example...

     glColor3f(0.8,0.8,1);
    drawPointSet(positions2 , normals2);

    glColor3f(0.5,1,0.5);
    drawPointSet(positions , normals);
    
    glColor3f(0.5,1,0.5);
    drawPointSet(outputPoints , normals2);
}








void display () {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply ();
    draw ();
    glFlush ();
    glutSwapBuffers ();
}

void idle () {
    glutPostRedisplay ();
}

void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'f':
        if (fullScreen == true) {
            glutReshapeWindow (SCREENWIDTH, SCREENHEIGHT);
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;

    case 'w':
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if(polygonMode[0] != GL_FILL)
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        break;

    default:
        break;
    }
    idle ();
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
    idle ();
}

void motion (int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate (x, y);
    }
    else if (mouseMovePressed == true) {
        camera.move ((x-lastX)/static_cast<float>(SCREENWIDTH), (lastY-y)/static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom (float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize (w, h);
}

Vec3 projectPointPlane(Vec3 point, Vec3 plane, Vec3 n)
{

    return (point - Vec3::dot((plane -point) , n )* n) ;

}

void projection(Vec3 input, Vec3& output, Vec3 const& position, Vec3 const& normal) {
    float y = Vec3::dot((input - position), normal) / normal.length();
    output = input - y * normal;
}

void HPSS( Vec3 inputPoint , Vec3 & outputPoint , Vec3 & outputNormal ,
std::vector<Vec3>const & positions , std::vector<Vec3>const & normals , BasicANNkdTree const & kdtree ,
int kernel_type, unsigned int nbIterations = 1 , unsigned int knn = 10 ) {
    int k = 0;
    while (k < nbIterations) {
        ANNidxArray id_nearest_neighbors =new ANNidx[ knn ];
        ANNdistArray square_distances_to_neighbors = new ANNdist[ knn ];
        kdtree.knearest(inputPoint, knn, id_nearest_neighbors, square_distances_to_neighbors);
        Vec3 n = Vec3(0, 0, 0);
        Vec3 c = Vec3(0, 0, 0);
        float somme_w = 0;
        Vec3 output[knn];
        for (int i = 0; i < knn; i++) {
            projection(inputPoint, output[i], positions[id_nearest_neighbors[i]], normals[id_nearest_neighbors[i]]);
            float h = sqrt(square_distances_to_neighbors[knn-1]);
            float w = 0;
            float r = (inputPoint - positions[id_nearest_neighbors[i]]).length();
            if (kernel_type == 0) {
                w = exp(-pow(r, 2) / pow(h, 2)); // gaussien
            } else if (kernel_type == 1) {
                w = pow(1 - r / h, 4) * (1 + 4 * r / h); // wendland
            } else {
                w = pow(h / r, 2); // singulier
            }
            n += (w*normals[id_nearest_neighbors[i]]);
            c += w*output[i];
            somme_w += w;
        }
        outputPoint = c / somme_w;
        outputNormal = n / somme_w;
        delete[] id_nearest_neighbors;
        delete[] square_distances_to_neighbors;
        k++;
        inputPoint = outputPoint;
    }
}

struct voxel{
    int id = -1;
    int coins[8];
    float isoValue;
};



struct Grid{
        
    unsigned int nx, ny, nz;
    Vec3 BBmin, BBmax;

    std::vector<voxel> cells;
    std::vector<Vec3> gridPoints;
    
    Grid(int x, int y, int z, Vec3 min, Vec3 max){
        nx = x;
        ny = y;
        nz = z;

        BBmin = min;
        BBmax = max;
        cells.resize((nx-1)*(ny-1)*(nz-1));
        gridPoints.resize(nx*ny*nz);

    }

};


void createVoxels(Grid &grid){
    int i = 0;
    
    for(int x = 0; x< grid.nx-1; x++)
        for(int y = 0; y< grid.ny-1; y++)
            for(int z = 0; z< grid.nz-1; z++)
            {
                voxel v;
                v.coins[0] = i;
                v.coins[1] = i+1;
                v.coins[2] = i+grid.nz;
                v.coins[3] = i+grid.nz+1;
                v.coins[4] = i+grid.nz*grid.ny;
                v.coins[5] = i+grid.nz*grid.ny+1;
                v.coins[6] = i+grid.nz*grid.ny*grid.nx;
                v.coins[7] = i+grid.nz*grid.ny*grid.nx+1;
                grid.cells.push_back(v);
            }
}



void createGrid(Grid &grid){
    int e =0;
    
    float xStep = (grid.BBmax[0] - grid.BBmin[0]) / (float)(grid.nx-1);
    float yStep = (grid.BBmax[1] - grid.BBmin[1]) / (float)(grid.ny-1);    
    float zStep = (grid.BBmax[2] - grid.BBmin[2]) / (float)(grid.nz-1); 

    std::cout << xStep << " " << yStep << " " << zStep << "\n";
    


    //std::cout << grid.ny << " \n" << grid.nx << " \n" << grid.nz << " \n" << grid.nx * grid.ny * grid.nz << " \n";

    //grid.gridPoints.resize(grid.nx * grid.ny * grid.nz);

    for (unsigned int i = 0; i < grid.nx; i++) {
        for (unsigned int j = 0; j < grid.ny; j++) {
            for (unsigned int k = 0; k < grid.nz; k++) {
                
                
                 grid.gridPoints[e++] = Vec3(grid.BBmin[0]+xStep*i, grid.BBmin[1]+yStep*j, grid.BBmin[2]+zStep*k); // point
      
            }
        }
    }
}


// void checkVoxelId(){

//     for(int i=0; i<grid.gridPoints.size(); i++){
//         double g = implicite(grid.gridPoints[i], position[/*???*/], normals[/*???*/]);
//     }
// }

// double implicite( Vec3 point, Vec3 plan, kdtree tree, ){
//     Vec3 output;
//     Vec3 outputNormal;
//     HPSS(point, output, outputNormal, position, normals, tree, 1, 1, 10));
//    //puissance T ???
//    return ( output , outputNormal));
// }

void getBoundingBox(Vec3 &BBmin, Vec3 BBmax){

Vec3 grid_bbmin = positions[0];
Vec3 grid_bbmax = positions[0];
for( unsigned int pIt = 0 ; pIt < positions.size() ; ++pIt ) {
  for( unsigned int i = 0 ; i < 3 ; ++i ) {
    grid_bbmin[i] = std::min(grid_bbmin[i] , positions[pIt][i]);
    grid_bbmax[i] = std::max(grid_bbmax[i] , positions[pIt][i]);
  }
}

Vec3 grid_center = (grid_bbmin + grid_bbmax) / 2.0;
grid_bbmin += 0.1 * (grid_bbmin - grid_center);
grid_bbmax += 0.1 * (grid_bbmax - grid_center);
BBmin = grid_bbmin;
BBmax = grid_bbmax;

        std::cout << BBmin[0] << " " << BBmin[1] << " " << BBmin[2] << "\n";
        
        std::cout << BBmax[0] << " " << BBmax[1] << " " << BBmax[2] << "\n";

}

#define POINT_INDEX(res, x, y, z) (res) * (res) * (x) + (res) * (y) + (z)

void PointGrid(unsigned res, Vec3 start, Vec3 end, Grid &grid)
{
    grid.gridPoints.resize(res * res * res, Vec3());
    Vec3 boxSize = end - start;

    for (unsigned x = 0; x < res; x++)
    {
        for (unsigned y = 0; y < res; y++)
        {
            for (unsigned z = 0; z < res; z++)
            {
                Vec3 offset(
                    x * boxSize[0] / res,
                    y * boxSize[1] / res,
                    z * boxSize[2] / res
                );
                grid.gridPoints[POINT_INDEX(res, x, y, z)] = start + offset;
            }   
        } 
    }
}


float impliciteHPSS(
    Vec3 inputPoint, 
    std::vector<Vec3> const &positions, 
    std::vector<Vec3> const &normals, 
    BasicANNkdTree const &kdtree, 
    int kernel_type = 1.0,  
    unsigned int nbIterations = 10, 
    unsigned int knn = 20
)
{
    Vec3 projPos, projNormal;
    HPSS(inputPoint, projPos, projNormal, positions, normals, kdtree, kernel_type, nbIterations, knn);
    return Vec3::dot(inputPoint - projPos, projNormal);
}

int main (int argc, char ** argv) {
    if (argc > 2) {
        exit (EXIT_FAILURE);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ("tp point processing");

    init ();
    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);
    key ('?', 0, 0);


    {
        // Load a first pointset, and build a kd-tree:
        loadPN("pointsets/igea.pn" , positions , normals);

        BasicANNkdTree kdtree;
        kdtree.build(positions);
        int a = 16;
        // Create a second pointset that is artificial, and project it on pointset1 using MLS techniques:
        positions2.resize( a*a*a );
        normals2.resize(positions2.size());
        for( unsigned int pIt = 0 ; pIt < positions2.size() ; ++pIt ) {
            // positions2[pIt] = Vec3(
            //             -0.6 + 1.2 * (double)(rand())/(double)(RAND_MAX),
            //             -0.6 + 1.2 * (double)(rand())/(double)(RAND_MAX),
            //             -0.6 + 1.2 * (double)(rand())/(double)(RAND_MAX)
            //             );
             positions2[pIt].normalize();
             positions2[pIt] = 0.6 * positions2[pIt];

         

                     
        }

        // PROJECT USING MLS (HPSS and APSS):
        // TODO
        
        // for(int i=0; i< positions2.size(); i++ ){
        //     HPSS( positions2[i] , positions2[i] , normals2[i] , positions , normals , kdtree ,  0 , 30, 20 );  
        //     //HPSS( positions2[i] , positions2[i] , normals2[i] ,positions , normals , kdtree ,  0 , 5 , 8 );       
        // } 
                Vec3 grid_bbmin = positions[0];
                Vec3 grid_bbmax = positions[0];
                for( unsigned int pIt = 0 ; pIt < positions.size() ; ++pIt ) {
                    for( unsigned int i = 0 ; i < 3 ; ++i ) {
                        grid_bbmin[i] = std::min(grid_bbmin[i] , positions[pIt][i]);
                        grid_bbmax[i] = std::max(grid_bbmax[i] , positions[pIt][i]);
                    }
                }

                Vec3 grid_center = (grid_bbmin + grid_bbmax) / 2.0;
                grid_bbmin += 0.1 * (grid_bbmin - grid_center);
                grid_bbmax += 0.1 * (grid_bbmax - grid_center);

        //getBoundingBox(BBmin, BBmax);
                
        Grid g = Grid(a,a,a, grid_bbmin  ,grid_bbmax); //Vec3(0.6, 0.6, 0.6)
        createGrid(g);
        //PointGrid(a,BBmin, BBmax, g);
        createVoxels(g);

        for (int i = 0; i < g.cells.size(); i++)
        {
            int signCount = 0;
            for (int j = 0; j < 8; j++)
            {
                if(impliciteHPSS(g.gridPoints[g.cells[i].coins[j]], positions, normals, kdtree ) < 0.0){
                    signCount++;
                }
            }
            if(signCount == 8 || signCount == 0){
                //std::cout <<"nope\n";
                continue;
            }
            //std::cout <<"yep\n";
            Vec3 cellPoint = (g.gridPoints[g.cells[i].coins[0]] + g.gridPoints[g.cells[i].coins[7]]) / 2;

            Vec3 cellNormal; 


                
               // HPSS(cellPoint, cellPoint, cellNormal, positions, normals, kdtree,1);


            outputPoints.push_back(cellPoint);
            outputNormals.push_back(cellNormal);
            
        }
        

        for(int i=0; i<g.gridPoints.size();i++){

            positions2[i] = g.gridPoints[i];
        }

        
    }



    glutMainLoop ();
    return EXIT_SUCCESS;
}

