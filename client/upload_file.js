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

    $('.fileUpload').hide();
    $('.loader').show();

    $.ajax({
        url: 'upload.php?image',
        type: 'POST',
        data: data,
        cache: false,
        processData: false,
        contentType: false,
        success: function(data, textStatus, jqXHR)
        {
            if(typeof data.error === 'undefined')
            {
                $('#canvas').show();
                $('.zoom-icon').show();
                $('.navbar-nav').show();
                
                $('.loader').hide();
                var parsedData = JSON.parse(data);
                console.log(parsedData['files']);
                init(parsedData['files']);
            }
            else
            {
                console.log('ERRORS: ' + data.error);
            }
        },
        error: function(jqXHR, textStatus, errorThrown)
        {
            console.log('ERRORS: ' + textStatus);
        }
      });
}