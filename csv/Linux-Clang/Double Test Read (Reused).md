
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 822.34 | 0.223007 | 212.248ms | 1811 | 4890 | 107270 | 2100.23 | 0.0165321 | 2.97378 | 1(Win) | true |
| simdjson (ondemand) | 471.201 | 0.0869333 | 377.684ms | 1811 | 40 | 406.122 | 3665.32 | 0.168299 | 5.21864 | 2(Loss) | true |
