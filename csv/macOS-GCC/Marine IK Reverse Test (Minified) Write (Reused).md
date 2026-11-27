
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1306.35 | 0.0849535 | 9064.4ms | 1922245 | 30 | 4.26367e+07 | 1.4033e+06 | 0.0783823 | 1(Win) | true |
| Jsonifier | 1220.3 | 0.766348 | 8726.55ms | 1922245 | 40 | 5.30144e+09 | 1.50225e+06 | 1.40287 | 2(Loss) | true |
| Glaze | 818.28 | 0.524853 | 6795.63ms | 1833577 | 160 | 2.01275e+10 | 2.13696e+06 | 1.82245 | 3(Loss) | true |
