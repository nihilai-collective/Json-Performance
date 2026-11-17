
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1527.46 | 0.116835 | 115.86ms | 1811 | 30 | 52.3552 | 1130.7 | 0.293936 | 1.58531 | 1(Win) | true |
| Glaze | 696.56 | 0.0378226 | 268.576ms | 1811 | 40 | 35.1788 | 2479.47 | 0.138999 | 3.52013 | 2(Loss) | true |
| Jsonifier (two-stage) | 451.798 | 0.0788671 | 388.642ms | 1811 | 30 | 272.685 | 3822.73 | 0.235989 | 5.44116 | 3(Loss) | true |
| simdjson (ondemand) | 218.953 | 0.0589028 | 800.318ms | 1811 | 40 | 863.512 | 7888.02 | 0.0136264 | 11.2664 | 4(Loss) | true |
