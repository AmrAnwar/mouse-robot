package com.phantom;

import java.util.Scanner;

/**
 * Created by kareem on 11/30/2017.
 */
public class Maze {
    private  Node[][] mMaze;
    public Maze(){
        mMaze=new Node[8][8];
    }
    public  Node[][] getMaze(){
        return mMaze;
    }

    public void loadMaze(){
        //ToDo load maze from big string or file

        for (int i=0;i<8;i++){
            for(int j=0;j<8;j++) {

                mMaze[i][j] = new Node(i,j);
                setBoards(mMaze[i][j]);
            }

        }

    }
    Scanner m =new Scanner(System.in);


    private void setBoards(Node current){

        String f = m.nextLine();
        char[] boards = f.toCharArray();

        current.setBoards(boards);

    }

}



