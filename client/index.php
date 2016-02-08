<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Document</title>
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
					<a href="#"><span class="glyphicon glyphicon-trash" aria-hidden="true"></span></a>
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
		
	</div>

</div>
<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.0.min.js" ></script>
<script type="text/javascript" src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" ></script>
<script type="text/javascript" src="manipulate_canvas.js" ></script>
<script type="text/javascript" src="upload_file.js" ></script>
</body>
</html>