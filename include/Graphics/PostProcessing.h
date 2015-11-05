#ifndef KTE_POST_PROCESSING_H
#define KTE_POST_PROCESSING_H

#include <GL/glew.h>
#include "Window.h"
#include "ShaderManager.h"
#include "RenderTechnique.h"
#include "Geometries.h"
#include <Components/Camera.h>
#include <GameEngine.h>
#include "Utility/SaveTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace kte 
{
    class PostProcessing 
    {
    public:
	
	PostProcessing()
	{
	    fbo = 0;
	    renderTarget = 0;
	    context = nullptr;
	}
	
	~PostProcessing()
	{
	     glDeleteRenderbuffersEXT(1, &depthBuffer);
	     glDeleteTextures(1, &renderTarget);
	     glDeleteFramebuffers(1, &fbo);
	}
	bool initialize()
	{
	    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	    glGenFramebuffers(1, &fbo);
	    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	    
	    // The texture we're going to render to
	    glGenTextures(1, &renderTarget);
	    
	    // "Bind" the newly created texture : all future texture functions will modify this texture
	    glBindTexture(GL_TEXTURE_2D, renderTarget);
	    
	    context = kte::GameEngine::instance()->getContext();
	    
		    
	    
	    // Give an empty image to OpenGL ( the last "0" )
	    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, context->getScreenResolution().x, context->getScreenResolution().y, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
	    
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	    glGenerateMipmapEXT(GL_TEXTURE_2D);

	    
	    // The depth buffer
	    glGenRenderbuffers(1, &depthBuffer);
	    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, context->getScreenResolution().x, context->getScreenResolution().y);
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);    
		
	    // Set "renderedTexture" as our colour attachement #0
	    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTarget, 0);
	    
	    // Set the list of draw buffers.
	    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	    // Always check that our framebuffer is ok
	    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	    return false;

	    quad = &kte::Geometry::quad;
	    
	    return (renderTarget>0 && fbo > 0);
	}
	
	void reload() 
	{
	    glDeleteTextures(1, &renderTarget);
	    glDeleteFramebuffers(1, &fbo);
	    glDeleteRenderbuffersEXT(1, &depthBuffer);
	    
	    
	    initialize();
	}
	
	void bind() 
	{
	    // Render to our framebuffer
	    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	    glViewport(0, 0, context->getScreenResolution().x, context->getScreenResolution().y); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	}
	
	void render(GLuint renderResult) 
	{

	    GLint textureLoc = glGetUniformLocation(currentTechnique->getProgramId(), "texture");
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, renderResult);
	    	
	    glUniform1i(textureLoc, 0);
	    renderToScreen();
	}
	void render()
	{

	    GLint textureLoc = glGetUniformLocation(currentTechnique->getProgramId(), "texture");
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, renderTarget);
	    	
	    glUniform1i(textureLoc, 0);
	    
	    renderToScreen();

	}
	
	void setTechnique(RenderTechnique* technique)
	{
	    currentTechnique = technique;
	}
	
    private:
	void renderToScreen()
	{

	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	    glUseProgram(currentTechnique->getProgramId());

	    quad->bindVAO();
	    
	    glm::mat4 matrix;
	    matrix = glm::translate(matrix, glm::vec3(-1.0f, -1.0f, 0.0f));
	    matrix = glm::scale(matrix, glm::vec3(2.0f, 2.0f, 1.0f));
	    
	    glm::mat4 mvp = matrix;
	    glm::vec4 color = glm::vec4(1, 1, 1, 1);
	    glm::vec4 uv = glm::vec4(0,0,1,1);
	    
	    


	    glBindBuffer(GL_ARRAY_BUFFER, quad->getMVP());
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &mvp, GL_DYNAMIC_DRAW);

	    glBindBuffer(GL_ARRAY_BUFFER, quad->getCOLOR());
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), &color, GL_DYNAMIC_DRAW);

	    glBindBuffer(GL_ARRAY_BUFFER, quad->getUV());
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), &uv, GL_DYNAMIC_DRAW);


	    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getNumberOfIndices(), 1);
	    
	    
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glBindVertexArray(0);
	}
	
	GLuint fbo;
	GLuint renderTarget;
	GLuint depthBuffer;
	RenderTechnique* currentTechnique;
	kte::Window* context;
	kte::Quad* quad;
    };
}
#endif