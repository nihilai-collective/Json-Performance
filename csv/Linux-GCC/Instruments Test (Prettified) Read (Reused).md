
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4014.2 | 0.158672 | 4564.87ms | 183677 | 640 | 3.06826e+06 | 43637.1 | 0.225923 | 0.616381 | 1(Win) | true |
| Jsonifier | 2866.74 | 0.181577 | 6075.01ms | 183677 | 640 | 7.87837e+06 | 61103.5 | 0.041627 | 0.863258 | 2(Loss) | true |
| simdjson (reflection) | 2489.44 | 0.0854345 | 7130.14ms | 183677 | 1280 | 4.62576e+06 | 70364.5 | 0.166511 | 0.994142 | 3(Loss) | true |
| Glaze | 2387.53 | 0.147286 | 7490.7ms | 183677 | 2560 | 2.98933e+07 | 73367.8 | 1.28557 | 1.03661 | 4(Loss) | true |
| simdjson (ondemand) | 1900.01 | 0.0468599 | 9360.29ms | 183677 | 4890 | 9.12657e+06 | 92193 | 0.684951 | 1.30269 | 5(Loss) | true |
