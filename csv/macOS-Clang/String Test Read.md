
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1031.24 | 0.107933 | 364.272ms | 4215 | 40 | 708.025 | 3897.97 | 0.0558294 | 1(Win) | true |
| Glaze | 806.864 | 0.194456 | 497.277ms | 4215 | 1280 | 120128 | 4981.93 | 0.169461 | 2(Loss) | true |
| simdjson (ondemand) | 680.586 | 0.0873595 | 594.704ms | 4215 | 80 | 2129.8 | 5906.29 | 0.106992 | 3(Loss) | true |
