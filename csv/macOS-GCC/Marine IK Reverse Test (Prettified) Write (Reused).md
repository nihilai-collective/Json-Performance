
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6339.18 | 0.432247 | 9502.71ms | 10018896 | 160 | 6.79139e+09 | 1.50726e+06 | 2.32326 | 1(Win) | true |
| Glaze | 2969.62 | 0.701388 | 9591.42ms | 9930228 | 30 | 1.50091e+10 | 3.18903e+06 | 1.49893 | 2(Loss) | true |
| simdjson (reflection) | 289.452 | 0.563125 | 10091.3ms | 10018896 | 30 | 1.03662e+12 | 3.30099e+07 | 1.85328 | 3(Loss) | true |
