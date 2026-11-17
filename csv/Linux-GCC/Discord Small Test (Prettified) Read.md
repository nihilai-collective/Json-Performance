
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1959.18 | 0.185298 | 1049.73ms | 6701 | 320 | 11690.1 | 3261.85 | 0.0286537 | 2.69239 | 10.6927 | 1.98732 | 0.000936427 | 2.70482e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1901.29 | 0.033903 | 1056.97ms | 6701 | 4890 | 6349.9 | 3361.17 | 0.137248 | 2.73974 | 10.8105 | 1.86845 | 0.000593447 | 3.00599e-05 | 6.53078e-06 | 2(Loss) | true |
