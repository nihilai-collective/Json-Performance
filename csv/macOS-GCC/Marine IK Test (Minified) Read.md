
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 435.306 | 0.71327 | 6036.65ms | 1834197 | 80 | 6.57205e+10 | 4.01838e+06 | 1.03579 | 1(Win) | true |
| Jsonifier (generic) | 404.177 | 0.476983 | 6541.83ms | 1834197 | 30 | 1.27842e+10 | 4.32787e+06 | 2.61824 | 2(Loss) | true |
