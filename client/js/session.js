function Session() {
	this.token;
	var that = this;
}

Session.prototype.startSession = function(file, callback)
{
	$.ajax({
    url: 'uploader.txt',
    type: 'POST',
    data: file,
    cache: false,
    processData: false,
    contentType: false,
    context : this,
    success: function(responseJson, textStatus, jqXHR)
    {
    	var response = JSON.parse(responseJson);
    	if(response.error == null)
    	{
    		this.token = response.token;
    		callback(response.fileName);
    	}
    },
    error: function(jqXHR, textStatus, errorThrown)
    {
        console.log('ERRORS: ' + textStatus);
    }
  });
}

Session.prototype.imageInfos = function(filename, callback)
{
	console.log(this.token);
	var imagePath = "data/" + filename;
	$.ajax({
    url: 'getBoundingBox.txt',
    type: 'POST',
    data: "token=" + this.token,
    success: function(data, textStatus, jqXHR)
    {
      console.log(JSON.parse(data));
      $('#canvas').show();
      $('.zoom-icon').show();
      $('.navbar-nav').show();
      
      $('.loader').hide();
      callback(imagePath, JSON.parse(data));
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}

Session.prototype.removeSession = function()
{
	$.ajax({
    url: 'stopSession.txt',
    type: 'POST',
    data: "token=" + this.token,
    async: false,
    success: function(data, textStatus, jqXHR)
    {
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}



Session.prototype.getInfoOnCC = function(id, callback)
{
	console.log(id);
	$.ajax({
    url: 'getInfoOnCC.txt',
    type: 'POST',
    data: "token=" + this.token + "&id=" + id,
    context: callback,
    success: function(data, textStatus, jqXHR)
    {
    	var info = JSON.parse(data);
    	callback.manipulateInfos(info.id, info.left, info.right, info.up, info.down, info.letter);
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}

Session.prototype.updateInfoOnCC = function(activeId, ids, left, right, up, down, letter)
{
	var jsonId = "{";
	for	(index = 0; index < ids.length; index++) {
    jsonId += "\"" + ids[index] + "\":" + ids[index];
    if(index < ids.length-1)
    {
    	jsonId += ",";
    }
	}
	jsonId += "}";
	$.ajax({
    url: 'updateInfoOnCC.txt',
    type: 'POST',
    data: "token=" + this.token + "&activeid=" + activeId + "&id=" + jsonId + "&left=" + left + "&right=" + right + "&up=" + up + "&down=" + down + "&letter=" + letter,
    success: function(data, textStatus, jqXHR)
    {
    	console.log(data);
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}