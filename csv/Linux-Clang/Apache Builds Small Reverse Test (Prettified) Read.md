
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.74 | 0.0410737 | 933.699ms | 3370 | 2560 | 2018.18 | 2161.7 | 0.0373734 | 3.5317 | 13.6786 | 2.65697 | 0.00495479 | 4.55536e-05 | 5.21606e-06 | 1(Win) | true |
| simdjson (ondemand) | 920.007 | 0.0404828 | 1070.58ms | 3370 | 1280 | 2559.94 | 3493.32 | 0.00699947 | 5.6617 | 24.1282 | 4.57567 | 0.0102886 | 3.26873e-05 | 9.273e-07 | 2(Loss) | true |
