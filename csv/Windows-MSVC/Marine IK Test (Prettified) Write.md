
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2431.71 | 0.129573 | 5866.17ms | 9930848 | 80 | 2.03736e+09 | 3.89471e+06 | 0.543381 | 1.24983 | 1(Win) | true |
| Glaze | 1272.05 | 0.268665 | 5215.68ms | 9930228 | 30 | 1.2002e+10 | 7.44483e+06 | 0.173109 | 2.38934 | 2(Loss) | true |
