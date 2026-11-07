
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3071.56 | 0.0859506 | 600.742ms | 18245 | 80 | 1896.52 | 5664.8 | 0.267271 | 0.802211 | 1(Win) | true |
| Jsonifier | 2524.9 | 0.311372 | 703.596ms | 18245 | 640 | 294673 | 6891.29 | 0.186482 | 0.976718 | 2(Loss) | true |
| simdjson (ondemand) | 1853.08 | 0.103337 | 944.533ms | 18245 | 4890 | 460380 | 9389.64 | 0.529209 | 1.33202 | 3(Loss) | true |
| Glaze | 1828.61 | 0.0884003 | 971.02ms | 18245 | 30 | 2122.64 | 9515.33 | 0.150407 | 1.35014 | 4(Loss) | true |
