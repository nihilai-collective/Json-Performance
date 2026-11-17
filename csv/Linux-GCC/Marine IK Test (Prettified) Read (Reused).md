
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2802.09 | 0.181359 | 8586.51ms | 7351818 | 80 | 1.64737e+09 | 2.50214e+06 | 0.0885435 | 0.883553 | 1(Win) | true |
| Jsonifier | 2771.22 | 0.0962166 | 8677.92ms | 7351818 | 40 | 2.37032e+08 | 2.53002e+06 | 0.00501438 | 0.89339 | 2(Loss) | true |
| simdjson (reflection) | 2399.57 | 0.0671262 | 9798.42ms | 7351818 | 30 | 1.15406e+08 | 2.92188e+06 | 0.383967 | 1.03177 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2148.15 | 0.0551744 | 5283.71ms | 7351818 | 30 | 9.7287e+07 | 3.26384e+06 | 0.00735792 | 1.15252 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2145.5 | 0.187248 | 5335.31ms | 7351818 | 80 | 2.99542e+09 | 3.26788e+06 | 0.314734 | 1.15396 | 4(Tie) | true |
