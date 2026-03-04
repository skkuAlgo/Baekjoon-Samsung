import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt(); //연구소 크기(가로)
        int M = sc.nextInt(); //활성화시킬 바이러스의 수
        int[][] arr = new int[N][N];

        

        int emptyCnt = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                arr[i][j] = sc.nextInt();
                if(arr[i][j] == 0) emptyCnt++;
            }
        }

        sc.close();


        spread(6,6,0,arr,N,emptyCnt);



       
    }

    // x좌표, y좌표, 부모한테서 받은 시간, arr, 배열 가로, 빈칸 수
    public static void spread(int x, int y, int time, int[][] arr, int N, int empty){
        System.out.println("time: " + time);
        showArr(arr,N);
        time++;

        // 상하좌우
        int[] dx = new int[] {1, -1, 0, 0};
        int[] dy = new int[] {0, 0, -1, 1};
        int[] check = new int[4];

        // 상하좌우 확인
        for(int i=0; i<4; i++){
            // 빈공간 -> 바이러스 채움
            if(x+dx[i] < 0 || x+dx[i] >= N || y+dy[i] < 0 || y+dy[i] >= N ){}
            else{
                if(arr[x+dx[i]][y+dy[i]] == 0){
                    arr[x+dx[i]][y+dy[i]] = 3;
                    check[i] = 1;
                }
                // 비활성 바이러스 -> 활성화
                else if(arr[x+dx[i]][y+dy[i]] == 2){
                    arr[x+dx[i]][y+dy[i]] = 3;
                    check[i] = 1;
                }
            }
            
        }

        int count = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(arr[i][j] == 0) count++;
            }
        }

        if(count == 0){
           System.out.println(time); 
           return;
        } 
        if(count == empty){
            System.out.println(time);
            return;
        } 

        for(int i=0; i<4; i++){
            if(check[i] == 1){
                spread(x+dx[i], y+dy[i], time, arr, N, count);
            }
        }
    }

    public static void showArr(int[][] arr, int N){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
}