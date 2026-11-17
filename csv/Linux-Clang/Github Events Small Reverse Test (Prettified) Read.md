
----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1061.39 | 0.0291324 | 912.066ms | 2158 | 4890 | 1560.33 | 1939 | 0.0346491 | 4.95625 | 17.3916 | 3.51946 | 0.00252951 | 0.000111252 | 2.90923e-05 | 1(Win) | true |
| simdjson (ondemand) | 870.487 | 0.0483863 | 959.745ms | 2158 | 2560 | 3350.15 | 2364.23 | 0.0667551 | 6.01698 | 23.7845 | 4.22799 | 0.0017875 | 7.45772e-05 | 1.53861e-05 | 2(Loss) | true |
