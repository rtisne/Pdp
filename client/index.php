<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Document</title>
	<link href="style.css" rel="stylesheet">
	<link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
	<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.0.min.js" ></script>
	<script type="text/javascript" src="init.js" ></script>

</head>
<body>
<div class="row header">
	<div class="col-md-2">
		<button class="btn btn-default" type="submit"><span class="glyphicon glyphicon-flash" aria-hidden="true"></span></button>
		
	</div>
	<div class="col-md-4">
		<div class="btn-group" data-toggle="buttons">
		  <label class="btn btn-primary active">
		    <input type="radio" name="options" id="option1" autocomplete="off" checked> Connexe Hull
		  </label>
		  <label class="btn btn-primary">
		    <input type="radio" name="options" id="option2" autocomplete="off"> Bounding Box
		  </label>
		</div>
	</div>
</div>
<div class="row processing">
	<div class="left col-md-8">
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
		
	</div>

</div>

<script type="text/javascript" src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" ></script>
<script type="text/javascript" src="manipulate_canvas.js" ></script>
<script type="text/javascript" src="upload_file.js" ></script>
</body>
</html>