
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2982.78 | 0.257158 | 864.819ms | 3808 | 4890 | 47935.9 | 1217.52 | 0.331696 | 1.75052 | 6.17463 | 0.871586 | 0.000532675 | 5.00507e-05 | 1.81514e-05 | 1(Win) | true |
| Glaze | 2717.14 | 0.183251 | 878.781ms | 3808 | 4890 | 29334 | 1336.55 | 0.119876 | 1.92899 | 7.88524 | 1.36371 | 0.000467373 | 4.02768e-05 | 6.12208e-06 | 2(Loss) | true |
| Jsonifier | 1903.84 | 0.598811 | 938.577ms | 3808 | 1280 | 167002 | 1907.51 | 0.716098 | 2.68347 | 6.6415 | 1.23481 | 0.000536289 | 4.2263e-05 | 1.27199e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1351.96 | 0.142704 | 1046.27ms | 3808 | 2560 | 37616.6 | 2686.17 | 0.249611 | 3.78441 | 12.8301 | 2.11292 | 0.000511157 | 6.89338e-05 | 2.86198e-05 | 4(Loss) | true |
