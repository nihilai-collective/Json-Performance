
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 954.059 | 0.154713 | 9528.49ms | 728486 | 320 | 4.06159e+08 | 728192 | 0.752127 | 2.59489 | 1(Win) | true |
| Jsonifier | 922.935 | 0.211539 | 9841.45ms | 728486 | 80 | 2.02848e+08 | 752749 | 0.816429 | 2.68237 | 2(Loss) | true |
| Glaze | 874.659 | 0.641248 | 5049.11ms | 728486 | 80 | 2.07543e+09 | 794296 | 0.249127 | 2.83041 | 3(Loss) | true |
| simdjson (ondemand) | 706.83 | 0.538974 | 6161.88ms | 728486 | 80 | 2.24511e+09 | 982892 | 1.02319 | 3.50256 | 4(Loss) | true |
