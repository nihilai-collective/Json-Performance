
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9451.29 | 0.0865442 | 6351.98ms | 631514 | 2560 | 7.78574e+06 | 63722.4 | 0.16764 | 0.261786 | 1(Win) | true |
| Jsonifier | 9430.62 | 0.0592342 | 6349.24ms | 631514 | 4890 | 6.99745e+06 | 63862 | 0.733219 | 0.262361 | 2(Loss) | true |
| simdjson (ondemand) | 8874.28 | 0.107867 | 6991.24ms | 631514 | 1280 | 6.85945e+06 | 67865.7 | 0.443323 | 0.278843 | 3(Loss) | true |
| simdjson (reflection) | 8848.84 | 0.0744354 | 6886.56ms | 631514 | 4890 | 1.25505e+07 | 68060.8 | 0.0265088 | 0.27963 | 4(Loss) | true |
| Glaze | 3708.21 | 0.128549 | 8428.6ms | 631514 | 320 | 1.39483e+07 | 162412 | 0.353456 | 0.667531 | 5(Loss) | true |
