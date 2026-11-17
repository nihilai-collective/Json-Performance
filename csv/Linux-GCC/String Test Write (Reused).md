
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11279.9 | 0.233176 | 825.92ms | 9578 | 80 | 285.233 | 809.788 | 0.0447849 | 0.481082 | 2.23585 | 0.274589 | 0.000779129 | 2.21863e-05 | 9.13552e-06 | 1(Win) | true |
| simdjson (reflection) | 9222.92 | 0.201038 | 845.357ms | 9578 | 320 | 1268.58 | 990.391 | 0.0552486 | 0.572606 | 3.07329 | 0.321257 | 0.000110279 | 1.01143e-05 | 0 | 2(Loss) | true |
| Glaze | 5909.47 | 0.0649322 | 895.127ms | 9578 | 2560 | 2578.78 | 1545.71 | 0.0488767 | 0.890906 | 4.44805 | 0.7202 | 0.000151062 | 2.02286e-05 | 7.17791e-06 | 3(Loss) | true |
