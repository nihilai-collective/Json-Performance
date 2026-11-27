
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9467.03 | 0.151084 | 7090.91ms | 631514 | 320 | 2.95614e+06 | 63616.4 | 0.0706881 | 0.528055 | 2.67674 | 0.327108 | 0.000625001 | 4.73069e-05 | 1.45979e-06 | 1(Win) | true |
| Jsonifier | 9314.67 | 0.0952353 | 7143.01ms | 631514 | 1280 | 4.8533e+06 | 64657 | 0.575609 | 0.540765 | 2.67674 | 0.327108 | 0.000989193 | 4.37478e-05 | 2.71669e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8268.13 | 0.199608 | 8050.24ms | 631514 | 80 | 1.69121e+06 | 72841 | 0.160726 | 0.615112 | 2.90442 | 0.295473 | 0.000538151 | 2.51578e-05 | 7.46223e-06 | 3(Loss) | true |
| Glaze | 4008.03 | 0.107691 | 8008.65ms | 631514 | 80 | 2.09487e+06 | 150263 | 0.00614793 | 1.26206 | 5.34723 | 0.944654 | 0.00127357 | 2.17929e-05 | 1.54787e-05 | 4(Loss) | true |
