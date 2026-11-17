
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3603.99 | 0.15305 | 6354.19ms | 16002592 | 80 | 3.36024e+09 | 4.23454e+06 | 0.0597614 | 1.40428 | 7.61292 | 1.20636 | 0.000871026 | 0.0327834 | 0.0054251 | 1(Win) | true |
| simdjson (ondemand) | 2922.45 | 0.0992361 | 7826.45ms | 16002592 | 30 | 8.05652e+08 | 5.22208e+06 | 0.0953326 | 1.72872 | 8.64356 | 1.26589 | 0.00287135 | 0.037025 | 0.00718846 | 2(Loss) | true |
