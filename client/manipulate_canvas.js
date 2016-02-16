// Constructeur de la classe ProcessingImage
function ProcessingImage(src) {

    this.img = new Image();
    this.img.src = src;

}

//Dessine l'image
ProcessingImage.prototype.draw = function(ctx) {
    var locx = this.x;
    var locy = this.y;
    ctx.drawImage(this.img,locx,locy);
}

// Determine si un point est dans l'image
ProcessingImage.prototype.contains = function(mx, my) {

  return  (this.x <= mx) && (this.x + (this.w) >= mx) &&
          (this.y <= my) && (this.y + (this.h) >= my);
}


//Constructeur de la baseline
function Baseline(lines) {
    this.lines = lines;
    this.visible = false;

}

Baseline.prototype.draw = function(ctx, image){  
    if(this.visible)
    {
        for (index = 0; index < this.lines.length; index++) {
            ctx.beginPath();
            ctx.moveTo(image.x+ this.lines[index].xstart,image.y + this.lines[index].y);
            ctx.lineTo(image.x + this.lines[index].xfinish,image.y + this.lines[index].y);
            ctx.strokeStyle = '#2ecc71';
            ctx.stroke();
        }   
    }
    
}

function Rectangle(rect){
    this.rect = rect;
    this.color = '#3498db';
    this.selectedColor = '#e74c3c';
    this.visible = true;
    this.selected = false;
}

Rectangle.prototype.draw = function(ctx, image){
    if(this.visible)
    {
        if(this.selected)
            ctx.fillStyle = this.selectedColor;
        else
            ctx.fillStyle = this.color;

        ctx.globalAlpha=0.4;
        ctx.fillRect(image.x + this.rect.x,image.y + this.rect.y, this.rect.w, this.rect.h);

    }
}

//Constructeur de la bounding box
function BoundingBox(rects) {
    this.rects = rects;

}

BoundingBox.prototype.draw = function(ctx, image){
    for (index = 0; index < this.rects.length; index++) {
        this.rects[index].draw(ctx, image);
    }
}
BoundingBox.prototype.contains = function(mx, my, image){
    for (index = 0; index < this.rects.length; index++) {
        if((this.rects[index].rect.x + image.x <= mx) 
            && (this.rects[index].rect.x + image.x + this.rects[index].rect.w >=mx)
            && (this.rects[index].rect.y + image.y <= my) 
            && (this.rects[index].rect.y + image.y + this.rects[index].rect.h >= my))
            return index;
    }
    return 'false';
}
BoundingBox.prototype.select = function (id){
    for (index = 0; index < this.rects.length; index++) {
        this.rects[index].selected = false;
    }
    if(id != 'false')
        this.rects[id].selected = true;
}


function CanvasState(canvas, image, baseline, boundingBox, previewCanvas) {
  
    var myState = this;

    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    this.ctx = canvas.getContext('2d');

    this.image = image;

    this.baseline = baseline;
    this.boundingBox = boundingBox;

    this.previewCanvas = previewCanvas;

    this.dragging = false;

    this.scale = 1.0;

    this.panX = 0;
    this.panY = 0;

    //Coordonnées de la selection sur l'image
    this.dragoffx = 0;
    this.dragoffy = 0;


    this.image.img.onload = function(){
        myState.image.w = this.width;
        myState.image.h = this.height;


        myState.image.initialx = myState.width/2 - this.width/2;
        myState.image.initialy = myState.height/2 - this.height/2;

        myState.image.x = myState.image.initialx;
        myState.image.y = myState.image.initialy;


        if(this.width > this.height)
            myState.scale = myState.width /this.width;
        else
            myState.scale = myState.height /this.height;
    }

   

    canvas.addEventListener('selectstart', function(e) { e.preventDefault(); return false; }, false);
  

    canvas.addEventListener('click', function(e) {

        var mouse = myState.getMouse(e);
        var mx = mouse.x;
        var my = mouse.y;

        var id = myState.boundingBox.contains(mx, my, myState.image);
        if(id != 'false')
        {
            myState.boundingBox.select(id);
            myState.previewCanvas.zoomTo(myState.boundingBox.rects[id]);
            myState.previewCanvas.visible = true;
            $(".container_right").show();
        }
        else
        {
            myState.boundingBox.select('false');
            $(".container_right").hide();
        }

    }, true);
    canvas.addEventListener('mousedown', function(e) {

        var mouse = myState.getMouse(e);
        var mx = mouse.x;
        var my = mouse.y;

        var image = myState.image;

        
        if (image.contains(mx, my)) {
        
            myState.dragoffx = mx - image.x;
            myState.dragoffy = my - image.y;             
            myState.dragging = true;
            return;
          }
    }, true);

    canvas.addEventListener('mousemove', function(e) {
        if (myState.dragging){
            var mouse = myState.getMouse(e);
            image.x = (mouse.x) - myState.dragoffx;
            image.y = (mouse.y) - myState.dragoffy; 
        }
    }, true);

    canvas.addEventListener('mouseup', function(e) {
        myState.dragging = false;
    }, true);

    document.getElementById('zoom-in').addEventListener('click', function(e){
        myState.scale += 0.1;
    }, true);

    document.getElementById('zoom-out').addEventListener('click', function(e){
        myState.scale -= 0.1;
    }, true);
    
    document.getElementById('zoom-reset').addEventListener('click', function(e){
        if(this.width > this.height)
            myState.scale = myState.width /myState.image.w;
        else
            myState.scale = myState.height /myState.image.h;

        myState.image.x = myState.image.initialx;
        myState.image.y = myState.image.initialy;
    }, true);

    document.getElementById('baseline').addEventListener('change', function(e){
        if(this.checked){
            myState.baseline.visible = true;
        }
        else{
            myState.baseline.visible = false;
        }     
    }, true);


    document.getElementById('valid-reset').addEventListener('click', function(e){
              
        var data = new FormData();
        data.append('file', myState.image.img.src);

        $.ajax({
            url: 'remove.php?restart',
            type: 'POST',
            data: data,
            cache: false,
            processData: false, 
            contentType: false,
            success: function(data, textStatus, jqXHR)
            {
                var parsedData = JSON.parse(data);
                if (parsedData == true) {
                    location.reload();
                    console.log("Page réinitialisée.");    
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

    }, true);

    this.interval = 30;
    setInterval(function() { myState.draw(); }, myState.interval);

}


// Efface le canvas pour redessiner
CanvasState.prototype.clear = function() {
  this.ctx.clearRect(0, 0, this.width, this.height);
}

// Dessine le canvas avec ces éléments
CanvasState.prototype.draw = function() {
  if (!this.valid) {
    var ctx = this.ctx;

    var newWidth = this.width * this.scale;
    var newHeight = this.height * this.scale;
    this.panX = -((newWidth-this.width)/2);
    this.panY = -((newHeight-this.height)/2);
    
    this.clear();

    ctx.save();

    ctx.translate(this.panX, this.panY);


    ctx.scale(this.scale, this.scale);
    
    this.image.draw(ctx);

    this.baseline.draw(ctx, this.image);

    this.boundingBox.draw(ctx, this.image);


    this.previewCanvas.draw();

    ctx.restore();

  }
}

// Retourne les coordonnées de la souris
CanvasState.prototype.getMouse = function(e) {
    var rect = this.canvas.getBoundingClientRect();
    var mx = Math.floor((e.clientX-rect.left)/(rect.right-rect.left)*this.canvas.width);
    var my = Math.floor((e.clientY-rect.top)/(rect.bottom-rect.top)*this.canvas.height);

    var mouseXT = parseInt((mx - this.panX) / this.scale);
    var mouseYT = parseInt((my - this.panY) / this.scale);

    return {x: mouseXT, y: mouseYT};
}



function PreviewCanvas(canvas, image)
{
    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    this.ctx = canvas.getContext('2d');

    this.image = image;

    this.visible = false;
    this.scale = 1;


    this.actualRect = null;

    var myPreviewCanvas = this;

    
}

// Efface le canvas pour redessiner
PreviewCanvas.prototype.clear = function() {
    this.ctx.clearRect(0, 0, this.width, this.height);
}
// Dessine le canvas avec ces éléments
PreviewCanvas.prototype.draw = function() {
    if(this.visible)
    {
        var ctx = this.ctx;
        this.clear();
        ctx.save();

        var newWidth = this.width * this.scale;
        var newHeight = this.height * this.scale;
        var panX = -((newWidth-this.width)/2);
        var panY = -((newHeight-this.height)/2);

        ctx.translate(panX, panY);

        ctx.scale(this.scale,this.scale);

        this.image.draw(ctx);

         //UpLine
        ctx.beginPath();
        ctx.moveTo(0, this.image.y + this.actualRect.y);
        ctx.lineTo(this.width, this.image.y + this.actualRect.y);
        ctx.lineWidth = 1 / this.scale;
        ctx.stroke();

        //DownLine
        ctx.beginPath();
        ctx.moveTo(0, this.image.y + this.actualRect.y + this.actualRect.h);
        ctx.lineTo(this.width, this.image.y + this.actualRect.y + this.actualRect.h);
        ctx.lineWidth = 1 / this.scale;
        ctx.stroke();

        //LeftLine
        ctx.beginPath();
        ctx.moveTo(this.image.x + this.actualRect.x, 0);
        ctx.lineTo(this.image.x + this.actualRect.x, this.height);
        ctx.lineWidth = 1 / this.scale;
        ctx.stroke();

        //RightLine
        ctx.beginPath();
        ctx.moveTo(this.image.x + this.actualRect.x + this.actualRect.w, 0);
        ctx.lineTo(this.image.x + this.actualRect.x + this.actualRect.w, this.height);
        ctx.lineWidth = 1 / this.scale;
        ctx.stroke();
    
        ctx.restore();

       
    }
   
}
PreviewCanvas.prototype.zoomTo = function(rect){

    this.image.x = (this.width/2) - rect.rect.x - rect.rect.w/2;
    this.image.y = (this.height/2) - rect.rect.y - rect.rect.h/2;
    if(rect.rect.w > rect.rect.h)
        this.scale = this.width /rect.rect.w - rect.rect.w / 37;
    else
        this.scale = this.height /rect.rect.h - rect.rect.h / 37;
    this.actualRect = rect.rect;
}

function init(src) {
    var image = new ProcessingImage(src);
    var imagePreview = new ProcessingImage(src);
    var baseline = new Baseline([{xstart:50, y:90, xfinish:560}, {xstart:50, y:130, xfinish:570}]);
    var box1 = new Rectangle({x:50, y:60, w:30, h: 30});
    var box2 = new Rectangle({x:82, y:70, w:18, h: 20});
    var box3 = new Rectangle({x:102, y:68, w:16, h: 22});
    var boundingBox = new BoundingBox([box1, box2, box3]);



    var previewCanvas = new PreviewCanvas(document.getElementById('small_canvas'), imagePreview);
    var normalCanvas = new CanvasState(document.getElementById('canvas'), image, baseline, boundingBox, previewCanvas);
    

}







