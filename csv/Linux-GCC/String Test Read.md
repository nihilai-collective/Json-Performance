
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3039.98 | 0.0733393 | 841.286ms | 4215 | 640 | 601.878 | 1322.29 | 0.105411 | 1.74975 | 8.60047 | 1.09181 | 0.00213115 | 2.81732e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 2815.08 | 0.0510176 | 852.438ms | 4215 | 320 | 169.826 | 1427.93 | 0.0284422 | 1.90872 | 9.88422 | 0.932622 | 0.00137233 | 3.03974e-05 | 0 | 2(Loss) | true |
