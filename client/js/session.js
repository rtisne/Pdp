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
      callback(imagePath, JSON.parse(data).boundingbox, JSON.parse(data).baseline);
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



Session.prototype.getInfoOnCC = function(id, idCC, idLine, callback)
{
    console.log(idCC + ":" + idLine);
	$.ajax({
    url: 'getInfoOnCC.txt',
    type: 'POST',
    data: "token=" + this.token + "&idCC=" + idCC +"&idLine="+ idLine,
    context: callback,
    success: function(data, textStatus, jqXHR)
    {
    	var info = JSON.parse(data);
    	callback.manipulateInfos(id, info.left, info.right, info.up, info.down, info.letter, info.baseline);
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}

Session.prototype.updateInfoOnCC = function(activeId, activeLine, jsonId, ids, left, right, up, down, baseline,letter)
{
	$.ajax({
    url: 'updateInfoOnCC.txt',
    type: 'POST',
    data: "token=" + this.token + "&activeid=" + activeId + "&activeline=" + activeLine + "&id=" + jsonId + "&left=" + left + "&right=" + right + "&up=" + up + "&down=" + down + "&baseline=" + baseline + "&letter=" + letter,
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

Session.prototype.extractFont = function(fontname)
{
	$.ajax({
    url: 'extractFont.txt',
    type: 'POST',
    data: "token=" + this.token +"&fontname=" + fontname,
    success: function(data, textStatus, jqXHR)
    {
        var file = new Blob([data], {type: "text/plain;charset=utf-8"});
        saveAs(file, fontname + ".of");
        

        $('#saveModal').modal('hide');
		  
    },
    error: function(error)
    {
 			console.log('ERRORS: ' + error);
    }
	});
}
Session.prototype.updateBaseline = function(idLine, value)
{
    $.ajax({
    url: 'updateBaseline.txt',
    type: 'POST',
    data: "token=" + this.token +"&idLine=" + idLine + "&value=" + value,
    success: function(data, textStatus, jqXHR)
    {
          
    },
    error: function(error)
    {
            console.log('ERRORS: ' + error);
    }
    });
}