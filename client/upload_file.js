var files;

$('input[type=file]').on('change', prepareUpload);

function prepareUpload(event)
{
  files = event.target.files;

  event.stopPropagation(); 
    event.preventDefault(); 
    var data = new FormData();
    $.each(files, function(key, value)
    {
        data.append(key, value);
    });
    $('form').hide();
    $('.loader').show();
    $.ajax({
        url: 'uploader.txt',
        type: 'POST',
        data: data,
        cache: false,
        processData: false, // Don't process the files
        contentType: false, // Set content type to false as jQuery will tell the server its a query string request
        success: function(data, textStatus, jqXHR)
        {
            if(typeof data.error === 'undefined')
            {
                $('#canvas').show();
                $('.zoom-icon').show();
                $('.navbar-nav').show();
                
                $('.loader').hide();
                init("data/" + data);
            }    
            else
            {
                // Handle errors here
                console.log('ERRORS: ' + data.error);
            }
        },
        error: function(jqXHR, textStatus, errorThrown)
        {
            // Handle errors here
            console.log('ERRORS: ' + textStatus);
            // STOP LOADING SPINNER
        }
      });
}