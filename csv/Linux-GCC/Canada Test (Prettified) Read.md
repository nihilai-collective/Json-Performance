
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18285.6 | 0.121984 | 7385.69ms | 5373214 | 1280 | 1.49578e+08 | 280237 | 0.734762 | 0.274739 | 1.37324 | 0.0519539 | 0.000771326 | 0.0195662 | 3.28263e-06 | 1(Win) | true |
| simdjson (stage-1) | 14892.1 | 0.530615 | 8928.34ms | 5373214 | 30 | 1.00009e+08 | 344095 | 0.0562661 | 0.339288 | 1.59197 | 0.0578107 | 0.000981777 | 0.0196128 | 1.23452e-06 | 2(Loss) | true |
