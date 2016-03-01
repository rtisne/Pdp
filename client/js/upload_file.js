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
        url: 'uploader.txt',
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
                var url = "data/" + data;
                //init("data/" + data);


                 $.ajax({
                    url: 'getBoundingBox.txt',
                    type: 'POST',
                    success: function(data, textStatus, jqXHR)
                    {
                      console.log(JSON.parse(data));
                      init(url, JSON.parse(data));
                    
                    }
                  });
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