
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4008.73 | 0.174938 | 8122.64ms | 1151920 | 40 | 9.19298e+06 | 274041 | 0.0748142 | 1.25993 | 6.09497 | 0.925311 | 0.0047726 | 0.0470471 | 6.13975e-05 | 1(Win) | true |
| Jsonifier | 3251.23 | 0.0999643 | 9694.61ms | 1151920 | 80 | 9.12705e+06 | 337890 | 0.225109 | 1.55704 | 6.98687 | 1.53083 | 0.00362685 | 0.0127777 | 4.62706e-05 | 2(Loss) | true |
| Glaze | 2880.65 | 0.049541 | 5433.41ms | 1151920 | 640 | 2.2844e+07 | 381357 | 0.0226332 | 1.75263 | 8.12575 | 1.5582 | 0.00543803 | 0.00923357 | 3.25923e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2713.65 | 0.157246 | 5645.82ms | 1151920 | 160 | 6.48366e+07 | 404827 | 0.100435 | 1.84251 | 8.40381 | 1.15461 | 0.00423407 | 0.0375394 | 6.53691e-05 | 4(Loss) | true |
