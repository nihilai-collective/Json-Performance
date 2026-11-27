
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4678.06 | 0.522819 | 6630.86ms | 10548466 | 80 | 1.01121e+10 | 2.15042e+06 | 0.173301 | 1.08954 | 3.87583 | 0.65398 | 0.0107521 | 0.0174676 | 0.00027915 | 1(Win) | true |
| simdjson (ondemand) | 4036.19 | 0.190632 | 7806.35ms | 10548466 | 40 | 9.02998e+08 | 2.4924e+06 | 0.157699 | 1.26253 | 4.46385 | 0.711749 | 0.00862894 | 0.017463 | 0.000261382 | 2(Loss) | true |
