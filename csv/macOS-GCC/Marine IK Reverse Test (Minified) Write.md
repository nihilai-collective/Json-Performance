
----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1264.16 | 0.986408 | 9069.75ms | 1922245 | 30 | 6.13829e+09 | 1.45013e+06 | 1.51917 | 1(Win) | true |
| simdjson (reflection) | 1201.89 | 0.412004 | 9099.98ms | 1922245 | 30 | 1.18472e+09 | 1.52527e+06 | 0.657754 | 2(Loss) | true |
| Glaze | 944.267 | 0.125495 | 6776.38ms | 1833577 | 30 | 1.62026e+08 | 1.85184e+06 | 0.450926 | 3(Loss) | true |
