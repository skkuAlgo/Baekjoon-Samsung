import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        int R = sc.nextInt();
        int C = sc.nextInt();
        int time = sc.nextInt();
        int[][] arr = new int[R][C];
        int[][] spread_arr = new int[R][C];

        int airRow = 0;
        
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                arr[i][j] = sc.nextInt();
            }
        }
        // printArr(arr, R, C);

        // time만큼 반복
        for(int a=0; a<time; a++){
            for(int i=0; i<R; i++){
                for(int j=0; j<C; j++){
                    int dust = arr[i][j];
                    if(dust > 0){ //먼지
                        spread(i,j,dust,spread_arr,R,C,arr);
                    }
                    else if(dust == -1){ //공기청정기(아래칸 위치 저장)
                        spread_arr[i][j] = -1;
                        airRow = i;
                    }
                }
            }

            // 공기청정기 작동
            air(airRow-1, spread_arr, 0, R, C);
            air(airRow, spread_arr, 1, R, C);

            save(arr, spread_arr, R, C);
        }

        // printArr(spread_arr, R, C);
        add(arr,R,C);
    }

    // 확산함수 
    public static void spread(int row, int col, int dust, int[][] spread_arr,int R, int C, int[][] arr){
        int spreadDust = (int)(dust/5);
        int count = 0;

        // 상
        if(row-1>=0 && arr[row-1][col] != -1) {
            spread_arr[row-1][col] += spreadDust;
            count++;
        }
        // 하
        if(row+1<R && arr[row+1][col] != -1) {
            spread_arr[row+1][col] += spreadDust;
            count++;
        }
        // 좌
        if(col-1>=0 && arr[row][col-1] != -1) {
            spread_arr[row][col-1] += spreadDust;
            count++;
        }
        // 우
        if(col+1<C && arr[row][col+1] != -1) {
            spread_arr[row][col+1] += spreadDust;
            count++;
        }
        // 기존
        int originDust = dust - count*spreadDust;
        spread_arr[row][col] += originDust;
    }


    // 공기청정기 작동 함수
    public static void air(int airRow, int[][] spread_arr, int upDown, int R, int C){
        // upDown = 0 (위에 있는 공청기)
        if(upDown == 0){
            // 일렬로 저장 (반시계방향으로)
            int len = C-1 + airRow+1 + C + airRow - 3;
            int count = 1;
            int[] arr = new int[len+1];
            // 오른쪽으로 쭉 이동
            for(int i=1; i<C; i++){
                arr[count] = spread_arr[airRow][i];
                count++;
            }
            if(airRow == 0){//맨 위에 있는 경우
                arr[count] = -1;
            }else{
                // 위로 이동
                for(int i=airRow-1; i>=0; i--){
                    arr[count] = spread_arr[i][C-1];
                    count++;
                }
                // 왼쪽으로
                for(int i=C-2; i>0; i--){
                    arr[count] = spread_arr[0][i];
                    count++;
                }
                //아래로
                if(airRow == 1) arr[count] = -1; //1이면 끝!
                else{
                    for(int i=0; i<airRow; i++){
                        arr[count] = spread_arr[i][0];
                        count++;
                    }
                }
            }

            //이동
            count=0;
            for(int i=1; i<C; i++){
                spread_arr[airRow][i] = arr[count];
                count++;
            }
            if(airRow == 0){}
            else{
                // 위로 이동
                for(int i=airRow-1; i>=0; i--){
                    spread_arr[i][C-1] = arr[count];
                    count++;
                }
                // 왼쪽으로
                for(int i=C-2; i>0; i--){
                    spread_arr[0][i] = arr[count];
                    count++;
                }
                //아래로
                if(airRow == 1) arr[count] = -1; //1이면 끝!
                else{
                    for(int i=0; i<airRow; i++){
                        spread_arr[i][0] = arr[count];
                        count++;
                    }
                }
            }

        }
        // upDown = 1 (아래 있는 공청기)
        else{
            int len = C-1 + R-airRow + C + R-airRow-1 - 3;
            int count = 1;
            int[] arr = new int[len+1];
            // 오른쪽으로 쭉 이동
            for(int i=1; i<C; i++){
                arr[count] = spread_arr[airRow][i];
                count++;
            }
            if(airRow == R-1){//맨 아래에 있는 경우
                arr[count] = -1;
            }else{
                // 아래로 이동
                for(int i=airRow+1; i<R; i++){
                    arr[count] = spread_arr[i][C-1];
                    count++;
                }//=====================
                // 왼쪽으로
                for(int i=C-2; i>0; i--){
                    arr[count] = spread_arr[R-1][i];
                    count++;
                }
                //위로
                if(airRow == R-2) arr[count] = -1; //1이면 끝!
                else{
                    for(int i=R-1; i>airRow; i--){
                        arr[count] = spread_arr[i][0];
                        count++;
                    }
                }
            }

            // 이동
            count = 0;
            // 오른쪽으로 쭉 이동
            for(int i=1; i<C; i++){
                spread_arr[airRow][i] = arr[count];
                count++;
            }
            if(airRow == R-1){}
            else{
                // 아래로 이동
                for(int i=airRow+1; i<R; i++){
                    spread_arr[i][C-1] = arr[count];
                    count++;
                }//=====================
                // 왼쪽으로
                for(int i=C-2; i>0; i--){
                    spread_arr[R-1][i] = arr[count];
                    count++;
                }
                //위로
                if(airRow == R-2){} //1이면 끝!
                else{
                    for(int i=R-1; i>airRow; i--){
                        spread_arr[i][0] = arr[count];
                        count++;
                    }
                }
            }
        }
        
    }



    // 행렬 출력 함수 
    public static void printArr(int[][] arr, int R, int C){
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                System.out.print(arr[i][j]);
                System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println();
    }

    // 행렬 저장 
    public static void save(int[][] arr, int[][] spread_arr, int R, int C){
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                arr[i][j] = spread_arr[i][j];
                spread_arr[i][j] = 0;
            }
        }
    }


    // 행렬 합
    public static void add(int[][] arr, int R, int C){
        int result = 0;
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                if(arr[i][j] > 0){
                    result += arr[i][j];
                }
            }
        }
        System.out.println(result);
    }
}
