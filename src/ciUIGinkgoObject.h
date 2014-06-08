/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef CIUI_GINKGO_OBJECT
#define CIUI_GINKGO_OBJECT

#include "ciUIWidget.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"

class ciUIGinkgoObject : public ciUIButton
{
public:
    ciUIGinkgoObject(float x, float y, float w, bool _value, string _name, int _size)
    {
        useReference = false;         
        rect = new ciUIRectangle(x,y,w,0); 
        autoSize = false;         
        init(&_value, _name, _size); 
    }

    ciUIGinkgoObject(float w, bool _value, string _name, int _size, float h = 0)
    {
        useReference = false;         
        rect = new ciUIRectangle(0,0,w,h); 
        autoSize = false;         
        init(&_value, _name, _size); 
    }

    ciUIGinkgoObject(float x, float y, bool _value, string _name, int _size)
    {
        useReference = false;         
        rect = new ciUIRectangle(x,y,0,0); 
        autoSize = true;         
        init(&_value, _name, _size); 
    }

    ciUIGinkgoObject(bool _value, string _name, int _size)
    {
        useReference = false;         
        rect = new ciUIRectangle(0,0,0,0); 
        autoSize = true;         
        init(&_value, _name, _size); 
    }
    
    ciUIGinkgoObject(bool _value, string _name, string _type, int _size)
    {
        useReference = false;
        rect = new ciUIRectangle(0,0,0,0);
        autoSize = true;
        init(&_value, _name, _size);
        type = _type;
    }
    
    ciUIGinkgoObject(float x, float y, float w, bool *_value, string _name, int _size)
    {
        useReference = true; 
        rect = new ciUIRectangle(x,y,w,0); 
        autoSize = false;         
        init(_value, _name, _size); 
    }
    
    ciUIGinkgoObject(float w, bool *_value, string _name, int _size, float h = 0)
    {
        useReference = true;         
        rect = new ciUIRectangle(0,0,w,h); 
        autoSize = false;         
        init(_value, _name, _size); 
    }
    
    ciUIGinkgoObject(float x, float y, bool *_value, string _name, int _size)
    {
        useReference = true;         
        rect = new ciUIRectangle(x,y,0,0); 
        autoSize = true;         
        init(_value, _name, _size); 
    }
    
    ciUIGinkgoObject(bool *_value, string _name, int _size)
    {
        useReference = true;         
        rect = new ciUIRectangle(0,0,0,0); 
        autoSize = true;         
        init(_value, _name, _size);
    }    
    
    void init(bool *_value, string _name, int _size)
    {
        name = _name; 		
        
        label = new ciUILabel(0,0,(name+" LABEL"), name, _size);
		label->setParent(label); 
		label->setRectParent(rect);         
        label->setEmbedded(true);
        
        kind = CI_UI_WIDGET_GINKGOOBJECT;
        paddedRect = new ciUIRectangle(-padding, -padding, padding*2.0f, padding*2.0f);
		paddedRect->setParent(rect);
        
        if(useReference)
        {
            value = _value; 
        }
        else
        {
            value = new bool(); 
            *value = *_value; 
        }
        
        setValue(*_value);         
    }
		
	void setParent(ciUIWidget *_parent)
	{
		parent = _parent; 
        if(rect->getHeight() == 0)
        {
            rect->setHeight(label->getPaddingRect()->getHeight()+padding*4.0f);
        }    
		ciUIRectangle *labelrect = label->getRect(); 
        if(autoSize)
        {
            if (label->getPaddingRect()->getWidth()+padding*2.0f < gMinWidth)
            {
                rect->setWidth(gMinWidth);
            }else{
                rect->setWidth(label->getPaddingRect()->getWidth()+padding*2.0f);
            }
        }
        else
        {
            while(labelrect->getWidth() > rect->getWidth())
            {
                string labelstring = label->getLabel();
                string::iterator it;
                it=labelstring.end();
                it--; 
                labelstring.erase (it); 
                label->setLabel(labelstring);
            }            
        }

		float h = labelrect->getHeight()/2;
		float ph = rect->getHeight(); 	
        
        float w = labelrect->getWidth();
        float pw = rect->getWidth(); 
        
		labelrect->setY((int)(ph*.5f - h*.5f)); 
        labelrect->setX((int)(pw*.5f - w*.5f)); 
		paddedRect->setHeight(rect->getHeight()+padding*5.0f);
        paddedRect->setWidth(rect->getWidth()+padding*5.0f);
	}	
    
    virtual void draw()
    {
        drawPadded();
        drawPaddedOutline();
        
        drawBack();
        
        drawOutline();
        drawOutlineHighlight();
        
        //type header
        ci::gl::drawString(type, Vec2f(floor(rect->getX()+8), floor(rect->getY()+8)), ColorA(1,0.75,1,.5));
        
        drawFill();
        drawFillHighlight();
    }
    
protected:    //inherited: ciUIRectangle *rect; ciUIWidget *parent; 
    bool autoSize;
    std::string type;
    float gMinWidth = 72;
};

#endif
