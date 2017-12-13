package com.phantom;

import java.util.Scanner;

/**
 * Created by kareem on 11/29/2017.
 */
public class Node {

    Scanner scanner;
    private int mX;
    private int mY;

    // 0 for down  v
    //1 for right >>
    // 2 for up ^
    //3 for left <<
    char[] boards;


    public Node(){

        scanner =new Scanner(System.in);
        boards=new char[4];
        setBoardsFalse();

    }
    public Node(int x,int y){
        mX=x;
        mY=y;
        scanner =new Scanner(System.in);
        boards=new char[4];
        setBoardsFalse();

    }
    private  void setBoardsFalse(){
        for (int i=0;i<boards.length;i++){
            boards[i]='0';
        }
    }

    public int getmX() {
        return mX;
    }


    public int getmY() {
        return mY;
    }

    public char[] getBoards() {
        return boards;
    }






    public void setBoards(char[] boards) {

        this.boards=boards;
    }




    @Override
    public boolean equals(Object obj) {
        Node current = (Node) obj;
        for (int i = 0; i < 4; i++) {

            if (this.boards[i] != current.boards[i]) {
                return false;
            }
        }


        return true;
    }

    @Override
    public String toString() {
        return this.getmX()+" , " +this.getmY();
    }
}
class  Unknown_node extends Node{


    int[] v_boards;
    Unknown_node(){
        v_boards=new int[4];
    }

    public    void setV_boards(){
        char []c=this.getBoards();

        for(int i=0;i<this.getBoards().length;i++){

            v_boards[i]=Character.getNumericValue(c[i]);}

    }



}
