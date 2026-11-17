
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 655.724 | 0.535407 | 8031.2ms | 1834197 | 40 | 8.15976e+09 | 2.66763e+06 | 1.1001 | 1(Win) | true |
| Jsonifier (two-stage) | 580.743 | 0.784641 | 10126ms | 1834197 | 80 | 4.46844e+10 | 3.01205e+06 | 1.54862 | 2(Loss) | true |
| Glaze | 421.411 | 1.00506 | 6310.32ms | 1834197 | 30 | 5.2214e+10 | 4.15088e+06 | 0.631944 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 390.169 | 1.51613 | 7495.68ms | 1834197 | 30 | 1.38605e+11 | 4.48325e+06 | 7.42148 | -(Loss) | false |
