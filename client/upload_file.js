var files;

$('input[type=file]').on('change', prepareUpload);

function prepareUpload(event)
{
  files = event.target.files;

  event.stopPropagation(); // Stop stuff happening
    event.preventDefault(); // Totally stop stuff happening

    // START A LOADING SPINNER HERE

    // Create a formdata object and add the files
    var data = new FormData();
    $.each(files, function(key, value)
    {
        data.append(key, value);
    });
    $('form').hide();
    $('.loader').show();
    $.ajax({
        url: 'upload.php?image',
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
                $('.navbar-right').show();
                $('.container_right').show();
                
                $('.loader').hide();
                var parsedData = JSON.parse(data);
                console.log(parsedData['files']);
                console.log(parsedData);
                init(parsedData['files']);
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