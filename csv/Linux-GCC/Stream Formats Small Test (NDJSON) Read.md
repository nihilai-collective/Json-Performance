
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3969.01 | 0.0731849 | 5830.65ms | 16002592 | 80 | 6.33503e+08 | 3.8451e+06 | 0.34951 | 0.623779 | 1(Win) | true |
| simdjson (ondemand) | 3514.62 | 0.31529 | 6520.67ms | 16002592 | 30 | 5.62299e+09 | 4.34223e+06 | 1.0624 | 0.704427 | 2(Loss) | true |
