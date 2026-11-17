
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7626.89 | 0.064249 | 52.0359ms | 3808 | 1280 | 119.796 | 476.156 | 0.129787 | 0.306567 | 1(Win) | true |
| Jsonifier (two-stage) | 7178.74 | 0.106084 | 54.2067ms | 3808 | 160 | 46.0801 | 505.881 | 0.0506285 | 0.326106 | 2(Loss) | true |
| Jsonifier | 7124.17 | 0.0901418 | 53.2525ms | 3808 | 160 | 33.783 | 509.756 | 0.0771832 | 0.328921 | 3(Loss) | true |
| simdjson (reflection) | 7036.11 | 0.0699068 | 54.7226ms | 3808 | 640 | 83.3195 | 516.136 | 0.0778623 | 0.333641 | 4(Loss) | true |
| Glaze | 3894.74 | 0.0242268 | 98.6777ms | 3808 | 640 | 32.6594 | 932.436 | 0.031996 | 0.618587 | 5(Loss) | true |
