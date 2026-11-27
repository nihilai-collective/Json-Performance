
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11616.4 | 0.0646256 | 5233.42ms | 631514 | 2560 | 2.87389e+06 | 51845.4 | 0.167043 | 0.212983 | 1(Win) | true |
| Jsonifier | 11240.4 | 0.18948 | 5373.68ms | 631514 | 640 | 6.59648e+06 | 53580 | 0.0781307 | 0.220106 | 2(Loss) | true |
| simdjson (ondemand) | 9463.86 | 0.145114 | 6500.91ms | 631514 | 1280 | 1.09159e+07 | 63637.7 | 0.0184538 | 0.261439 | 3(Loss) | true |
| Glaze | 3963.11 | 0.0385111 | 7805.89ms | 631514 | 2560 | 8.76808e+06 | 151966 | 0.0543215 | 0.6246 | 4(Loss) | true |
