
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2051.13 | 0.123934 | 7823.26ms | 5373214 | 30 | 2.87597e+08 | 2.49828e+06 | 0.0498284 | 1.20702 | 1(Win) | true |
| Jsonifier | 1957.61 | 0.373069 | 8138.28ms | 5373214 | 80 | 7.62926e+09 | 2.61763e+06 | 0.67354 | 1.26468 | 2(Loss) | true |
| simdjson (ondemand) | 1702.4 | 0.108453 | 9351.07ms | 5373214 | 30 | 3.19709e+08 | 3.01005e+06 | 0.234209 | 1.4543 | 3(Loss) | true |
| Glaze | 1601.19 | 0.0473738 | 10104.4ms | 5373214 | 160 | 3.67771e+08 | 3.2003e+06 | 0.386161 | 1.54622 | 4(Loss) | true |
