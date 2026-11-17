
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1038.49 | 0.104277 | 1251.57ms | 4630 | 1280 | 25161.6 | 4251.84 | 0.0300698 | 4.91747 | 22.7313 | 4.63391 | 0.00567208 | 5.36582e-05 | 1.11366e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 937.808 | 0.0775522 | 1305.12ms | 4630 | 2560 | 34132 | 4708.33 | 0.013397 | 5.4423 | 25.5099 | 5.0622 | 0.00584824 | 7.71126e-05 | 2.18514e-05 | 2(Loss) | true |
| simdjson (ondemand) | 878.755 | 0.159289 | 1339.6ms | 4630 | 1280 | 81998.9 | 5024.74 | 0.0600983 | 5.79611 | 28.308 | 4.76199 | 0.00208103 | 7.74501e-05 | 2.46355e-05 | 3(Loss) | true |
| Glaze | 859.833 | 0.152705 | 1342.43ms | 4630 | 640 | 39356.8 | 5135.31 | 0.168817 | 5.92417 | 26.0533 | 4.8797 | 0.00170188 | 4.15092e-05 | 6.74946e-06 | 4(Loss) | true |
