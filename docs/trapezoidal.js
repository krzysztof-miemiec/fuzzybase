// this code is live, edit me!
const mul = 20;

const trap = (l, m, n, o) => graph.add((x) => {
    if(x<l || x>o) return NaN;
    if(x<m){
        return mul*(x-l)/(m-l);
    }
    if(x<n){
        return 1*mul;
    }
    if(x<o){
        return mul*(x-o)/(n-o);
    }
});
const age = () => {
	const child = trap(0, 0, 12, 15);
	const young = trap(10, 12, 16, 19);
	const youngAdult = trap(17, 19, 35, 40);
	const adult = trap(35, 40, 60, 65);
	const old = trap(60, 65, 200, 200);
};


const chol = () => {
	const desirable = trap(0, 0, 200, 210);
	const borderlineHigh = trap(190, 200, 240, 250);
	const high = trap(230, 240, 1000, 1000);
};

const heart_rate = () => {
	const none = trap(0, 0, 0, 0);
	const veryLow = trap(1, 1, 35, 40);
	const low = trap(35, 40, 60, 70);
	const normal = trap(50, 60, 10, 130);
	const high = trap(120, 130, 160, 190);
	const veryHigh = trap(160, 180, 300, 300);
	const extremelyHigh = trap(250, 300, 600, 900);
	const impossible = trap(300, 400, 1200, 1200);
};

const blood_pressure = () => {
	const hypotension = trap(0, 0, 80, 85);
	const normal = trap(75, 80, 120, 130);
	const prehypertension = trap(120, 125, 140, 150);
	const hypertension1 = trap(130, 140, 160, 170);
	const hypertension2 = trap(150, 160, 180, 200);
	const highCrisisEmergency = trap(170, 180, 300, 300);
};

// age();
chold();
// blood_pressure();
//heart_rate();