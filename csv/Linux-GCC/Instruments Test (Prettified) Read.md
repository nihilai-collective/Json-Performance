
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3567.85 | 0.108393 | 4870.42ms | 183677 | 2560 | 7.25004e+06 | 49096.3 | 0.378671 | 0.693484 | 1(Win) | true |
| Jsonifier | 3515.89 | 0.111336 | 4969.36ms | 183677 | 1280 | 3.93842e+06 | 49821.8 | 0.87831 | 0.703773 | 2(Loss) | true |
| simdjson (reflection) | 2488.65 | 0.0510671 | 6958.18ms | 183677 | 4890 | 6.31794e+06 | 70386.9 | 0.336285 | 0.994436 | 3(Loss) | true |
| Glaze | 2181.09 | 0.0714007 | 8151.05ms | 183677 | 1280 | 4.20898e+06 | 80312.1 | 0.162589 | 1.13474 | 4(Loss) | true |
| simdjson (ondemand) | 2032.6 | 0.0962979 | 8524.66ms | 183677 | 1280 | 8.81554e+06 | 86179.2 | 0.364429 | 1.21764 | 5(Loss) | true |
