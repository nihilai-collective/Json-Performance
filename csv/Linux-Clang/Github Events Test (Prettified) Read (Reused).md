
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2653.91 | 0.0917476 | 2829.56ms | 65103 | 4890 | 2.25284e+06 | 23394.6 | 0.474995 | 0.93174 | 1(Win) | true |
| Glaze | 2176.65 | 0.0783533 | 3379.95ms | 65103 | 4890 | 2.44258e+06 | 28524.1 | 0.319003 | 1.13633 | 2(Loss) | true |
| Jsonifier | 1851.58 | 0.339281 | 3910.8ms | 65103 | 320 | 4.14178e+06 | 33532 | 0.275804 | 1.33586 | 3(Loss) | true |
| simdjson (ondemand) | 1263.43 | 0.273467 | 5435.89ms | 65103 | 320 | 5.77908e+06 | 49141.6 | 0.267089 | 1.95838 | 4(Loss) | true |
