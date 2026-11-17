
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5934.45 | 0.0699161 | 5006.88ms | 9930848 | 30 | 3.73497e+07 | 1.5959e+06 | 0.0446174 | 0.417186 | 1(Win) | true |
| Glaze | 3784.89 | 0.105471 | 7887.51ms | 9930228 | 40 | 2.78574e+08 | 2.50211e+06 | 0.103587 | 0.654119 | 2(Loss) | true |
| simdjson (reflection) | 286.803 | 2.74907 | 10100.6ms | 10018896 | 30 | 2.51632e+13 | 3.33147e+07 | 1.05878 | 8.63248 | 3(Loss) | true |
