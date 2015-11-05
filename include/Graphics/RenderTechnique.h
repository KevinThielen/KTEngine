#ifndef KTE_RENDERTECHNIQUE_H
#define KTE_RENDERTECHNIQUE_H

#include <map>
#include <GL/glew.h>
#include "Components/TransformationComponent.h"
#include "Components/SpriteComponent.h"
#include "GameEngine.h"

namespace kte
{
    class GameObject;
    class Window;
    class RenderTechnique
    {
    public:
        /******************
        * Use the Rendertechnique at the passed renderPass
        *******************/
        RenderTechnique(std::string name) : name(name), context(nullptr){}
        virtual ~RenderTechnique()
	{
	    glDeleteRenderbuffersEXT(1, &depthBuffer);
	     glDeleteTextures(1, &renderTarget);
	     glDeleteFramebuffers(1, &fbo);	    
	}
        virtual void use() = 0;
        virtual bool init() = 0;
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender){}
        virtual void renderCached(){}

        unsigned int getNumberOfRenderpasses() { return numberOfRenderpasses; }

        std::string getName() { return name; }
        void setName(std::string name) { this->name = name; }

	virtual GLuint getProgramId(unsigned int pass = 0) { return programId; }
	virtual GLuint getRenderTexture() { return renderTarget; }
	
    protected:
	bool generateFBO()
	{ 
	    if(renderTarget > 0)
		glDeleteTextures(1, &renderTarget);
	    if(fbo > 0)
		glDeleteFramebuffers(1, &fbo);
	    
	    if(depthBuffer > 0)
		glDeleteRenderbuffersEXT(1, &fbo);
	    
	    
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

	    
	    return (renderTarget>0 && fbo > 0);
	}
	
        unsigned int numberOfRenderpasses = 1;
        std::string name;
	GLuint programId;
	
	//rendertarget FBo
	GLuint fbo;
	GLuint renderTarget;
	GLuint depthBuffer;			//depthRenderBuffer
	
	kte::Window* context;
    };
}

#endif