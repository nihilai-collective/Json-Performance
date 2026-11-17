
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1713.63 | 0.203988 | 5304.94ms | 728486 | 40 | 2.73575e+07 | 405419 | 0.122981 | 1.44464 | 1(Win) | true |
| simdjson (reflection) | 1704.03 | 0.195837 | 5035.94ms | 728486 | 160 | 1.01999e+08 | 407703 | 0.237306 | 1.45278 | 2(Loss) | true |
| Jsonifier (two-stage) | 1678.48 | 0.0580554 | 5336.55ms | 728486 | 320 | 1.84775e+07 | 413908 | 0.0867248 | 1.47491 | 3(Loss) | true |
| Jsonifier | 1534.95 | 0.0740074 | 5750.25ms | 728486 | 640 | 7.18095e+07 | 452612 | 0.178591 | 1.61283 | 4(Loss) | true |
| Glaze | 1423 | 0.229092 | 6336.15ms | 728486 | 30 | 3.75297e+07 | 488222 | 0.0124549 | 1.73976 | 5(Loss) | true |
