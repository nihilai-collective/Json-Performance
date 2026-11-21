
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2902.27 | 0.0446233 | 310.985ms | 8051 | 160 | 222.981 | 2645.53 | 0.0207941 | 0.844421 | 1(Win) | true |
| Jsonifier | 2284.82 | 0.0605773 | 385.888ms | 8051 | 80 | 331.516 | 3360.45 | 0.281257 | 1.07457 | 2(Loss) | true |
| Glaze | 2013.53 | 0.060867 | 428.982ms | 8051 | 80 | 430.961 | 3813.22 | 0.145101 | 1.22131 | 3(Loss) | true |
| simdjson (ondemand) | 1578.29 | 0.068043 | 532.563ms | 8051 | 40 | 438.281 | 4864.77 | 0.045716 | 1.55963 | 4(Loss) | true |
