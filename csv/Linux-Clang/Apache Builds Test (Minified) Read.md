
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1560.89 | 0.152179 | 5773.71ms | 94653 | 320 | 2.4785e+06 | 57831.4 | 0.270164 | 1.58537 | 1(Win) | true |
| Jsonifier (two-stage) | 1433.19 | 0.082476 | 6304.23ms | 94653 | 1280 | 3.45406e+06 | 62984.3 | 0.171819 | 1.7267 | 2(Loss) | true |
| Glaze | 1382.4 | 0.0680098 | 6618.22ms | 94653 | 1280 | 2.52439e+06 | 65298.3 | 0.129925 | 1.79019 | 3(Loss) | true |
| simdjson (ondemand) | 1036.03 | 0.124023 | 8733.73ms | 94653 | 2560 | 2.98931e+07 | 87128.8 | 0.445007 | 2.38894 | 4(Loss) | true |
