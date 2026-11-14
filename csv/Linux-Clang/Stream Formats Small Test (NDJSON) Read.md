
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4094.65 | 0.299521 | 5960.33ms | 16002592 | 40 | 4.98496e+09 | 3.72712e+06 | 2.48003 | 0.604634 | 1(Win) | true |
| simdjson (ondemand) | 3479.38 | 0.122169 | 6659.64ms | 16002592 | 80 | 2.29716e+09 | 4.3862e+06 | 0.320311 | 0.711552 | 2(Loss) | true |
