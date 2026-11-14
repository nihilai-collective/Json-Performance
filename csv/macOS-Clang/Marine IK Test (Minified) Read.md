
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 608.845 | 0.181989 | 8973.9ms | 1834197 | 160 | 4.3741e+09 | 2.87303e+06 | 0.0516129 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 605.001 | 0.604629 | 8789.2ms | 1834197 | 40 | 1.22241e+10 | 2.89128e+06 | 3.02804 | 1(Tie) | true |
| simdjson (ondemand) | 417.264 | 0.186298 | 6382.92ms | 1834197 | 30 | 1.82982e+09 | 4.19214e+06 | 1.36386 | 3(Loss) | true |
| Glaze | 396.337 | 1.67018 | 6558.45ms | 1834197 | 40 | 2.17345e+11 | 4.41348e+06 | 0.47184 | 4(Loss) | true |
