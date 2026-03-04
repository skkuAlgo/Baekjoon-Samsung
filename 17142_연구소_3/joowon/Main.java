import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt(); //연구소 크기(가로)
        int M = sc.nextInt(); //활성화시킬 바이러스의 수
        int[][] map = new int[N][N];
        ArrayList<int[]> virus = new ArrayList<>();
        int emptyCount = 0;

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                map[i][j] = sc.nextInt();
                // 바이러스들 좌표 저장
                if(map[i][j] == 2) virus.add(new int[]{i,j});
                if(map[i][j] == 0) emptyCount++;
            }
        }
        sc.close();

        if(emptyCount == 0){
            System.out.println(0);
            return;
        }

        ArrayList<ArrayList<int[]>> combList = new ArrayList<>();
        combination(virus, M, 0, new ArrayList<>(), combList);

        int result = 1000000000;
        int checkFirst = 0;

        for(int a=0; a<combList.size(); a++){
            int[][] arr = new int[N][N];
            for (int i = 0; i < N; i++) {
                arr[i] = map[i].clone();
            }
            // 실제로 돌릴 list
            ArrayList<int[]> list = new ArrayList<>();

            for(int b=0; b<combList.get(a).size(); b++){
                list.add(new int[]{combList.get(a).get(b)[0],combList.get(a).get(b)[1]});
            }

            for(int i=0; i<list.size(); i++){
                arr[list.get(i)[0]][list.get(i)[1]] = 3;
            }

            int time=-1;
            int checkEmpty = emptyCount;
            while(true){
                time++;
                // System.out.println("time: " + time);
                // System.out.println("result:  "+result);
                // showArr(arr,N);
                
                int size = list.size();
                int exCheck = checkEmpty;

                // 1차 오류 : for문 안에서 list.size()를 했는데, 그럼 매 for문마다 새로 계산된다고 함
                for(int i=0; i<size; i++){
                    checkEmpty = spread(list.get(i), arr, N, list, checkEmpty);
                    // 마지막에 list에서 자기 자신 빼줘야 함
                    // list.remove(0);
                }
                list.subList(0,size).clear();
                
                // 2차 오류 : 마지막에 제대로 퍼져서 (list에는 마지막에 퍼졌던 애들이 남아있는데) 
                //           마무리 된 경우 size가 0이 아니라서 한 번 더 돌고 끝남.
                // 3차 오류... : 처음부터 다 채워진 경우에는.... ... ... (순서 바꿔줌! - 더 이상 채울게 없는걸 확인하는 부분이랑)
                

                // 다 채우면
                if(checkEmpty <= 0){
                    // System.out.println("checkEmpty"+ checkEmpty);
                    checkFirst++;
                    // System.out.println("checkFirst"+ checkFirst);
                    // System.out.println();
                    time++;
                    break;
                }

                // 계속 반복(긍까 마무리가 안 되는 경우)
                if (list.size() == 0) {
                    time = -1;
                    break;
                }

                
                // 4차 오류 : 여러 경우의 수 중, 가능한 경우도 있을건데,
                //           지금은 안 채워지는 경우가 발생하면 -> time을 -1로 설정해버림
                
            }

            // 채워지는 경우가 있음
            if(checkFirst > 0){
                if(checkFirst == 1) {
                    if(time == -1){}
                    else{
                        result = time; 
                    }
                }
                else{
                    if(time == -1){}
                    else{
                        if(time<result) result = time;
                    }
                }                
            }
            else{ // 채워지는 경우가 없음 (-1)
                result = -1;
            }

        }
        
        System.out.println(result);
    }


    public static int spread(int[] me, int[][] arr, int N, ArrayList<int[]> list, int checkEmpty){

        // 상하좌우
        int[] dx = new int[] {1, -1, 0, 0};
        int[] dy = new int[] {0, 0, -1, 1};
        int x = me[0];
        int y = me[1];

        // 상하좌우 확인
        for(int i=0; i<4; i++){
            // 빈공간 -> 바이러스 채움
            if(x+dx[i] < 0 || x+dx[i] >= N || y+dy[i] < 0 || y+dy[i] >= N ){}
            else{
                if(arr[x+dx[i]][y+dy[i]] == 0){
                    arr[x+dx[i]][y+dy[i]] = 3;
                    list.add(new int[]{x+dx[i], y+dy[i]});
                    checkEmpty--;
                }
                // 비활성 바이러스 -> 활성화
                else if(arr[x+dx[i]][y+dy[i]] == 2){
                    arr[x+dx[i]][y+dy[i]] = 3;
                    list.add(new int[]{x+dx[i], y+dy[i]});
                }
            }
            
        }
        return checkEmpty;
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



    // 이건 지피티 설명 듣고 만들었음... 조합 이거 어케함!! 흥..
    public static void combination(ArrayList<int[]> virus, int M, int start,
                                    ArrayList<int[]> picked,
                                    ArrayList<ArrayList<int[]>> combList){

        if(picked.size() == M){
            ArrayList<int[]> temp = new ArrayList<>();
            for(int[] p : picked){
                temp.add(new int[]{p[0], p[1]});
            }
            combList.add(temp);
            return;
        }

        for(int i=start; i<virus.size(); i++){
            picked.add(virus.get(i));
            combination(virus, M, i+1, picked, combList);
            picked.remove(picked.size()-1);
        }
    }
}