
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2072.68 | 0.0594188 | 1567.58ms | 18245 | 320 | 7962 | 8394.84 | 0.0986983 | 2.49663 | 10.0902 | 1.99477 | 0.00287836 | 1.04481e-05 | 1.7128e-07 | 1(Win) | true |
| simdjson (ondemand) | 1980.11 | 0.0707244 | 1611.91ms | 18245 | 80 | 3089.85 | 8787.29 | 0.0513262 | 2.61402 | 10.7303 | 1.82165 | 0.00310907 | 6.16607e-06 | 0 | 2(Loss) | true |
