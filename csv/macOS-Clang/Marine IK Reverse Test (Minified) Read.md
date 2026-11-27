
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 293.139 | 0.297696 | 9005.15ms | 1834197 | 40 | 1.26227e+10 | 5.96723e+06 | 0.362627 | 1(Win) | true |
| simdjson (ondemand) | 193.19 | 0.165702 | 6399.6ms | 1834197 | 30 | 6.75306e+09 | 9.05442e+06 | 0.157043 | 2(Loss) | true |
