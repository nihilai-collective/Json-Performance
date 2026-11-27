
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1181.96 | 0.297387 | 7593.86ms | 728486 | 320 | 9.77756e+08 | 587786 | 0.0570261 | 2.0945 | 1(Win) | true |
| Jsonifier (two-stage) | 1022.17 | 0.0919104 | 8824.39ms | 728486 | 640 | 2.49752e+08 | 679672 | 0.304425 | 2.42196 | 2(Loss) | true |
| Glaze | 886.714 | 0.374881 | 5037.57ms | 728486 | 40 | 3.45082e+08 | 783498 | 1.41662 | 2.79195 | 3(Loss) | true |
| simdjson (ondemand) | 736.576 | 0.220005 | 5948.83ms | 728486 | 30 | 1.29179e+08 | 943200 | 0.12354 | 3.36115 | 4(Loss) | true |
