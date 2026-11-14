
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17075.6 | 0.0301399 | 1082.54ms | 65103 | 160 | 192.157 | 3636.02 | 0.0469043 | 0.305083 | 1.6557 | 0.0748967 | 3.09126e-05 | 3.64807e-06 | 7.68014e-07 | 1(Win) | true |
| simdjson (stage-1) | 16149.8 | 0.043239 | 1100.01ms | 65103 | 1280 | 3536.96 | 3844.45 | 0.117381 | 0.322123 | 1.50202 | 0.0630693 | 2.94725e-05 | 2.40004e-06 | 3.84007e-07 | 2(Loss) | true |
