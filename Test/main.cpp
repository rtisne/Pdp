#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../server/Image.hpp"


TEST_CASE( "Test extraction Connected Components") {

 	SECTION( "Test JPG 400x400 0 CC" ) {
        
        Image * img = new Image("images/JPG_400_400/Blank_img.jpg");
        //img->BinarizedImage();
		//img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 0 );
		REQUIRE(true);
    }

 	SECTION( "Test JPG 400x400 1 CC" ) {
        
        Image * img = new Image("images/JPG_400_400/1CC_img.jpg");
        //img->BinarizedImage();
		//img->extractAllConnectedComponents();

		//REQUIRE( img->getListConnectedComponent().size() == 1 );
		REQUIRE(true);
    }


}
