
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3501.81 | 0.055 | 67.9614ms | 2158 | 640 | 66.8688 | 587.705 | 0.100661 | 0.675275 | 1(Win) | true |
| Glaze | 2543.39 | 0.0839546 | 91.6044ms | 2158 | 160 | 73.8393 | 809.169 | 0.0363159 | 0.94205 | 2(Loss) | true |
| Jsonifier | 2228.06 | 0.117283 | 101.946ms | 2158 | 80 | 93.8884 | 923.688 | 0.00676682 | 1.08035 | 3(Loss) | true |
| simdjson (ondemand) | 2078.78 | 0.0939502 | 109.499ms | 2158 | 160 | 138.421 | 990.019 | 0.010731 | 1.15801 | 4(Loss) | true |
