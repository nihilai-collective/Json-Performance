
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 288.601 | 0.276868 | 9155.98ms | 1834197 | 80 | 2.25284e+10 | 6.06105e+06 | 3.60112 | 1(Win) | true |
| simdjson (ondemand) | 183.083 | 0.549136 | 6469.47ms | 1834197 | 30 | 8.25802e+10 | 9.55426e+06 | 3.81148 | 2(Loss) | true |
