
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 795.174 | 0.110893 | 7934.23ms | 1834197 | 160 | 9.52125e+08 | 2.1998e+06 | 0.00338854 | 1(Win) | true |
| Jsonifier (two-stage) | 676.989 | 0.167602 | 9110.98ms | 1834197 | 160 | 3.00059e+09 | 2.58383e+06 | 0.00836594 | 2(Loss) | true |
| Glaze | 541.068 | 0.188821 | 5400.83ms | 1834197 | 80 | 2.98111e+09 | 3.23292e+06 | 0.154211 | 3(Loss) | true |
| simdjson (ondemand) | 449.921 | 0.36773 | 6345.43ms | 1834197 | 40 | 8.17593e+09 | 3.88785e+06 | 0.389511 | 4(Loss) | true |
