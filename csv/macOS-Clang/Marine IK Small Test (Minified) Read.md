
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 349.136 | 0.969502 | 1223.11ms | 4604 | 80 | 1.18924e+06 | 12575.9 | 0.574713 | 1(Win) | true |
| simdjson (ondemand) | 338.439 | 0.0747626 | 1315.79ms | 4604 | 4890 | 460032 | 12973.4 | 0.155467 | 2(Loss) | true |
