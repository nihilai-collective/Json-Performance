
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3451.62 | 0.0916081 | 67.3475ms | 2158 | 160 | 47.7358 | 596.25 | 0.154896 | 0.685119 | 1(Win) | true |
| Glaze | 2460.97 | 0.225573 | 92.8754ms | 2158 | 30 | 106.754 | 836.267 | 0.554939 | 0.97507 | 2(Loss) | true |
| Jsonifier | 2252.47 | 0.0524423 | 101.537ms | 2158 | 320 | 73.4677 | 913.675 | 0.00478858 | 1.06911 | 3(Loss) | true |
| simdjson (ondemand) | 2194.24 | 0.113471 | 103.766ms | 2158 | 160 | 181.227 | 937.925 | 0.184907 | 1.09566 | 4(Loss) | true |
