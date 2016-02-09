<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Pdp client</title>
	<link href="style.css" rel="stylesheet">
	<link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
	
</head>
<body>
<nav class="navbar navbar-default">
  <div class="container-fluid">
    <div class="navbar-header">
      <a class="navbar-brand" href="#" ref="Process and find connexes composants"><span class="glyphicon glyphicon-tasks"></span></a>
    </div>

    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <ul class="nav navbar-nav">
        <li>
					<a href="#">
				    <label>
				      <input type="checkbox" id="baseline">  Show Baseline
						</label>
					</a>
        </li>
      </ul>
      <ul class="nav navbar-nav navbar-right">
        <li>
					<a href="#"><span class="glyphicon glyphicon-save" aria-hidden="true"></span></a>
				</li>
				<li>
					<a class="modal" href="#"><span class="glyphicon glyphicon-trash" id="button_trash" aria-hidden="true"></span></a>
				</li>
      </ul>
    </div>
  </div>
</nav>
<div class="row processing">
	<div class="left col-md-8">
		<div class="zoom-icon">
			<span class="glyphicon glyphicon-zoom-in" id="zoom-in"></span><br>
			<span class="glyphicon glyphicon-zoom-out" id="zoom-out"></span><br>
			<span class="glyphicon glyphicon-repeat" id="zoom-reset"></span>
		</div>
		
		<canvas id="canvas" height="500" width="500" data-girar="0"></canvas>
		<img class="loader" src="img/loader.gif">
		<form enctype="multipart/form-data" action="" method="post" class="upload_image">

			<input type="hidden" name="MAX_FILE_SIZE" value="52428800" />
		 	<div class="fileUpload btn btn-primary">
		    <span>Upload</span>
		    <input type="file" class="upload" name="image"/>
			</div>
		</form>
	</div>
	<div class="right col-md-4">
		<div class="container_right">
			<button class="buttonPrevious btn btn-primary">Previous</button>
			<button class="buttonNext btn btn-primary">Next</button>
			
			<!--<canvas id="small_canvas" height="500" width="500" data-girar="500"></canvas>-->

			<div class="container_option_base">

				<label id="title_modif">Modification base of bounding box</label><br><br>
				<div class="field_modification_base">
					<div class="field">
						<div class="field_base">
		        			<label id="up_base">Up : </label>
		        			<input type="text" name="up_base" id="up_base-input"/>
		        		</div>
		        		<div class="change_base_icon">
							<span class="glyphicon glyphicon-chevron-up" id="glyph_base_up" ></span><br>
							<span class="glyphicon glyphicon-chevron-down" id="glyph_base_down"></span>
						</div>
		        		<br>
	        		</div>

	        		<div class="field">
						<div class="field_base">
							<label id="down_base">Down : </label>
		        			<input type="text" name="down_base" id="down_base-input"/>
		        		</div>
		        		<div class="change_base_icon">
							<span class="glyphicon glyphicon-chevron-up" id="glyph_base_up" ></span><br>
							<span class="glyphicon glyphicon-chevron-down" id="glyph_base_down"></span>
						</div>
		        		<br>
		        	</div>

		        	<div class="field">
		        		<div class="field_base">
		        		<label id="right_base">Right : </label>
		        		<input type="text" name="right_base" id="right_base-input"/>
		        		</div>
		        		<div class="change_base_icon">
							<span class="glyphicon glyphicon-chevron-up" id="glyph_base_up" ></span><br>
							<span class="glyphicon glyphicon-chevron-down" id="glyph_base_down"></span>
						</div>
		        		<br>
		        	</div>

		        	<div class="field">
		        		<div class="field_base">
		        		<label id="left_base">Left : </label>
		        		<input type="text" name="left_base" id="left_base-input"/>
		        		</div>
		        		<div class="change_base_icon">
							<span class="glyphicon glyphicon-chevron-up" id="glyph_base_up" ></span><br>
							<span class="glyphicon glyphicon-chevron-down" id="glyph_base_down"></span>
						</div>
		        		<br>
		        	</div>
	        	</div>
			</div>
	    </div>
	</div>

</div>
<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.0.min.js" ></script>
<script type="text/javascript" src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" ></script>
<script type="text/javascript" src="manipulate_canvas.js" ></script>
<script type="text/javascript" src="upload_file.js" ></script>

</body>
</html>