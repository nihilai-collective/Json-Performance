
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1267.51 | 0.378382 | 6050.9ms | 5212421 | 80 | 1.76168e+10 | 3.92182e+06 | 0.539919 | 1(Win) | true |
| simdjson (ondemand) | 1183.08 | 0.215844 | 6237.09ms | 5212421 | 80 | 6.57993e+09 | 4.2017e+06 | 0.0735922 | 2(Loss) | true |
