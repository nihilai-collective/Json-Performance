
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 716.704 | 0.102013 | 955.081ms | 1811 | 80 | 483.461 | 2409.79 | 0.108295 | 7.31668 | 37.9094 | 6.13087 | 0.00106295 | 4.14136e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 371.65 | 0.046752 | 1184.42ms | 1811 | 2560 | 12083.9 | 4647.12 | 0.05736 | 13.8262 | 70.2253 | 9.04362 | 0.000599634 | 0.000236187 | 5.43553e-05 | 2(Loss) | true |
