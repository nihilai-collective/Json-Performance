
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2203.3 | 0.281727 | 6319.8ms | 466906 | 30 | 9.72502e+06 | 202095 | 0.0506436 | 1(Win) | true |
| Glaze | 1669.69 | 0.0785018 | 6992.5ms | 466906 | 640 | 2.80497e+07 | 266682 | 0.0979981 | 2(Loss) | true |
| Jsonifier (two-stage) | 1455.8 | 0.347229 | 7873.31ms | 466906 | 1280 | 1.44377e+09 | 305864 | 1.46642 | 3(Loss) | true |
| simdjson (reflection) | 1351.54 | 0.0925815 | 8679.38ms | 466906 | 640 | 5.95427e+07 | 329458 | 0.214317 | 4(Loss) | true |
| simdjson (ondemand) | 974.793 | 0.480204 | 5673.56ms | 466906 | 80 | 3.84925e+08 | 456790 | 0.20568 | 5(Loss) | true |
