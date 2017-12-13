package com.phantom;

/**
 * Created by kareem on 12/2/2017.
 */
public class Location {


    Node[][] maze;
    Scanner scanner;
    Stack<Unknown_node> visited;
    LinkedList<Node> couldBe;

    public Location(Node[][] maze) {
        scanner = new Scanner(System.in);
        this.maze = maze;
        System.out.println("enter boards");
        visited = new Stack<Unknown_node>();
        get_reads_from_unknown(enterBoards());
    }

    private void get_reads_from_unknown(char[] reads) {
        boolean check_all_ones = true;
        for (int i = 0; i < reads.length; i++) {
            if (reads[i] == '0') {
                check_all_ones = false;
            }
        }
        if (check_all_ones) {

            //Todo Go to Dwon then Go to left
            System.out.println("go to down to left");
            get_reads_from_unknown(enterBoards());
        } else {
            Unknown_node unkown = new Unknown_node();
            unkown.setBoards(reads);
            unkown.setV_boards();
            visited.push(unkown);
            detect_Location(unkown);
        }


    }


    public void detect_Location(Unknown_node unknown) {

        couldBe  = new LinkedList<Node>();


        for (int i = 0; i < maze.length; i++) {

            for (int j = 0; j < maze[i].length; j++) {


                if (maze[i][j].equals(unknown)) {
                    couldBe.add(maze[i][j]);
                }
            }
        }

        for (Node current:couldBe
                ) {
            System.out.println(current);
        }


        System.out.println(whereToGo((Unknown_node) unknown));


    }


    private char[] enterBoards() {

        String f = scanner.nextLine();
        char[] b = f.toCharArray();


        return b;

    }


    Node whereToGo(Unknown_node unknown) {
        Node m;
        if (unknown.v_boards[1] == 1) {
            m = goRight();
            if (couldBe.size() == 0) {
                return m;
            } else {
                return whereToGo((Unknown_node) m);
            }
        } else if (unknown.v_boards[0] == 1) {
            m = goDwon();
            if (couldBe.size() == 0) {
                return m;
            } else {
                return whereToGo((Unknown_node) m);
            }
        } else if (unknown.v_boards[2] == 1) {
            m = goUp();
            if (couldBe.size() == 0) {
                return m;
            } else {
                return whereToGo((Unknown_node) m);
            }
        } else if (unknown.v_boards[3] == 1) {

            m = goLeft();
            if (couldBe.size() == 0) {
                return m;
            } else {
                return whereToGo((Unknown_node) m);
            }
        } else {
            m=unknown;
            switch (getIndexNotZero(unknown.v_boards)){
                case 0:
                    System.out.println("gotoDwon");
                    visited.pop();
                    return whereToGo( backTodwon());
                case 1:
                    System.out.println("gotoRight");

                    visited.pop();
                    return whereToGo( backToRight());

                case 2:
                    System.out.println("backToUp");
                    visited.pop();
                    return whereToGo( backToUp());

                case 3:
                    System.out.println("back to left");
                    visited.pop();
                    return whereToGo( backToLeft());


                case -1:
                    System.out.println("no place to go ");
                    break;
            }



        }
        return m;
    }


    private int getIndexNotZero(int[] arr) {
        int index = -1;

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > 0) {
                index = i;

            }

        }

        return index;
    }


    private Node goRight() {

        System.out.println("  go right");
        Unknown_node new_unknown = new Unknown_node();
        new_unknown.setBoards(enterBoards());
        new_unknown.setV_boards();
        new_unknown.v_boards[3]++;
        visited.push(new_unknown);
        int size = couldBe.size();
        for (int i = 0; i < size; i++) {

            Node current = couldBe.pop();

            if (maze[current.getmX() + 1][current.getmY()].equals(new_unknown)) {

                couldBe.add(maze[current.getmX() + 1][current.getmY()]);
            }


        }

        if (couldBe.size() == 1) {
            return couldBe.pop();
        }
        return new_unknown;

    }


    private Node goDwon() {

        System.out.println("  go dwon");
        Unknown_node new_unknown = new Unknown_node();
        new_unknown.setBoards(enterBoards());
        new_unknown.setV_boards();
        new_unknown.v_boards[2]++;
        visited.push(new_unknown);
        int size = couldBe.size();
        for (int i = 0; i < size; i++) {
            Node current = couldBe.poll();

            if (maze[current.getmX()][current.getmY() - 1].equals(new_unknown)) {

                couldBe.add(maze[current.getmX()][current.getmY() - 1]);
            }


        }

        if (couldBe.size() == 1) {
            return couldBe.pop();
        }
        return new_unknown;

    }


    Unknown_node backToLeft(){

        Unknown_node back=visited.pop();
        back.v_boards[1]++;

        return back;
    }
    Unknown_node backToUp(){

        Unknown_node back=visited.pop();
        back.v_boards[0]++;

        return back;
    }
    Unknown_node backToRight(){

        Unknown_node back=visited.pop();
        back.v_boards[3]++;

        return back;
    }
    Unknown_node backTodwon(){

        Unknown_node back=visited.pop();
        back.v_boards[2]++;

        return back;
    }
    private Node goLeft() {

        System.out.println("  go left");
        Unknown_node new_unknown = new Unknown_node();
        new_unknown.setBoards(enterBoards());
        new_unknown.setV_boards();
        new_unknown.v_boards[1]++;
        visited.push(new_unknown);
        int size = couldBe.size();
        for (int i = 0; i < size; i++) {
            Node current = couldBe.poll();

            if (maze[current.getmX() - 1][current.getmY()].equals(new_unknown)) {

                couldBe.add(maze[current.getmX() - 1][current.getmY()]);
            }


        }

        if (couldBe.size() == 1) {
            return couldBe.pop();
        }
        return new_unknown;

    }

    private Node goUp() {

        System.out.println("  go up");
        Unknown_node new_unknown = new Unknown_node();
        new_unknown.setBoards(enterBoards());
        new_unknown.setV_boards();
        new_unknown.v_boards[0]++;
        visited.push(new_unknown);
        int size = couldBe.size();
        for (int i = 0; i < size; i++) {
            Node current = couldBe.poll();

            if (maze[current.getmX()][current.getmY() + 1].equals(new_unknown)) {

                couldBe.add(maze[current.getmX()][current.getmY() + 1]);
            }


        }

        if (couldBe.size() == 1) {
            return couldBe.pop();
        }
        return new_unknown;

    }


}

