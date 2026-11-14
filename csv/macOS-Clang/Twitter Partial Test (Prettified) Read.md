
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5414.4 | 0.135505 | 5856ms | 631514 | 640 | 1.45398e+07 | 111233 | 0.154819 | 1(Win) | true |
| Jsonifier (two-stage) | 5380.12 | 0.275715 | 5759.19ms | 631514 | 320 | 3.04827e+07 | 111942 | 0.240117 | 2(Loss) | true |
| simdjson (ondemand) | 4832.61 | 0.0677313 | 6386.61ms | 631514 | 2560 | 1.82398e+07 | 124624 | 0.106821 | 3(Loss) | true |
| Glaze | 2766.89 | 0.257428 | 5642.09ms | 631514 | 30 | 9.41926e+06 | 217667 | 0.377604 | 4(Loss) | true |
