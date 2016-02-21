<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Pdp client</title>
	<link href="style.css" rel="stylesheet">
	<link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
	<link href="css/normalize.css" rel="stylesheet">
	
</head>
<body class="fill-height">
	<nav class="navbar navbar-default">
		<div class="container-fluid">
			<div class="navbar-header">
				<a class="navbar-brand" href="#">PDP</a>
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
						<a href="#"><span class="glyphicon glyphicon-export" aria-hidden="true"></span></a>
					</li>
					<li>

						<a href="#popup" data-toggle="modal" data-target=".bs-example-modal-sm"><span class="glyphicon glyphicon-plus" id="button_trash" aria-hidden="true"></span></a>

					</li>
				</ul>
			</div>
		</div>
	</nav>
	<div class="processing">
		<div class="inside">

			<div class="left">
				<div class="zoom-icon">
					<span class="glyphicon glyphicon-zoom-in" id="zoom-in"></span><br>
					<span class="glyphicon glyphicon-zoom-out" id="zoom-out"></span><br>
					<span class="glyphicon glyphicon-repeat" id="zoom-reset"></span>
				</div>

				<canvas id="canvas" width="500" height="500" data-girar="0"></canvas>
				<img class="loader" src="img/loader.gif">
				<div class="fileUpload btn btn-primary">
					<span>Upload</span>
					<input type="file" class="upload" name="image"/>
				</div>
			</div>
			<div class="right">
				<div class="container_right">
					<div class="right_up">
						<div class="button_nav_cc row">
							<div class="col-md-3">
								<button class="buttonPrevious btn btn-primary">Previous</button>
							</div>
							<div class="col-md-3 col-md-offset-6">
								<button class="buttonNext btn btn-primary">Next</button>
							</div>		
						</div>
						
						<div class="small-canvas">
							<div class="content">
								<canvas id="small_canvas" data-girar="500"></canvas>
							</div> 
						</div>



						<div class="container_option_base">
							<div class="row">
							  
					      <div class="input-group col-sm-6 col-sm-offset-1">
					        <input class="form-control" type="text" value="" placeholder="" name="q">
					        <div class="input-group-btn">
					          <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><span id="mydropdowndisplay">Letter</span> <span class="caret"></span></button>
					          <ul class="dropdown-menu" id="mydropdownmenu">
					            <li><a href="#">Letter</a></li>
					            <li><a href="#">Unicode</a></li>
					          </ul>
					          <input type="hidden" id="mydropwodninput" name="category">
					        </div>
					      </div>
								<div class="col-sm-3 add-button">
									<button type="button" class="btn btn-primary">Add</button>
								</div>
							</div>

							<div class="field_modification_base">
								<div class="row">
								  <div class="form-group col-sm-5 col-sm-offset-1 modif-line-value">
								  	<div class="group">
								  		<label class="sr-only" for="up"></label>
									    <div class="input-group">
									      <div class="input-group-addon">Up</div>
									      <input type="number" class="form-control" id="up">
									    </div>
								  	</div> 
								  </div>
								  <div class="form-group col-sm-5 modif-line-value">
								    <label class="sr-only" for="down"></label>
								    <div class="input-group">

								      <div class="input-group-addon">Down</div>
								      <input type="number" class="form-control" id="down">
								    </div>
								  </div>
								</div>		
								<div class="row">
								  <div class="form-group col-sm-5 col-sm-offset-1 modif-line-value">
								    <label class="sr-only" for="left"></label>
								    <div class="input-group">
								      <div class="input-group-addon">Left</div>
								      <input type="number" class="form-control" id="left">
								    </div>
								  </div>
								  <div class="form-group col-sm-5 modif-line-value">
								    <label class="sr-only" for="up"></label>
								    <div class="input-group">
								      <div class="input-group-addon">Right</div>
								      <input type="number" class="form-control" id="right">
								    </div>
								  </div>
								</div>		
							</div>
						

						</div>
						
					</div>
					<div class="right_down">
						<ul class="row letter-list">
							<li class="col-sm-15">A <span class="pull-right letter-number">45</span></li>
							<li class="col-sm-15">F <span class="pull-right letter-number">67</span></li>
							<li class="col-sm-15">Q <span class="pull-right letter-number">33</span></li>
							<li class="col-sm-15">P <span class="pull-right letter-number">35</span></li>
							<li class="col-sm-15">311C <span class="pull-right letter-number">4</span></li>
							<li class="col-sm-15">V <span class="pull-right letter-number">56</span></li>
							<li class="col-sm-15">36BE <span class="pull-right letter-number">3</span></li>
							<li class="col-sm-15">G <span class="pull-right letter-number">9</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
							<li class="col-sm-15">R <span class="pull-right letter-number">84</span></li>
						</ul>
					</div>
					
				</div>

			</div>
			<div class="modal fade bs-example-modal-sm" tabindex="-1" role="dialog">
				<div class="modal-dialog">
					<div class="modal-content">
						<div class="modal-header">
							<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
							<h4 class="modal-title">New</h4>
						</div>
						<div class="modal-body">
							<p>Have you save your previous work ?</p>
						</div>
						<div class="modal-footer">
							<button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
							<button id="valid-reset" type="button" class="btn btn-primary">Yes</button>
						</div>
					</div>
				</div>

			</div>
			<div class="modal fade" tabindex="-1" role="dialog" id="baseline_modal">
			  <div class="modal-dialog">
			    <div class="modal-content">
			      <div class="modal-header">
			        <h4 class="modal-title">Baseline validation</h4>
			      </div>
			      <div class="modal-body">
			        <img src="images/image.png" width="300">
			      </div>
			      <div class="modal-footer">
			        <button type="button" class="btn btn-primary">Save changes</button>
			      </div>
			    </div>
			  </div>
			</div>
		</div>
	</div>
	<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.0.min.js" ></script>
	<script type="text/javascript" src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" ></script>
	<script type="text/javascript" src="manipulate_canvas.js" ></script>
	<script type="text/javascript" src="init.js" ></script>
	<script type="text/javascript" src="upload_file.js" ></script>

</body>
</html>