function Controller(canvas, previewCanvas) {
    this.canvas = canvas;
    this.previewCanvas = previewCanvas;

    var controller = this;

    // Initialisation
    $(".container_right").show();
    $('#baseline_options').hide();
    this.canvas.boundingBox.select(0);
    this.previewCanvas.zoomTo(this.canvas.boundingBox.rects[0], 0);
    this.previewCanvas.visible = true;


    
    canvas.canvas.addEventListener('selectstart', function(e) { e.preventDefault(); return false; }, false);
    canvas.canvas.addEventListener('click',function(e) { 
        var mouse = controller.canvas.getMouse(e);
        var mx = mouse.x;
        var my = mouse.y;

        // Check if we clic on a BoundingBox
        var id = controller.canvas.boundingBox.contains(mx, my, controller.canvas.image);
        if(id != 'false')
        {   
            $("#letter_options").show();
            $('#baseline_options').hide();
            controller.canvas.baseline.select("false");
            var mergeButton = document.getElementById("mergeButton");
            if(e.metaKey)
            {
                controller.canvas.boundingBox.addToSelection(id);
                mergeButton.disabled=false;
            }
            else
            {
                controller.canvas.boundingBox.select(id);
                session.getInfoOnCC(id, controller);
            }    
        }
        // Check if we clic on a Baseline
        var id = controller.canvas.baseline.contains(mx, my, controller.canvas.image);
        if(id != 'false')
        {
            controller.canvas.boundingBox.select("false");
            controller.canvas.baseline.select(id);
            $('#letter_options').hide();
            $('#baseline_options').show();
            controller.previewCanvas.zoomTo(controller.canvas.baseline.lines[id], id);
            controller.previewCanvas.visible = true;

        }  

    }, true);

    // Détection Déplacement de l'image
    canvas.canvas.addEventListener('mousedown', function(e) { canvas.onMouseDown(e); }, true);
    canvas.canvas.addEventListener('mousemove', function(e) { canvas.onMouseMove(e);}, true);
    canvas.canvas.addEventListener('mouseup', function(e) { canvas.onMouseUp(e);}, true);
    
    // Détection zoom
    document.getElementById('zoom-in').addEventListener('click', function(e){ canvas.zoomIn();}, true);
    document.getElementById('zoom-out').addEventListener('click', function(e){ canvas.zoomOut();}, true);
    document.getElementById('zoom-reset').addEventListener('click', function(e){ canvas.zoomReset();}, true);

    // Détection checkbox baseline
    document.getElementById('baseline').addEventListener('change', function(e){
        if(this.checked){
            controller.canvas.baseline.visible = true;
        }
        else{
            controller.canvas.baseline.visible = false;
        }     
    }, true);

    //Déplacement de la base UP du caractère
    document.getElementById('up').addEventListener('change', function(e){
        controller.previewCanvas.position_up_line = parseFloat($("#up").val());
    }, true);

    //Déplacement de la base DOWN du caractère
    document.getElementById('down').addEventListener('change', function(e){
        controller.previewCanvas.position_down_line = parseFloat($("#down").val());
    }, true);

    //Déplacement de la base LEFT du caractère
    document.getElementById('left').addEventListener('change', function(e){
        controller.previewCanvas.position_left_line = parseFloat($("#left").val());
    }, true);

    //Déplacement de la base RIGHT du caractère
    document.getElementById('right').addEventListener('change', function(e){
        controller.previewCanvas.position_right_line = parseFloat($("#right").val());
    }, true);

    //Appui sur le boutton save
    document.getElementById('save').addEventListener('click', function(e){
        session.updateInfoOnCC(controller.previewCanvas.ccSelected, parseFloat($("#left").val()), parseFloat($("#right").val()),  parseFloat($("#up").val()), parseFloat($("#down").val()), $("#letter").val());
    }, true);



    // Détection boutton reset
    document.getElementById('button_trash').addEventListener('click', function(e){
        session.removeSession();
        

    }, true);
    window.onunload = function() { 
       session.removeSession();
    };

    // Affichage
    this.interval = 30;
    setInterval(function() { controller.draw(); }, controller.interval);

}

Controller.prototype.draw = function(){
    this.canvas.draw();
    this.previewCanvas.draw();

}


Controller.prototype.manipulateInfos = function manipulateInfos(id, left, right, up, down, letter){
    this.previewCanvas.zoomTo(this.canvas.boundingBox.rects[id], id);
    this.previewCanvas.visible = true;
    this.previewCanvas.position_up_line = up;
    this.previewCanvas.position_down_line = down;
    this.previewCanvas.position_left_line = left;
    this.previewCanvas.position_right_line = right;
    if(letter == "null")
        $("#letter").val("");
    else
        $("#letter").val(letter);

    $("#up").val(up);
    $("#down").val(down);
    $("#left").val(left);
    $("#right").val(right);

    mergeButton.disabled="disabled";
}

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

function Line(startx, y, finishx){
    this.startx = startx;
    this.y = y;
    this.finishx = finishx;
    this.selected = false;
}

Line.prototype.draw = function(ctx, image){
    ctx.beginPath();
    ctx.moveTo(image.x+ this.startx, image.y + this.y);
    ctx.lineTo(image.x + this.finishx, image.y + this.y);
    if(this.selected)
        ctx.strokeStyle = '#e74c3c';
    else
        ctx.strokeStyle = '#2ecc71';
    ctx.stroke();
}

//Constructeur de la baseline
function Baseline(lines) {
    this.lines = lines;
    this.visible = false;
    this.clickMargin = 0.4; //in percent of the image height

}

Baseline.prototype.draw = function(ctx, image){  
    if(this.visible)
    {
        for (index = 0; index < this.lines.length; index++) {
            this.lines[index].draw(ctx, image);
        }   
    }
    
}
Baseline.prototype.contains = function(mx, my, image){
    if(this.visible == false)
        return "false";
    for (index = 0; index < this.lines.length; index++) {
        if((this.lines[index].startx + image.x <= mx)
            && (this.lines[index].finishx + image.x >= mx)
            && (this.lines[index].y + image.y - (this.clickMargin * image.h / 100) <= my)
            && (this.lines[index].y + image.y + (this.clickMargin * image.h / 100) >= my))
            return index;
    }
    return 'false';
}

Baseline.prototype.select = function (id){
    for (index = 0; index < this.lines.length; index++) {
        this.lines[index].selected = false;
    }
    if(id != 'false')
        this.lines[id].selected = true;
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
BoundingBox.prototype.addToSelection = function (id){
    if(id != 'false')
        this.rects[id].selected = true;
}

function CanvasState(canvas, image, baseline, boundingBox) {
  
    var myState = this;

    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    this.ctx = canvas.getContext('2d');

    this.image = image;

    this.baseline = baseline;
    this.boundingBox = boundingBox;

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

}

CanvasState.prototype.onMouseDown= function(e){
    var mouse = this.getMouse(e);
    var mx = mouse.x;
    var my = mouse.y;

    var image = this.image;

    
    if (image.contains(mx, my)) {
    
        this.dragoffx = mx - image.x;
        this.dragoffy = my - image.y;             
        this.dragging = true;
        return;
      }
}

CanvasState.prototype.onMouseMove = function(e){
    if (this.dragging){
        var mouse = this.getMouse(e);
        this.image.x = (mouse.x) - this.dragoffx;
        this.image.y = (mouse.y) - this.dragoffy; 
    }
}

CanvasState.prototype.onMouseUp = function(e){
    this.dragging = false;
}

CanvasState.prototype.zoomIn = function(){
    this.scale += 0.1;
}
CanvasState.prototype.zoomOut = function(){
    this.scale -= 0.1;
}
CanvasState.prototype.zoomReset = function(){
    if(this.width > this.height)
        this.scale = this.width /this.image.w;
    else
        this.scale = this.height /this.image.h;

    this.image.x = this.image.initialx;
    this.image.y = this.image.initialy;
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
    this.scaleX = 1;
    this.scaleY = 1;

    this.isBaseline = false;

    this.position_up_line = 0;
    this.position_down_line = 0;
    this.position_left_line = 0;
    this.position_right_line = 0;
    this.position_baseline = 0;

    this.ccSelected = 0;

    

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

        var newWidth = this.width * this.scaleX;
        var newHeight = this.height * this.scaleY;
        var panX = -((newWidth-this.width)/2);
        var panY = -((newHeight-this.height)/2);

        ctx.translate(panX, panY);

        ctx.scale(this.scaleX,this.scaleY);

        this.image.draw(ctx);
        
        if(this.isBaseline)
        {
            //Baseline
            ctx.beginPath();
            ctx.moveTo(0, this.position_baseline);
            ctx.lineTo(this.width, this.position_baseline);
            ctx.lineWidth = 1;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();
        }
        else
        {
            //UpLine
            ctx.beginPath();
            ctx.moveTo(0, this.image.y + this.position_up_line);
            ctx.lineTo(this.width, this.image.y + this.position_up_line);
            ctx.lineWidth = 1 / this.scaleY;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();

            //DownLine
            ctx.beginPath();
            ctx.moveTo(0, this.image.y + this.position_down_line);
            ctx.lineTo(this.width, this.image.y + this.position_down_line);
            ctx.lineWidth = 1 / this.scaleY;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();

            //LeftLine
            ctx.beginPath();
            ctx.moveTo(this.image.x + this.position_left_line, 0);
            ctx.lineTo(this.image.x + this.position_left_line, this.height);
            ctx.lineWidth = 1 / this.scaleX;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();

            //RightLine
            ctx.beginPath();
            ctx.moveTo(this.image.x + this.position_right_line, 0);
            ctx.lineTo(this.image.x + this.position_right_line, this.height);
            ctx.lineWidth = 1 / this.scaleX;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();
        }
        ctx.restore();

       
    }
   
}
PreviewCanvas.prototype.zoomTo = function(obj, id){

    if(obj instanceof Rectangle)
    {
        this.ccSelected = id;
        var rect = obj;
        this.image.x = (this.width/2) - rect.rect.x - rect.rect.w/2;
        this.image.y = (this.height/2) - rect.rect.y - rect.rect.h/2;
        if(rect.rect.w > rect.rect.h)
            this.scaleX = this.width /rect.rect.w - rect.rect.w / 37;
        else
            this.scaleX = this.height /rect.rect.h - rect.rect.h / 37;

        this.scaleY = this.scaleX;
        var actualRect = rect.rect;
        this.isBaseline = false; 
    }
    else if (obj instanceof Line)
    {
        var line = obj;
        this.image.x = (this.width/2) - ((line.finishx - line.startx)/2 + line.startx);
        this.image.y = (this.height/2) - line.y;

        this.scaleX = this.width /(line.finishx - line.startx);
        this.scaleY = this.height / (this.image.img.height / 20);

        this.isBaseline = true;
        this.position_baseline = this.image.y + line.y;
    }
    
}

function init(src, boundingBox) {
    var image = new ProcessingImage(src);
    var imagePreview = new ProcessingImage(src);
    var baseline = new Baseline([new Line(50, 90, 560), new Line(50, 130, 570)]);

    var listRect = new Array();
    for (var rect in boundingBox) {
        listRect.push(new Rectangle({x:boundingBox[rect].x, y:boundingBox[rect].y, w:boundingBox[rect].width, h: boundingBox[rect].height}));
    }

    var boundingBox = new BoundingBox(listRect);



    var previewCanvas = new PreviewCanvas(document.getElementById('small_canvas'), imagePreview);
    var normalCanvas = new CanvasState(document.getElementById('canvas'), image, baseline, boundingBox);

    var controller = new Controller(normalCanvas, previewCanvas);
}







