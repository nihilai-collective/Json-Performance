
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22207.8 | 0.0752173 | 3157.4ms | 728486 | 4890 | 2.70753e+06 | 31283.5 | 0.0879414 | 0.111388 | 1(Win) | true |
| simdjson (stage-1) | 20445 | 0.0701583 | 3428.21ms | 728486 | 2560 | 1.45502e+06 | 33980.9 | 0.057531 | 0.120994 | 2(Loss) | true |
