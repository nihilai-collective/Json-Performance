
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1065.77 | 0.139459 | 8773.63ms | 676745 | 320 | 2.28227e+08 | 605568 | 0.122746 | 1(Win) | true |
| simdjson (ondemand) | 580.883 | 0.569943 | 7503.74ms | 676745 | 30 | 1.20297e+09 | 1.11106e+06 | 1.15244 | 2(Loss) | true |
