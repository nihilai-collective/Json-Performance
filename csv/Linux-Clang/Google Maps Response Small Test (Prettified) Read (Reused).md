
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3890.75 | 0.130313 | 991.918ms | 9378 | 1280 | 11485.2 | 2298.67 | 0.195891 | 1.32373 | 6.23331 | 1.17648 | 0.00150593 | 1.96604e-05 | 2.33259e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3065.42 | 0.116339 | 1053.76ms | 9378 | 30 | 345.633 | 2917.57 | 0.246243 | 1.67429 | 7.82502 | 1.23822 | 0.00209711 | 7.81972e-05 | 7.10884e-06 | 2(Loss) | true |
| Glaze | 2589.14 | 0.170719 | 1105.34ms | 9378 | 160 | 5564.07 | 3454.26 | 0.0166433 | 1.97748 | 9.0081 | 1.74579 | 0.00307835 | 2.93239e-05 | 7.99744e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2394.42 | 0.102369 | 1125.1ms | 9378 | 1280 | 18714 | 3735.17 | 0.0608495 | 2.16206 | 9.51845 | 1.46257 | 0.00157533 | 2.34092e-05 | 3.41557e-06 | 4(Loss) | true |
