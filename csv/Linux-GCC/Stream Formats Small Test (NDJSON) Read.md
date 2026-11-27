
----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3908.94 | 0.120837 | 5930.42ms | 16002592 | 40 | 8.90272e+08 | 3.9042e+06 | 0.217682 | 0.633342 | 1(Win) | true |
| simdjson (ondemand) | 3631.43 | 0.073182 | 6411.16ms | 16002592 | 80 | 7.56698e+08 | 4.20254e+06 | 0.519912 | 0.681743 | 2(Loss) | true |
