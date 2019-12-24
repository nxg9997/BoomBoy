"use strict";
let fs = require('fs');

console.log("hi");

let canvas = new fabric.Canvas('c', {
    backgroundColor: 'black'
});
let canvasObj = document.querySelector('#c');
canvas.setDimensions({width:window.innerWidth, height:window.innerHeight});

let ctx = canvas.getContext('2d');

let platSelect = document.querySelector("#platform-type");
let polyInput = document.querySelector("#poly-verts");
let addPloy = document.querySelector("#addPoly");
let genOutput = document.querySelector("#genOutput");
let dimInput = document.querySelector("#dimentions");
let changeDim = document.querySelector("#changeDimentions");

changeDim.onmousedown = e => {
    let dims = JSON.parse(dimInput.value);
    canvas.setDimensions({width:dims.width, height:dims.height});
};

genOutput.onmousedown = e => {
    createJSON();
};

addPloy.onmousedown = e => {
    console.log(polyInput.value);
    let tojson = "{\"0\":" + polyInput.value + "}";
    tojson = JSON.parse(tojson);
    console.log(tojson);
    let verts = [];
    for(let i = 0; i < tojson["0"].length; i++){
        verts.push({
            x: tojson["0"][i]["x"],
            y: tojson["0"][i]["y"]
        });
    }
    createPolygon(verts);
};

let gameObjects = [];

readFile("output.json");

/*let line = new fabric.Line([0,0,100,100]);
line.stroke = 'red';
line.strokeWidth = 5;
canvas.add(line);

// create a rectangle object
let rect = new fabric.Rect({
    left: 100,
    top: 100,
    fill: 'red',
    width: 20,
    height: 20
});
  
// "add" rectangle onto canvas
canvas.add(rect);

console.log(rect);
*/

onkeydown = e => {
    console.log(e);
    if(e.key == 'Delete'){
        //console.log("deleting");
        let obj = canvas.getActiveObject();
        //console.log(obj);
        if(obj == null) return;
        let index = -1;
        for(let i = 0; i < gameObjects.length; i++){
            if(gameObjects[i].shape == obj){
                index = i;
                break;
            }
        }
        //console.log(index);
        if(index == -1) return;
        gameObjects.splice(index, 1);
        canvas.remove(obj);
    }
}

onmousedown = e => {
    if(!e.target.classList.contains('upper-canvas')) return;
    if(e.button == 2){
        let scrollLeft = (window.pageXOffset !== undefined) ? window.pageXOffset : (document.documentElement || document.body.parentNode || document.body).scrollLeft;
        let scrollTop = (window.pageYOffset !== undefined) ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
        let go;
        
        if(platSelect.value == "rect"){
            go = new GameObject(0,{x:e.clientX + scrollLeft,y:e.clientY + scrollTop});
        }
        else if(platSelect.value == "complex"){
            
            return;
        }
        gameObjects.push(go);
    }
};

function createJSON(){
    let data = {
        "platforms":[],
        "dimentions":{"width":100,"height":100}
    };
    for(let i = 0; i < gameObjects.length; i++){
        if(gameObjects[i].type == 0){
            data["platforms"].push({
                "name": "p_" + i,
                "type": 0,
                "position": {"x": gameObjects[i].shape.aCoords.tl.x, "y": gameObjects[i].shape.aCoords.tl.y},
                "size": {"x": gameObjects[i].shape.aCoords.tr.x - gameObjects[i].shape.aCoords.tl.x, "y": gameObjects[i].shape.aCoords.br.y - gameObjects[i].shape.aCoords.tr.y}
            });
        }
        else if(gameObjects[i].type == 1){
            data["platforms"].push({
                "name": "c_p_" + i,
                "type": 1,
                "position": {"x": gameObjects[i].shape.aCoords.tl.x, "y": gameObjects[i].shape.aCoords.tl.y},
                "vertices":gameObjects[i].vertices
            });
        }
        
    }
    data["dimentions"].width = canvas.width;
    data["dimentions"].height = canvas.height;
    console.log(data);
    writeFile(data);
    return data;
}

function writeFile(data){
    fs.writeFile("output.json",JSON.stringify(data),()=>{
        console.log("done");
    });
}

function readFile(path){
    fs.readFile(path,(err,data)=>{
        //console.log(data.toString());
        let parsed = JSON.parse(data.toString());
        for(let i = 0; i < parsed["platforms"].length; i++){
            //console.log(parsed["platforms"][i]["vertices"]);
            let verts = null;
            if(parsed["platforms"][i]["vertices"] != undefined){
                verts = parsed["platforms"][i]["vertices"];
            }
            let size = null;
            if(parsed["platforms"][i]["size"] != undefined){
                size = parsed["platforms"][i]["size"];
            }
            let go = new GameObject(parsed["platforms"][i]["type"],parsed["platforms"][i]["position"],verts,size);
            gameObjects.push(go);
        }
        canvas.setDimensions({width:parsed["dimentions"].width, height:parsed["dimentions"].height});
    });
}

function createPolygon(vertices=[]){
    if(vertices.length == 0) return;
    let scrollLeft = (window.pageXOffset !== undefined) ? window.pageXOffset : (document.documentElement || document.body.parentNode || document.body).scrollLeft;
    let scrollTop = (window.pageYOffset !== undefined) ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
    let go = new GameObject(1,{x:100 + scrollLeft,y:100 + scrollTop},vertices);
    gameObjects.push(go);
}

class GameObject{
    constructor(type,pos,vertices=null,size={x:20,y:20}){
        this.type = type;
        this.shape = null;
        if(this.type == 0){
            this.shape = new fabric.Rect({
                left: pos.x,
                top: pos.y,
                fill: 'blue',
                stroke: 'green',
                strokeWidth: 1,
                width: size["x"],
                height: size["y"]
            });
        }
        else if(type == 1){
            //console.log(vertices);
            let polygon = new fabric.Polygon(vertices, {
                left: pos.x,
                top: pos.y,
                fill: 'purple'
            });
            this.vertices = vertices;
            this.shape = polygon;
        }
        canvas.add(this.shape);
    }
}