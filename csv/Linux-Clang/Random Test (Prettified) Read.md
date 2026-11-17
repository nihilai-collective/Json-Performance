
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22540 | 0.0864495 | 3092.26ms | 728486 | 2560 | 1.81761e+06 | 30822.5 | 0.305837 | 0.109746 | 1(Win) | true |
| simdjson (stage-1) | 20555.1 | 0.0667033 | 3443.16ms | 728486 | 4890 | 2.48546e+06 | 33798.8 | 0.169129 | 0.120353 | 2(Loss) | true |
