
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3124.66 | 0.0457451 | 634.274ms | 18245 | 80 | 519.113 | 5568.54 | 0.00336725 | 0.788478 | 1(Win) | true |
| Jsonifier | 2663.57 | 0.0811647 | 737.347ms | 18245 | 30 | 843.362 | 6532.5 | 0.118752 | 0.926031 | 2(Loss) | true |
| simdjson (ondemand) | 2046.53 | 0.121711 | 983.504ms | 18245 | 2560 | 274124 | 8502.09 | 0.0811504 | 1.20538 | 3(Loss) | true |
| Glaze | 1994.73 | 0.0694246 | 959.418ms | 18245 | 30 | 1100.19 | 8722.87 | 0.0160523 | 1.23765 | 4(Loss) | true |
