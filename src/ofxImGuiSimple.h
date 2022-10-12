//
//  ofxImGuiSimple.h
//  example-basic
//
//  Created by Eduard Frigola Bagué on 06/04/2020.
//

#ifndef ofxImGuiSimple_h
#define ofxImGuiSimple_h

#include <stdio.h>

class ofAppBaseWindow;

class ofxImGuiSimple {
public:
    ofxImGuiSimple(){};
    ~ofxImGuiSimple(){};
    
    void setup(ofAppBaseWindow* win = nullptr);
    
    void begin();
    void end();
    
    void draw(){};
    
private:
    bool isProgramableRenderer;
};

#endif /* ofxImGuiSimple_h */
