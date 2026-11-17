
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4146.24 | 0.037549 | 2949.16ms | 83958 | 4890 | 257111 | 19311.1 | 0.0708103 | 1.2342 | 5.97592 | 0.934658 | 0.00198426 | 3.93857e-06 | 9.03656e-07 | 1(Win) | true |
| simdjson (ondemand) | 3738.17 | 0.0271086 | 3154ms | 83958 | 1280 | 43154.8 | 21419.2 | 0.0266844 | 1.37975 | 6.26096 | 0.938338 | 0.00186136 | 4.13153e-06 | 9.58441e-07 | 2(Loss) | true |
