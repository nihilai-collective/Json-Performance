
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1385.96 | 0.135436 | 842.443ms | 1811 | 2560 | 7291.99 | 1246.14 | 0.0134809 | 3.79851 | 16.8459 | 3.40972 | 0.000909805 | 0.00022799 | 8.67097e-05 | 1(Win) | true |
| Glaze | 1101.95 | 0.12916 | 874.281ms | 1811 | 1280 | 5245.37 | 1567.31 | 0.0134604 | 4.82884 | 24.7974 | 3.4804 | 0.00206033 | 0.00013028 | 2.89032e-05 | 2(Loss) | true |
| simdjson (ondemand) | 440.507 | 0.0654341 | 1108.92ms | 1811 | 2560 | 16849.2 | 3920.71 | 0.0461305 | 11.8315 | 56.7847 | 11.2662 | 0.00116131 | 0.000261208 | 7.89446e-05 | 3(Loss) | true |
| simdjson (reflection) | 416.755 | 0.083358 | 1134.49ms | 1811 | 2560 | 30549.9 | 4144.17 | 0.346476 | 12.4141 | 59.0812 | 11.6941 | 0.00113111 | 0.000413704 | 0.000192401 | 4(Loss) | true |
