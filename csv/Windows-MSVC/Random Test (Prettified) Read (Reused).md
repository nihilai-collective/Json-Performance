
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.36 | 0.899012 | 6187.12ms | 728486 | 30 | 3.58265e+08 | 384393 | 0.304433 | 1.68148 | 1(Win) | true |
| Jsonifier (two-stage) | 1508.18 | 0.343179 | 7146.09ms | 728486 | 80 | 1.99926e+08 | 460648 | 0.666861 | 2.01495 | 2(Loss) | true |
| Glaze | 1257.54 | 0.205915 | 8109.44ms | 728486 | 640 | 8.28239e+08 | 552459 | 0.221471 | 2.41669 | 3(Loss) | true |
| simdjson (ondemand) | 1088.07 | 0.220741 | 9259.4ms | 728486 | 640 | 1.27139e+09 | 638508 | 0.127755 | 2.79278 | 4(Loss) | true |
