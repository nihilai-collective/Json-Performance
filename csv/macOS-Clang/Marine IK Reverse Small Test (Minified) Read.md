
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 493.324 | 0.786915 | 892.002ms | 4604 | 320 | 1.56968e+06 | 8900.27 | 1.50315 | 1(Win) | true |
| Jsonifier (two-stage) | 439.617 | 0.285825 | 996.173ms | 4604 | 4890 | 3.98502e+06 | 9987.59 | 1.83288 | 2(Loss) | true |
| Glaze | 387.989 | 0.108038 | 1229.4ms | 4604 | 30 | 4484.46 | 11316.6 | 0.17231 | 3(Loss) | true |
| simdjson (ondemand) | 315.44 | 0.162207 | 1501.69ms | 4604 | 4890 | 2.49281e+06 | 13919.4 | 1.85362 | 4(Loss) | true |
