
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5205.44 | 0.0659496 | 7779.07ms | 6661989 | 320 | 2.07332e+08 | 1.22052e+06 | 0.0469089 | 0.985354 | 2.95785 | 0.261242 | 7.62906e-05 | 0.0278388 | 0.000147463 | 1(Win) | true |
| Glaze | 3286.39 | 0.131513 | 6030.39ms | 6661897 | 160 | 1.03422e+09 | 1.93321e+06 | 0.577877 | 1.55011 | 4.23033 | 0.46932 | 7.64375e-05 | 0.0630756 | 0.00338083 | 2(Loss) | true |
