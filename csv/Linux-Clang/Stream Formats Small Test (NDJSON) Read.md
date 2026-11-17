
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3380.03 | 0.125655 | 6867.53ms | 16002592 | 40 | 1.28754e+09 | 4.51513e+06 | 0.422598 | 0.73243 | 1(Win) | true |
| Jsonifier (generic) | 3313.54 | 0.167602 | 6945.45ms | 16002592 | 80 | 4.76702e+09 | 4.60573e+06 | 0.76512 | 0.747122 | 2(Loss) | true |
