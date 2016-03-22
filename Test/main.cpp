#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../server/Image.hpp"



TEST_CASE( "Test extraction Connected Components PNG Files") {

    SECTION( "Test PNG 400x400 Blank" ) {
        
        Image * img = new Image("images/PNG/Blank.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        REQUIRE(ListTmpCC.size() == 1);
    }

    SECTION( "Test PNG 400x400 Black" ) {
        
        Image * img = new Image("images/PNG/Black.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        REQUIRE(ListTmpCC.size() == 1);
    }

    SECTION( "Test PNG 400x400 1CC" ) {
        
        Image * img = new Image("images/PNG/1CC.png");
        img->ComputeMask();
        
        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 1);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        REQUIRE( rect.x == Approx(113).epsilon(0.1));
        REQUIRE(rect.y == Approx(96).epsilon(0.1));
        REQUIRE(rect.height == Approx(167).epsilon(0.1));
        REQUIRE(rect.width == Approx(167).epsilon(0.1));
        
    }     

    SECTION( "Test PNG 400x400 9CC " ) {
        
        Image * img = new Image("images/PNG/9CC.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 9);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        REQUIRE(rect.x == Approx(30).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(6).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(1,0);

        REQUIRE(rect.x == Approx(39).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(14).epsilon(0.1));
        

        rect = img->getBoundingBoxAtIndex(2,0);

        REQUIRE(rect.x == Approx(55).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(3,0);

        REQUIRE(rect.x == Approx(66).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(14).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(4,0);

        REQUIRE(rect.x == Approx(77).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(10).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(5,0);

        REQUIRE(rect.x == Approx(94).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(12).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(6,0);

        REQUIRE(rect.x == Approx(103).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(10).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(7,0);

        REQUIRE(rect.x == Approx(114).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(8).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(8,0);

        REQUIRE(rect.x == Approx(123).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(7).epsilon(0.1));

    
    }

     SECTION( "Test PNG 400x400 13CC" ) {
        
       Image * img = new Image("images/PNG/13CC.png");
        img->ComputeMask();
        
        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC0 = ListTmpLine[0].getListCC();
        std::vector<ConnectedComponent> ListTmpCC1 = ListTmpLine[1].getListCC();

    

        REQUIRE(ListTmpLine.size() == 2);
        REQUIRE(ListTmpCC0.size() == 9);
        REQUIRE(ListTmpCC1.size() == 4);

        


       cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        REQUIRE(rect.x == Approx(30).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(6).epsilon(0.1));
        
        rect = img->getBoundingBoxAtIndex(1,0);

        REQUIRE(rect.x == Approx(39).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(14).epsilon(0.1));
        
 
        rect = img->getBoundingBoxAtIndex(2,0);

        REQUIRE(rect.x == Approx(55).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));
 
        rect = img->getBoundingBoxAtIndex(3,0);

        REQUIRE(rect.x == Approx(66).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(14).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));
 
        rect = img->getBoundingBoxAtIndex(4,0);

        REQUIRE(rect.x == Approx(77).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(10).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(5,0);

        REQUIRE(rect.x == Approx(94).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(12).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(6,0);

        REQUIRE(rect.x == Approx(103).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(10).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(7,0);

        REQUIRE(rect.x == Approx(114).epsilon(0.1));
        REQUIRE(rect.y == Approx(46).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(8).epsilon(0.1));

        rect = img->getBoundingBoxAtIndex(8,0);

        REQUIRE(rect.x == Approx(123).epsilon(0.1));
        REQUIRE(rect.y == Approx(43).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(7).epsilon(0.1));
         
        rect = img->getBoundingBoxAtIndex(0,1);

        REQUIRE(rect.x == Approx(32).epsilon(0.1));
        REQUIRE(rect.y == Approx(84).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(11).epsilon(0.1));
        
        rect = img->getBoundingBoxAtIndex(1,1);

        REQUIRE(rect.x == Approx(44).epsilon(0.1));
        REQUIRE(rect.y == Approx(87).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(10).epsilon(0.1));
        
        rect = img->getBoundingBoxAtIndex(2,1);

        REQUIRE(rect.x == Approx(56).epsilon(0.1));
        REQUIRE(rect.y == Approx(87).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(8).epsilon(0.1));
        
        rect = img->getBoundingBoxAtIndex(3,1);

        REQUIRE(rect.x == Approx(67).epsilon(0.1));
        REQUIRE(rect.y == Approx(87).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));

        
    }


}