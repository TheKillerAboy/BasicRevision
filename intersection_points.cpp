enum Event{
	BEGIN,END,VERTICAL;
}


vector<tuple<ll,ll,ll>> lines;

set<tuple<ll,Event,ll>> events; // b,e,h

int main(){
	ll N;
	cin>>N;
	ll t,b,e,h;
	for(ll i = 0; i < N; i++){
		cin>>t>>b>>e>>h;
		if(t == 0){ // Hor
			events.insert({b,BEGIN,i});
			events.insert({e,END,i});
			lines[i] = {b,e,h};
		}
		else{
			events.insert({h,VERTICAL,i});
			lines[i] = {b,e,h};
		}
	}
	set<ll> active_heights;
	for(auto event : events){
		if(get<1>(event) == BEGIN){
			active_heights.insert(get<0>(event));
		}
		else if(get<1>(event) == END){
			active_heights.erase(active_heights.find(get<0>(event)));
		}
		else if(get<1>(event) == VERTICAL){
			
		}
	}
}