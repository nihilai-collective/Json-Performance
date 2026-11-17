
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2610.14 | 0.366835 | 343.429ms | 8051 | 2560 | 298095 | 2941.62 | 0.0132943 | 0.939387 | 1(Win) | true |
| Jsonifier | 2050.98 | 0.291696 | 423.412ms | 8051 | 1280 | 152632 | 3743.58 | 0.176215 | 1.19674 | 2(Loss) | true |
| Glaze | 1883.19 | 0.140613 | 469.834ms | 8051 | 40 | 1314.69 | 4077.15 | 0.48693 | 1.30573 | 3(Loss) | true |
| simdjson (ondemand) | 1483.39 | 0.340627 | 563.066ms | 8051 | 640 | 198944 | 5176.02 | 0.043119 | 1.65946 | 4(Loss) | true |
