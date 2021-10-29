class Voiture{
    constructor(cell){
        this.cell = cell;
    }



    show(){
        fill(255,0,0);
        rect(this.cell.i * res , (this.cell.j *res) + res/4 , res, res/2);
    }
}