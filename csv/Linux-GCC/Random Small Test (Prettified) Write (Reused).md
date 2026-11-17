
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30422.9 | 0.0837989 | 31.5931ms | 9255 | 320 | 18.9138 | 290.119 | 0.195657 | 0.073984 | 1(Win) | true |
| Glaze | 4919.33 | 0.0787506 | 183.914ms | 9255 | 40 | 79.8564 | 1794.2 | 0.026003 | 0.496524 | 2(Loss) | true |
| simdjson (reflection) | 588.451 | 0.0794945 | 1590.7ms | 9255 | 30 | 4265.09 | 14999.1 | 0.715119 | 4.19997 | 3(Loss) | true |
