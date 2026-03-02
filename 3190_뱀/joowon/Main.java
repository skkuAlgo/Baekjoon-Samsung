import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        int N; // 보드 크기
        int apple_num; //사과 수
        int[][] apple_loc; //사과 위치
        int turn_num; //회전 수
        int[][] snake_turn; //회전 초,방향
        int time = 0;      

        // Snake
        int dir = 0;
        LinkedList<int[]> list = new LinkedList<int[]>();
        list.add(new int[] {1,1});
        /*
        list.add({1,1}) 은 {1,1}의 타입을 몰라서 에러를 띄움
        new int[]를 통해 타입 명시를 해 줘야 함
        */

        // input 받는 부분
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        apple_num = sc.nextInt();
        apple_loc = new int[apple_num][2];
        for(int i=0; i<apple_num; i++){
            /* 궁금한게 있음
            지금 위치의 경우 3 5 이렇게 주어지는데
            띄어쓰기나 줄바꿈이나 상관 없이 nextInt로 받아도 되는거임??
            */
            apple_loc[i][0] = sc.nextInt();
            apple_loc[i][1] = sc.nextInt();
        }
        turn_num = sc.nextInt();
        snake_turn = new int[turn_num][2];
        for(int i=0; i<turn_num; i++){
            snake_turn[i][0] = sc.nextInt();
            char c = sc.next().charAt(0);
            snake_turn[i][1] = c; //알파벳 걍 aski?로 변환해서 숫자로 저장
        }
        
        sc.close();

        // 보드 상태 
        // 0: 비어있음   1: 사과   2: 뱀(몸통+꼬리)  3:뱀 머리  4:벽벽
        int[][] board = new int[N+2][N+2]; //일케 하면 걍 0으로 채워짐
        for(int i=0; i<apple_num; i++){
            board[apple_loc[i][0]][apple_loc[i][1]] = 1;
        }
        for(int i=0; i<N+1; i++){
            board[0][i] = 4;
            board[i][0] = 4;
            board[i][N+1] = 4;
            board[N+1][i] = 4;
            board[N+1][N+1] = 4;
        }


        // ********* 실제 이동 시작 *********
        int check=0;
        int d = 'D';
        int l = 'L';
        while(true){

            // 회전 시간
            if(time == snake_turn[check][0]){
                //뱀의 원래 이동방향에 따라 달라짐
                if(dir == 0){ //오른쪽                    
                    if(snake_turn[check][1] == d){ //아래 
                        dir=1;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);

                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 1);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 1);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                    if(snake_turn[check][1] == l){ //위
                        dir=3;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);

                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 3);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 3);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                }
                else if(dir == 1){ //아래
                    if(snake_turn[check][1] == d){ //왼쪽
                        dir=2;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);

                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 2);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 2);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                    if(snake_turn[check][1] == l){ //오른쪽 
                        dir=0;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);
                        
                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 0);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 0);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                }
                else if(dir == 2){ //왼쪽
                    if(snake_turn[check][1] == d){ //위 
                        dir=3;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);
                        
                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 3);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 3);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                    if(snake_turn[check][1] == l){ //아래 
                        dir=1;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);
                        
                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 1);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 1);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                }
                else { //위
                    if(snake_turn[check][1] == d){ //오른쪽  
                        dir=0;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);
                        
                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 0);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 0);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                    if(snake_turn[check][1] == l){ //왼쪽 
                        dir=2;
                        int head_row = list.get(0)[0];
                        int head_col = list.get(0)[1];
                        int[] head_loc = checkHead(head_row, head_col, dir);
                        
                        if(board[head_loc[0]][head_loc[1]] == 1){
                            board[head_loc[0]][head_loc[1]]=0;
                            moveSnake(list, 2);
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 4){
                            System.out.println(time+1);
                            break;
                        }
                        else if(board[head_loc[0]][head_loc[1]] == 0){
                            moveSnake(list, 2);
                            if(checkCollapse(list)) {
                                System.out.println(time+1);
                                break;
                            }
                            list.remove(list.size()-1);
                        }
                    }
                }
                if(check<turn_num-1) check++;
            }
            else{
                int head_row = list.get(0)[0];
                int head_col = list.get(0)[1];
                int[] head_loc = checkHead(head_row, head_col, dir);
                        
                if(board[head_loc[0]][head_loc[1]] == 1){
                    board[head_loc[0]][head_loc[1]]=0;
                    moveSnake(list, dir);
                }
                else if(board[head_loc[0]][head_loc[1]] == 4){
                    System.out.println(time+1);
                    break;
                }
                else if(board[head_loc[0]][head_loc[1]] == 0){
                    moveSnake(list, dir);
                    if(checkCollapse(list)) {
                        System.out.println(time+1);
                        break;
                    }
                    list.remove(list.size()-1);
                }
            }
            // printBoard(board,N,list);
            // System.out.println();
            
            time++;
        }
    }

    public static void printBoard(int[][] board, int N, LinkedList<int[]> list){
        // 그냥 board2 = board 하면 둘이 아예 같아짐
        int[][] board2 = new int[board.length][board[0].length];

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                board2[i][j] = board[i][j];
            }
        }

        int len = list.size();
        for(int i=0; i<len; i++){
            board2[list.get(i)[0]][list.get(i)[1]] = 3;
        }

        for(int i=0; i<N+2; i++){
            for(int j=0; j<N+2; j++){
                System.out.print(board2[i][j]);
                System.out.print(" ");
            }
            System.out.println();
        }
        
    }

    // 뱀 이동
    public static void moveSnake(LinkedList<int[]> list, int dir){
        int[] head = {list.get(0)[0], list.get(0)[1]};

        // 오른쪽으로 이동
        if(dir == 0){
            list.add(0, new int[] {head[0], head[1]+1});
        }
        // 아래로 이동
        else if(dir == 1){
            list.add(0, new int[] {head[0]+1, head[1]});
        }
        // 왼쪽으로 이동
        else if(dir == 2){
            list.add(0, new int[] {head[0], head[1]-1});
        }
        //  위로 이동
        else {
            list.add(0, new int[] {head[0]-1, head[1]});
        }
    }

    // 머리 위치 확인
    public static int[] checkHead(int row, int col, int dir){
        //오른쪽으로 이동
        if(dir == 0) col++;
        // 아래로 이동
        else if(dir == 1) row++;
        // 왼쪽으로 이동
        else if(dir == 2) col--;
        //  위로 이동
        else row--;

        return new int[] {row, col};
    }

    // 뱀 몸통 충돌 확인
    public static boolean checkCollapse(LinkedList<int[]> list){
        int row = list.get(0)[0];
        int col = list.get(0)[1];
        int check = 0;

        for(int[] data : list){
            if(data[0] == row && data[1] == col) check++;
        }

        if(check >= 2) return true;
        else return false;
    }
}
