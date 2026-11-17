
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3236.46 | 0.169547 | 628.604ms | 18245 | 2560 | 212699 | 5376.18 | 0.22854 | 0.760906 | 1(Win) | true |
| Jsonifier | 2560.11 | 0.0825623 | 787.49ms | 18245 | 40 | 1259.49 | 6796.5 | 0.319317 | 0.963147 | 2(Loss) | true |
| simdjson (ondemand) | 2021.45 | 0.355526 | 955.22ms | 18245 | 320 | 299679 | 8607.58 | 0.260102 | 1.22048 | 3(Loss) | true |
| Glaze | 1888.23 | 0.148558 | 1042.25ms | 18245 | 2560 | 479745 | 9214.88 | 0.241203 | 1.30726 | 4(Loss) | true |
