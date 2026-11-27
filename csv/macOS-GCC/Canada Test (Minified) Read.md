
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 524.768 | 0.111727 | 5838.36ms | 2090234 | 30 | 5.40377e+08 | 3.79864e+06 | 4.73991 | 1(Win) | true |
| simdjson (ondemand) | 519.263 | 0.133722 | 5812.94ms | 2090234 | 30 | 7.90572e+08 | 3.83891e+06 | 4.8252 | 2(Loss) | true |
