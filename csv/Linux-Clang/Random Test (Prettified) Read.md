
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1931.27 | 0.0956669 | 9219.16ms | 728486 | 320 | 3.78991e+07 | 359731 | 0.222273 | 1.2818 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.44 | 0.26094 | 5107.56ms | 728486 | 30 | 3.26609e+07 | 399864 | 0.683715 | 1.42478 | 2(Loss) | true |
| Glaze | 1380.06 | 0.0812304 | 6389.9ms | 728486 | 320 | 5.35096e+07 | 503410 | 0.0669167 | 1.79382 | 3(Loss) | true |
| simdjson (ondemand) | 1187.65 | 0.139793 | 7451.53ms | 728486 | 30 | 2.00611e+07 | 584969 | 0.0582882 | 2.08447 | 4(Loss) | true |
