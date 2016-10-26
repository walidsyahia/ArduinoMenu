/********************
Sept. 2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
creative commons license 3.0: Attribution-ShareAlike CC BY-SA
This software is furnished "as is", without technical support, and with no
warranty, express or implied, as to its usefulness for any purpose.

Thread Safe: No
Extensible: Yes

Use graphics screens (adafruit library based) as menu output
www.r-site.net
***/
#ifndef RSITE_ARDUINOP_MENU_GFX
	#define RSITE_ARDUINOP_MENU_GFX
	#include <Adafruit_GFX.h>
	#include "../menu.hpp"

namespace Menu {

		#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

	  class menuGFX:public gfxOut {
	    public:
				Adafruit_GFX& gfx;
				const colorDef<uint16_t> (&colors)[nColors];
		    menuGFX(Adafruit_GFX& gfx,const colorDef<uint16_t> (&c)[nColors],panelsList &p,idx_t resX=6,idx_t resY=9)
					:gfxOut(resX,resY,p,false),colors(c),gfx(gfx) {}
					//:gfxOut(gfx.width()/resX,gfx.height()/resY,resX,resY,false),colors(c),gfx(gfx) {}

				size_t write(uint8_t ch) override {return gfx.write(ch);}

				inline uint16_t getColor(colorDefs color=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) const {
          return memWord(&(stat==enabledStatus?colors[color].enabled[selected+edit]:colors[color].disabled[selected]));
        }

				void setColor(colorDefs c,bool selected=false,status s=enabledStatus,bool e=false) override {
					gfx.setTextColor(getColor(c,selected,s,e));
				}

				void clearLine(idx_t ln,idx_t panelNr=0,colorDefs color=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) override {
					const panel p=panels[panelNr];
					gfx.fillRect(p.x*resX,(p.y+ln)*resY,maxX()*resX,resY,getColor(color,selected,stat,edit));
		    	//setCursor(0,ln);
		    }
		    void clear() override {
					gfx.fillScreen(getColor(bgColor,false,enabledStatus,false));
		    	setCursor(0,0);
					setColor(fgColor);
				}

				virtual void clear(idx_t panelNr) override {
					const panel p=panels[panelNr];
					gfx.fillRect(p.x*resX,p.y*resY,p.w*resX,p.h*resY,getColor(bgColor,false,enabledStatus,false));
				}

		    void setCursor(idx_t x,idx_t y,idx_t panelNr=0) override {
					const panel p=panels[panelNr];
					gfx.setCursor((p.x+x)*resX,(p.y+y)*resY+fontMarginY);
				}

				void drawCursor(idx_t ln,bool selected,status stat,bool edit=false,idx_t panelNr=0) override {
					const panel p=panels[panelNr];
					gfxOut::drawCursor(ln,selected,stat);
					gfx.drawRect(p.x*resX,(p.y+ln)*resY,maxX()*resX,resY,getColor(cursorColor,selected,enabledStatus,false));
				}

	  };

}; //namespace menuGFX
#endif
