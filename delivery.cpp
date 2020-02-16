#include <iostream>
#include <queue>
#define companyCnt 6
using namespace std;

class BoxContainer 
{
private:
    //Length는 cm, weight는 kg 단위
    int* length;
    int cnt, max;
    double* weight;
    bool visit, fast;
    enum Location
    {
        Metropolitan = 1,
        Gangwon = 2,
        Chungnam = 3,
        Chungbuk = 4,
        Jeonnam = 5,
        Jeonbuk = 6,
        Gyeongnam = 7,
        Gyeongbuk = 8,
        Jeju = 9
    };
    Location departure, destination;
public:
    BoxContainer(int max)
    {
        this->weight = new double[max];
        this->length = new int[max];
        this->max = max;
    }

    void setWeightLength(double weight, int length)
    {
        this->weight[cnt] = weight;
        this->length[cnt] = length;
    }

    void setLocation(int departure, int destination)
    {
        this->departure = (Location)departure;
        this->destination = (Location)destination;
    }
    
    void setVisit(int value)
    {
        this->visit = (bool) value; 
    }
    
    void setFast(int value)
    {
        this->fast = (bool) value; 
    }

    void setCnt(int cnt)
    {
        this->cnt = cnt;
    }

    int getLength(void)
    {
        return this->length[cnt];
    }

    int getWeight(void)
    {
        return this->weight[cnt];
    }

    Location getDeparture(void)
    {
        return this->departure;
    }
    
    Location getDestination(void)
    {
        return this->destination;
    }

    int getCnt(void)
    {
        return this->cnt;
    }

    int getMax(void)
    {
        return this->max;
    }

    bool isSameRegional(void)
    {
        if(this->departure == this->destination)
            return true;
        else
            return false;      
    }

    bool isSameSouthNorthRegional(void)
    {
        if((this->departure == Chungnam && this->destination == Chungbuk) || (this->departure == Chungbuk && this->destination == Chungnam)
            || (this->departure == Jeonnam && this->destination == Jeonbuk) || (this->departure == Jeonbuk && this->destination == Jeonnam)
            || (this->departure == Gyeongnam && this->destination == Gyeongbuk) || (this->departure == Gyeongbuk && this->destination == Gyeongnam))
            return true;
        else
            return false;
    }

    bool isJejuWithAnotherArea(void)
    {
        if(this->departure == Jeju && this->destination == Jeju)
            return false;
        else if(this->departure == Jeju || this->destination == Jeju)
            return true;
        else
            return false;       
    }
    
    bool isVisit(void)
    {
        if(visit)
            return true;
        else
            return false;
    }

    bool isFast(void)
    {
        if(fast)
            return true;
        else
            return false;
    }
};

void best(BoxContainer);
int CJ(BoxContainer box);
int Losen(BoxContainer box);
int Lotte(BoxContainer box);
int Hanjin(BoxContainer box);
int Post(BoxContainer box);
int CUPost(BoxContainer box);


int main(void)
{

    //초기화 : 택배 개수 설정
    int max;
    cout << "택배 개수를 입력하세요 : ";
    cin >> max;
    BoxContainer box(max);

    //출발지, 도착지 설정
    int departure, destination;
    cout << "1.수도권 2.강원 3.충남 4.충북 5.전남 6.전북 7.경남 8.경북 9.제주" << endl;
    cout << "택배 발송지역과 도착지역을 선택하세요(예 : 1 3) : " << endl;
    cin >> departure >> destination;
    box.setLocation(departure, destination);

    //택배 정보 입력
    for(int cnt = 1; cnt <= max; cnt++){
        double weight;
        int length;
        box.setCnt(cnt);
        cout << "(" << cnt << "개 째 입력중) 택배의 무게와 길이(세변의 합)를 입력하세요 : ";
        box.setWeightLength(weight, length);
    }

    while(true){
        int visit, fast;
        cout << "방문접수(고객이 택배점으로 찾아가는 경우)를 원하시는 경우 1, 아니면 0을 입력하세요 : ";
        cin >> visit; box.setVisit(visit);
        cout << "최대한 당일배송을 원하시는 경우 1, 아니면 0을 입력하세요 : ";
        cin >> fast; box.setFast(fast);

        best(box);

        cout << "최적 검색 완료. 종료하려면 엔터키를 누르세요.";
        // if(cin == '\r')
            // break;
    }
    return 0;
}

void best(BoxContainer box)
{
    for(int cnt = 1; cnt <= box.getMax(); cnt++){
        box.setCnt(cnt);
        priority_queue<int, vector<int>, greater<int> > pq;

        // pq.push(CJ(box), "CJ대한통운");
        // pq.push(Losen(box), "로젠택배");
        // pq.push(Lotte(box), "롯데택배");
        // pq.push(Hanjin(box), "한진택배");
        // pq.push(Post(box), "우체국택배");
        // pq.push(CUPost(box), "CU편의점택배");
        pq.push(CJ(box));
        pq.push(Losen(box));
        pq.push(Lotte(box));
        pq.push(Hanjin(box));
        pq.push(Post(box));
        pq.push(CUPost(box));

        printf("%d번째 택배 : %원, %s", cnt, pq.top(), pq.top());

        //test code
        while (!pq.empty()) {
            printf("%d",pq.top());
            pq.pop();
        }      
    }
}

int CJ(BoxContainer box)
{
    int cost = 0;
    if(!box.isSameRegional() && !box.isSameSouthNorthRegional()){   //보내는 곳과 받는 곳이 같은 권역이 아닐 때
        if(box.isJejuWithAnotherArea())                             // 재주지역 요금 추가. 단, 제주 <-> 제주는 제외
            cost = 3000;
        else
            cost = 1000;
    }
    if(box.getLength() <= 80 && box.getWeight() <= 2){
        cost += 5000;
        return cost;
    }
    else if(box.getLength() <= 100 && box.getWeight() <= 5){
        cost += 7000;
        return cost;
    }
    else if(box.getLength() <= 120 && box.getWeight() <= 15){
        cost += 8000;
        return cost;
    }
    else if(box.getLength() <= 160 && box.getWeight() <= 25){
        cost += 9000;
        return cost;
    }
}

int Losen(BoxContainer box)
{
    int cost = 0;
    if(!box.isSameRegional() && !box.isSameSouthNorthRegional()){  
        if(box.isJejuWithAnotherArea())                            
            cost = 3000;        // 중량에 따라 차등적용이나 데이터가 없어 3000원이 추가된다고 가정
        else
            cost = 1000;
    }
    if(box.getLength() <= 100 && box.getWeight() <= 5){
        cost += 6000;
        return cost;
    }
    else if(box.getLength() <= 120 && box.getWeight() <= 10){
        cost += 7000;
        return cost;
    }  
    else if(box.getLength() <= 140 && box.getWeight() <= 20){
        cost += 8000;
        return cost;
    }
    else if(box.getLength() <= 160 && box.getWeight() <= 30){
        cost += 10000;
        return cost;
    }
}

int Lotte(BoxContainer box)
{
    int cost = 0;
    if(!box.isSameRegional() && !box.isSameSouthNorthRegional()){  
        if(box.isJejuWithAnotherArea())                         
            cost = 4000;      
        else
            cost = 1000;
    }
    if(box.getLength() <= 80 && box.getWeight() <= 3){
        cost += 4000;
        return cost;
    }
    else if(box.getLength() <= 120 && box.getWeight() <= 10){
        cost += 5000;
        return cost;
    }  
    else if(box.getLength() <= 160 && box.getWeight() <= 25){
        cost += 6000;
        return cost;
    }
}

int Hanjin(BoxContainer box)
{
    int cost = 0;
    if(!box.isSameRegional() && !box.isSameSouthNorthRegional()){   
        if(box.isJejuWithAnotherArea())                           
            cost = 3000;        
        else
            cost = 1000;
    }
    if(box.getLength() <= 120 && box.getWeight() <= 10){
        cost += 4000;
        return cost;
    }  
    else if(box.getLength() <= 140 && box.getWeight() <= 20){
        cost += 5000;
        return cost;
    }
    else if(box.getLength() <= 160 && box.getWeight() <= 25){
        cost += 6000;
        return cost;
    } 
}

int Post(BoxContainer box)
{
    int cost = 0;
    if(!box.isVisit()){    //isVisit는 '고객'이 직접 '택배점'으로 방문한다는 의미
        if(box.isFast()){
            if(box.isJejuWithAnotherArea()){   // 방문 접수 - 제주로 빨리 보내려는 경우만           
                if(box.getLength() <= 60 && box.getWeight() <= 2)
                    cost = 1500;      
                else
                    cost = 2500;
            }
        }

        if(box.getLength() <= 60 && box.getWeight() <= 2){
            cost += 5000;
            return cost;
        }  
        else if(box.getLength() <= 80 && box.getWeight() <= 5){
            cost += 6000;
            return cost;
        }  
        else if(box.getLength() <= 100 && box.getWeight() <= 10){
            cost += 8000;
            return cost;
        }
        else if(box.getLength() <= 120 && box.getWeight() <= 20){
            cost += 11000;
            return cost;
        } 
        else if(box.getLength() <= 160 && box.getWeight() <= 30){
            cost += 14000;
            return cost;
        } 
    }
    else{
        if(box.isJejuWithAnotherArea()){        
            if(box.getLength() <= 50 && box.getWeight() <= 1)
                cost = 1500;      
            else
                cost = 2500;
        }

        if(box.isFast()){
            
            if(box.getLength() <= 50 && box.getWeight() <= 1){
                cost += 5000;
                return cost;
            }  
            else if(box.getLength() <= 80 && box.getWeight() <= 3){
                cost += 6000;
                return cost;
            }  
            else if(box.getLength() <= 100){
                if(box.getWeight() <= 5){
                    cost += 4500;
                    return cost;
               }
                else if(box.getWeight() <= 7){
                    cost += 5000;
                    return cost;
                }
            } 
            else if(box.getLength() <= 120){
                if(box.getWeight() <= 10){
                    cost += 6000;
                    return cost;
                }
                if(box.getWeight() <= 15){
                    cost += 7000;
                    return cost;
                }
                if(box.getWeight() <= 20){
                    cost += 8000;
                    return cost;
                }
                if(box.getWeight() <= 25){
                    cost += 9000;
                    return cost;
                }
            } 
            else if(box.getLength() <= 160 && box.getWeight() <= 30){
                cost += 11000;
                return cost;
            }
        }
        else{
            if(box.getLength() <= 50 && box.getWeight() <= 1){
                cost += 2200;
                return cost;
            }  
            else if(box.getLength() <= 80 && box.getWeight() <= 3){
                cost += 2700;
                return cost;
            }  
            else if(box.getLength() <= 100){
                if(box.getWeight() <= 5){
                    cost += 3200;
                    return cost;
               }
                else if(box.getWeight() <= 7){
                    cost += 3700;
                    return cost;
                }
            } 
            else if(box.getLength() <= 120){
                if(box.getWeight() <= 10){
                    cost += 4700;
                    return cost;
                }
                if(box.getWeight() <= 15){
                    cost += 5700;
                    return cost;
                }
                if(box.getWeight() <= 20){
                    cost += 6700;
                    return cost;
                }
                if(box.getWeight() <= 25){
                    cost += 7700;
                    return cost;
                }
            } 
            else if(box.getLength() <= 160 && box.getWeight() <= 30){
                cost += 9700;
                return cost;
            }
        }
    }
}

int CUPost(BoxContainer box)
{
    int cost = 0;
    if(!box.isVisit()){
        if(box.isJejuWithAnotherArea()) cost = 4000;   
        else cost = 2500;
        
        if(box.getLength() <= 80){
            if(box.getWeight() <= 2){
                cost += 4000;
                return cost;
            }
            else if(box.getWeight() <= 5){
                cost += 5000;
                return cost;
            }
        }
        else if(box.getLength() <= 100 && box.getWeight() <= 10){
            cost += 6000;
            return cost;
        } 
        else if(box.getLength() <= 120 && box.getWeight() <= 20){
            cost += 7500;
            return cost;
        } 
    
    }
    // else{
    //     if(box.getLength() <= 160){
    //         if(box.getWeight() <= 0.35){
    //             cost += 
    //             return cost;
    //         }
       
    //     } 
       
    // }
}


//  if(box.getLength() <= 60){
            
//             return;
//         }
//         else if(box.getLength() <= 80){
            
//             return;
//         }
//         else if(box.getLength() <= 100){

//             return;
//         }
//         else if(box.getLength() <= 120){

//             return;
//         }
//         else if(box.getLength() <= 140){

//             return;
//         }
//         else if(box.getLength() <= 160){

//             return;
//         }