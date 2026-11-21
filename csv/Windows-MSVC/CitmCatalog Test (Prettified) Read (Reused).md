
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2925.29 | 0.101573 | 5401.49ms | 1151920 | 640 | 9.31207e+07 | 375538 | 0.105793 | 0.846271 | 1(Win) | true |
| Jsonifier | 2421.54 | 0.225947 | 6320.17ms | 1151920 | 80 | 8.40553e+07 | 453660 | 0.139616 | 1.02234 | 2(Loss) | true |
| Glaze | 1548.88 | 0.262282 | 9631.49ms | 1151920 | 30 | 1.03817e+08 | 709260 | 0.856516 | 1.59839 | 3(Loss) | true |
| simdjson (ondemand) | 1307.28 | 0.156936 | 5606.32ms | 1151920 | 40 | 6.95686e+07 | 840338 | 0.784061 | 1.8938 | 4(Loss) | true |
