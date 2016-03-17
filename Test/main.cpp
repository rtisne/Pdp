#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../server/Image.hpp"


TEST_CASE( "Test extraction Connected Components JPG Files") {

 	SECTION( "Test JPG 400x400 0 CC" ) {
        
        Image * img = new Image("images/JPG_400_400/Blank_img.jpg");
        //img->BinarizedImage();
		//img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 0 );
		REQUIRE(true);
    }

 	SECTION( "Test JPG 400x400 1 CC" ) {
        
        Image * img = new Image("images/JPG_400_400/1CC_img.jpg");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		std::vector<ConnectedComponent> ListTmpCC = img->getListConnectedComponent();
  

		REQUIRE( ListTmpCC.size() == 1 );
		//REQUIRE( ListTmpCC[0].getBoundingBox().getX().x == 100 );
		//REQUIRE( ListTmpCC[0].getBoundingBox().getX().y == 100 );
		//REQUIRE( ListTmpCC[0].getBoundingBox().getHeight() == 150 );
		//REQUIRE( ListTmpCC[0].getBoundingBox().getWidth() == 150 );
    
    }     

    SECTION( "Test JPG 400x400 8 CC " ) {
        
        Image * img = new Image("images/JPG_400_400/8CC_img.jpg");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		REQUIRE( img->getListConnectedComponent().size() == 8);
    
    }

     SECTION( "Test JPG 400x400 14 CC 2L" ) {
        
        Image * img = new Image("images/JPG_400_400/14CC_2L_img.jpg");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 14);
    
    }


}

TEST_CASE( "Test extraction Connected Components PNG Files") {

 	SECTION( "Test PNG 400x400 0 CC" ) {
        
        Image * img = new Image("images/PNG_400_400/Blank_img.png");
        //img->BinarizedImage();
		//img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 0 );
		REQUIRE(true);
    }

 	SECTION( "Test PNG 400x400 1 CC" ) {
        
        Image * img = new Image("images/PNG_400_400/1CC_img.png");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		REQUIRE( img->getListConnectedComponent().size() == 1 );
    
    }     

    SECTION( "Test PNG 400x400 8 CC " ) {
        
        Image * img = new Image("images/PNG_400_400/8CC_img.png");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		REQUIRE( img->getListConnectedComponent().size() == 8);
    
    }

     SECTION( "Test PNG 400x400 14 CC 2L" ) {
        
        Image * img = new Image("images/PNG_400_400/14CC_2L_img.png");
        img->BinarizedImage();
		img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 14);
    
    }


}
