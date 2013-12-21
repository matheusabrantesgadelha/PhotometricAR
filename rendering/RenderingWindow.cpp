#include "RenderingWindow.hpp"

namespace rendering
{

	RenderingWindow* RenderingWindow::instance = NULL;

	RenderingWindow::RenderingWindow( std::string _name, int _width, int _height )
	: windowName( _name )
	, width( _width )
	, height( _height )
	{
		instance = this;
	}

	/**
	 * Starts rendering window
	 * @param argc Terminal arg value
	 * @param argv Terminal arg value
	 */
	void RenderingWindow::start( int argc, char* argv[] )
	{
		glutInit( &argc, argv );
        glutInitDisplayMode( GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH );
        
        glutInitContextVersion(3, 3);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(this->width, this->height);

        glutCreateWindow( this->windowName.c_str() );

        glEnable(GL_BLEND);
        glEnable( GL_DEPTH_TEST );
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        int OpenGLVersion[2];

        // Tests glew initialization.
        // The following line is trick due to messed glew implementation. Please correct that, guys! =)
        glewExperimental=true;
        GLenum err=glewInit();
        if(err!=GLEW_OK)
        {
			//Problem: glewInit failed, something is seriously wrong.
			std::cout<<"glewInit failed, aborting. " << glewGetErrorString(err) <<std::endl;
        }

        std::cout << "===============================================\n"
        		  << "OPENGL RENDERING WINDOW\n"
        		  << "===============================================\n";

		std::cout << "OpenGL version = " << glGetString(GL_VERSION) << std::endl;
		
		glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
		glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
		std::cout << "OpenGL major version = " << OpenGLVersion[0] << std::endl;
		std::cout << "OpenGL minor version = " << OpenGLVersion[1] << std::endl << std::endl;
		
		glutIdleFunc( this->idleWrapper );
		glutDisplayFunc( this->renderWrapper );
		glutReshapeFunc( this->reshapeWrapper );
		glutKeyboardFunc( this->keyboardWrapper );

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	/**
	 * Default method to execute on window is on an idle state.
	 */
	void RenderingWindow::idle()
	{
		
	}

	/**
	 * Default method for rendering
	 */
	void RenderingWindow::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		glutSwapBuffers();
	}

	/**
	 * Default method for keyboard event handling
	 * @param k Key description
	 * @param x Modifier value
	 * @param y Modifier value
	 */
	void RenderingWindow::keyboard( unsigned char k, int x, int y )
	{
		if( k==27 )
		{
			exit(0);
		}
	}

	/**
	 * Method to change window size
	 * @param _width  New window width
	 * @param _height New window height
	 */
	void RenderingWindow::reshape( int _width, int _height )
	{
		glViewport( 0, 0, _width, _height );
	}

	/**
	 * Wrapper method used to call overrided methods in an OO fashion
	 */
	void RenderingWindow::renderWrapper()
	{
		instance->render();
		glFlush();
	}

	/**
	 * Wrapper method used to call overrided methods in an OO fashion
	 */
	void RenderingWindow::reshapeWrapper( int _width, int _height )
	{
		instance->reshape( _width, _height );
	}

	/**
	 * Wrapper method used to call overrided methods in an OO fashion
	 */
	void RenderingWindow::keyboardWrapper( unsigned char k, int x, int y )
	{
		instance->keyboard( k, x, y );
	}

	/**
	 * Wrapper method used to call overrided methods in an OO fashion
	 */
	void RenderingWindow::idleWrapper()
	{
		instance->idle();
	}
}