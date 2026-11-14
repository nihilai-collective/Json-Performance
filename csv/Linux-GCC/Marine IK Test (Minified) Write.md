
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1271.75 | 0.0598368 | 8731.26ms | 1834197 | 320 | 2.1676e+08 | 1.37545e+06 | 0.00662257 | 3.96565 | 13.1198 | 0.79908 | 0.00291226 | 0.0618482 | 2.16495e-05 | 1(Win) | true |
| Glaze | 960.003 | 0.271794 | 5674.79ms | 1833577 | 160 | 3.92151e+09 | 1.82149e+06 | 0.265382 | 5.23699 | 16.0435 | 1.05288 | 0.00100569 | 0.0765555 | 2.89291e-05 | 2(Loss) | true |
| simdjson (reflection) | 889.731 | 0.0104599 | 6418.6ms | 1922245 | 80 | 3.71577e+06 | 2.06039e+06 | 0.0350942 | 5.67481 | 18.1621 | 2.01852 | 0.0244581 | 0.0518748 | 5.32841e-05 | 3(Loss) | true |
