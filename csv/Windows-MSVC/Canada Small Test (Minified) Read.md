
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 585.854 | 0.272267 | 767.424ms | 4630 | 160 | 67373.8 | 7536.88 | 0.00829325 | 5.17479 | 1(Win) | true |
| Jsonifier (two-stage) | 540.454 | 0.215902 | 824.19ms | 4630 | 640 | 199130 | 8170 | 0.168016 | 5.61043 | 2(Loss) | true |
| simdjson (ondemand) | 337.416 | 0.209218 | 1337.47ms | 4630 | 160 | 119936 | 13086.2 | 0 | 8.99518 | 3(Loss) | true |
| Glaze | 315.411 | 0.287662 | 1405.12ms | 4630 | 4890 | 7.93019e+06 | 13999.2 | 0.0504271 | 9.60471 | 4(Loss) | true |
