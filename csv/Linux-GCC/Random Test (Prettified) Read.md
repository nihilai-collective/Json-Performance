
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 19775.7 | 0.0478449 | 3523.45ms | 728486 | 4890 | 1.38152e+06 | 35130.8 | 0.00127616 | 0.125088 | 1(Win) | true |
| simdjson (stage-1) | 17232.7 | 0.0667444 | 4045.29ms | 728486 | 2560 | 1.85357e+06 | 40315.2 | 0.0715051 | 0.143561 | 2(Loss) | true |
