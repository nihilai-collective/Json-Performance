
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1625.33 | 0.080954 | 5542.85ms | 728486 | 320 | 3.83167e+07 | 427446 | 0.00155139 | 1(Win) | true |
| Jsonifier (two-stage) | 1248.25 | 0.0687269 | 7357.85ms | 728486 | 160 | 2.34107e+07 | 556570 | 0.106884 | 2(Loss) | true |
| Glaze | 1070.85 | 1.18061 | 8306.79ms | 728486 | 40 | 2.34669e+09 | 648772 | 1.69858 | 3(Loss) | true |
| simdjson (ondemand) | 992.151 | 0.13856 | 9149.47ms | 728486 | 640 | 6.02481e+08 | 700235 | 0.172578 | 4(Loss) | true |
