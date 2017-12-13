package com.phantom;

import java.util.Scanner;

public class Main {
    static Scanner scanner;
    public static void main(String[] args) throws Exception {
        scanner=new Scanner(System.in);
        Maze myMaze= new Maze();
        myMaze.loadMaze();
        Node[][] maze=myMaze.getMaze();
        Location location=new Location(maze);




    }


}
