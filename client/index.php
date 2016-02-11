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

					<a href="#popup" data-toggle="modal" data-target=".bs-example-modal-sm"><span class="glyphicon glyphicon-trash" id="button_trash" aria-hidden="true"></span></a>

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
		
		<canvas id="canvas" width="500" height="500" data-girar="0"></canvas>
		<img class="loader" src="img/loader.gif">
		<form enctype="multipart/form-data" action="" method="post" class="upload_image">

			<input type="hidden" name="MAX_FILE_SIZE" value="52428800" />
		 	<div class="fileUpload btn btn-primary">
		    <span>Upload</span>
		    <input type="file" class="upload" name="image"/>
			</div>
		</form>
	</div>
	<div class="right col-md-4" >
		<div class="container_right" style="display:none;">
			<button class="buttonPrevious btn btn-primary">Previous</button>
			<button class="buttonNext btn btn-primary">Next</button>
			
			<div class="small-canvas">
				<div class="content">
        	<canvas id="small_canvas" data-girar="500"></canvas>
        </div> 
	    </div>

		

			<div class="container_option_base">
				<div class="letter">
					<label id="label_letter">Letter : </label>
		        	<input type="text" name="label_letter" id="letter-input"/>
				</div>

				<br>
				<br>
				<br>

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
		        	<br>
		        	<br>
		        	<span class="glyphicon glyphicon-ok" id="valid_option"></span>
	        	</div>
	        	
	        	
			</div>

	  </div>

	</div>
	<div class="modal fade bs-example-modal-sm" tabindex="-1" role="dialog">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
	        <h4 class="modal-title">Reset</h4>
	      </div>
	      <div class="modal-body">
	        <p>Are you really sure to reset?</p>
	      </div>
	      <div class="modal-footer">
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	        <button id="valid-reset" type="button" class="btn btn-primary">Yes</button>
	      </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->

	</div>

</div>
<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.0.min.js" ></script>
<script type="text/javascript" src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" ></script>
<script type="text/javascript" src="manipulate_canvas.js" ></script>
<script type="text/javascript" src="upload_file.js" ></script>

</body>
</html>