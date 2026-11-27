
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 432.012 | 0.312232 | 6092.43ms | 1834197 | 80 | 1.27863e+10 | 4.04902e+06 | 0.945853 | 1(Win) | true |
| simdjson (ondemand) | 414.387 | 0.16868 | 6360.99ms | 1834197 | 40 | 2.02799e+09 | 4.22124e+06 | 0.284029 | 2(Loss) | true |
