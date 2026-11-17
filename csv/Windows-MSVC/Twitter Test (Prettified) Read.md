
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1399.93 | 0.315472 | 5480.14ms | 631514 | 640 | 1.17884e+09 | 430207 | 0.0291925 | 2.17077 | 1(Win) | true |
| Glaze | 1360.97 | 0.404371 | 5664.98ms | 631514 | 320 | 1.02466e+09 | 442521 | 0.527125 | 2.23301 | 2(Loss) | true |
| Jsonifier | 1323.84 | 0.916885 | 5850.66ms | 631514 | 80 | 1.39192e+09 | 454932 | 0.627993 | 2.29531 | 3(Loss) | true |
| simdjson (ondemand) | 1183.89 | 0.298634 | 6562.03ms | 631514 | 30 | 6.92375e+07 | 508710 | 0.0779143 | 2.567 | 4(Loss) | true |
