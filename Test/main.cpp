#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../server/Image.hpp"


TEST_CASE( "Test extraction Connected Components JPG Files") {

    SECTION( "Test JPG 400x400 Blank_img" ) {
        
        Image * img = new Image("images/JPG_400_400/Blank_img.jpg");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        //REQUIRE(ListTmpCC.size() == 0);
    }

    SECTION( "Test JPG 400x400 Black_img" ) {
        
        Image * img = new Image("images/JPG_400_400/Black_img.jpg");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        //REQUIRE(ListTmpCC.size() == 0);
    }

    SECTION( "Test JPG 400x400 1CC_img" ) {
        
        Image * img = new Image("images/JPG_400_400/1CC_img.jpg");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 1);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        REQUIRE( rect.x == Approx(100).epsilon(0.1));
        REQUIRE(rect.y == Approx(100).epsilon(0.1));
        REQUIRE(rect.height == Approx(150).epsilon(0.1));
        REQUIRE(rect.width == Approx(150).epsilon(0.1));
    
    }     

    SECTION( "Test JPG 400x400 8CC_img " ) {
        
        Image * img = new Image("images/JPG_400_400/8CC_img.jpg");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        //REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 8);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        //REQUIRE(rect.x == Approx(19).epsilon(0.1));
        //REQUIRE(rect.y == Approx(33).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));
        

        rect = img->getBoundingBoxAtIndex(1,0);

        //REQUIRE(rect.x == Approx(28).epsilon(0.1));
        REQUIRE(rect.y == Approx(36).epsilon(0.1));
        //REQUIRE(rect.height == Approx(10).epsilon(0.1));
        //REQUIRE(rect.width == Approx(8).epsilon(0.1));


        rect = img->getBoundingBoxAtIndex(2,0);

        //REQUIRE(rect.x == Approx(37).epsilon(0.1));
        REQUIRE(rect.y == Approx(36).epsilon(0.1));
        REQUIRE(rect.height == Approx(10).epsilon(0.1));
        //REQUIRE(rect.width == Approx(7).epsilon(0.1));
    
    }

     SECTION( "Test JPG 400x400 14CC_2L_img" ) {
        
        Image * img = new Image("images/JPG_400_400/14CC_2L_img.jpg");
       // img->ComputeMask();

        //std::vector<Line> ListTmpLine = img->getListLine();
        //std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        //REQUIRE(ListTmpLine.size() == 2);
        //REQUIRE(ListTmpCC.size() == 14);
        

        //cv::Rect rect = img->getBoundingBoxAtIndex(0,0);


        //REQUIRE(rect.x == Approx(19).epsilon(0.1));
        //REQUIRE(rect.y == Approx(33).epsilon(0.1));
        //REQUIRE(rect.height == Approx(8).epsilon(0.1));
        //REQUIRE(rect.width == Approx(13).epsilon(0.1));
    
    }


}
TEST_CASE( "Test extraction Connected Components PNG Files") {

    SECTION( "Test PNG 400x400 Blank_img" ) {
        
        Image * img = new Image("images/PNG_400_400/Blank_img.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        //REQUIRE(ListTmpCC.size() == 0);
    }

    SECTION( "Test PNG 400x400 Black_img" ) {
        
        Image * img = new Image("images/PNG_400_400/Black_img.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();

        //REQUIRE( ListTmpLine.size() == 0 );
        //REQUIRE(ListTmpCC.size() == 0);
    }

    SECTION( "Test PNG 400x400 1CC_img" ) {
        
        Image * img = new Image("images/PNG_400_400/1CC_img.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 1);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        REQUIRE( rect.x == Approx(100).epsilon(0.1));
        REQUIRE(rect.y == Approx(100).epsilon(0.1));
        REQUIRE(rect.height == Approx(150).epsilon(0.1));
        REQUIRE(rect.width == Approx(150).epsilon(0.1));
    
    }     

    SECTION( "Test PNG 400x400 8CC_img " ) {
        
        Image * img = new Image("images/PNG_400_400/8CC_img.png");
        img->ComputeMask();

        std::vector<Line> ListTmpLine = img->getListLine();
        std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        //REQUIRE(ListTmpLine.size() == 1);
        REQUIRE(ListTmpCC.size() == 8);
        

        cv::Rect rect = img->getBoundingBoxAtIndex(0,0);

        //REQUIRE(rect.x == Approx(19).epsilon(0.1));
        REQUIRE(rect.y == Approx(33).epsilon(0.1));
        REQUIRE(rect.height == Approx(13).epsilon(0.1));
        REQUIRE(rect.width == Approx(9).epsilon(0.1));
    
    
    }

     SECTION( "Test PNG 400x400 14CC_2L_img" ) {
        
        // Image * img = new Image("images/PNG_400_400/14CC_2L_img.png");
        // img->ComputeMask();

        // std::vector<Line> ListTmpLine = img->getListLine();
        // std::vector<ConnectedComponent> ListTmpCC = ListTmpLine[0].getListCC();
  
        // REQUIRE(ListTmpLine.size() == 2);
        // REQUIRE(ListTmpCC.size() == 14);
        

        // cv::Rect rect = img->getBoundingBoxAtIndex(0,0);


        // REQUIRE( rect.x == Approx(19).epsilon(0.1));
        // REQUIRE(rect.y == Approx(33).epsilon(0.1));
        // REQUIRE(rect.height == Approx(8).epsilon(0.1));
        // REQUIRE(rect.width == Approx(13).epsilon(0.1));
    
    }


}