
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3788.95 | 0.107142 | 218.791ms | 7932 | 40 | 183.025 | 1996.47 | 0.0746592 | 0.644658 | 1(Win) | true |
| Glaze | 2119.25 | 0.111038 | 378.299ms | 7932 | 40 | 628.356 | 3569.45 | 0.519774 | 1.15928 | 2(Loss) | true |
| Jsonifier | 2074.97 | 0.0678855 | 376.906ms | 7932 | 80 | 489.987 | 3645.61 | 0.0298215 | 1.18431 | 3(Loss) | true |
| simdjson (ondemand) | 1062.78 | 0.0487161 | 725.611ms | 7932 | 40 | 480.933 | 7117.7 | 0.25871 | 2.31966 | 4(Loss) | true |
