
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5936.51 | 0.120572 | 65.052ms | 3808 | 4890 | 2660.3 | 611.738 | 0.251599 | 0.496631 | 1(Win) | true |
| Jsonifier (two-stage) | 5897.28 | 0.132714 | 65.2636ms | 3808 | 4890 | 3266.12 | 615.808 | 0.284217 | 0.49982 | 2(Loss) | true |
| simdjson (ondemand) | 5087.49 | 0.188098 | 75.695ms | 3808 | 2560 | 4615.27 | 713.828 | 0.065624 | 0.58308 | 3(Loss) | true |
| Glaze | 3425.02 | 0.247163 | 109.555ms | 3808 | 1280 | 8791.15 | 1060.31 | 0.236337 | 0.862773 | 4(Loss) | true |
