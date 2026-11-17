
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2928.23 | 0.115949 | 8618.32ms | 7351818 | 30 | 2.31224e+08 | 2.39436e+06 | 1.66149 | 0.845442 | 1(Win) | true |
| Jsonifier | 2618.96 | 0.142555 | 9266.92ms | 7351818 | 30 | 4.36938e+08 | 2.67711e+06 | 1.03693 | 0.945325 | 2(Loss) | true |
| simdjson (ondemand) | 2351.06 | 0.220462 | 10283.1ms | 7351818 | 30 | 1.29673e+09 | 2.98216e+06 | 1.76078 | 1.053 | 3(Loss) | true |
| Glaze | 2161.32 | 0.288711 | 5394.28ms | 7351818 | 30 | 2.63147e+09 | 3.24396e+06 | 1.33912 | 1.14548 | 4(Loss) | true |
