
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4118.58 | 0.0763263 | 2957.23ms | 83958 | 160 | 35228.8 | 19440.8 | 0.0499986 | 1.25242 | 5.98375 | 0.936337 | 0.00213247 | 1.92805e-05 | 1.48884e-05 | 1(Win) | true |
| simdjson (ondemand) | 3704.81 | 0.0356059 | 3161.84ms | 83958 | 1280 | 75796 | 21612.1 | 0.0918925 | 1.37935 | 6.24253 | 0.932209 | 0.00202071 | 4.22458e-06 | 1.56328e-06 | 2(Loss) | true |
