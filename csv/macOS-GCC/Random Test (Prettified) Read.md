
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6382.93 | 0.758033 | 5770ms | 728486 | 160 | 1.08918e+08 | 108843 | 3.34052 | 1(Win) | true |
| simdjson (stage-1) | 5282.21 | 1.40577 | 6477.84ms | 728486 | 30 | 1.02556e+08 | 131524 | 2.04017 | 2(Loss) | true |
