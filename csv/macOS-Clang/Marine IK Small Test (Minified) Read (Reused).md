
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 922.945 | 0.0877668 | 622.257ms | 4604 | 80 | 1394.66 | 4757.29 | 0.0228649 | 1(Win) | true |
| Jsonifier (two-stage) | 739.473 | 0.0318344 | 742.954ms | 4604 | 320 | 1143.33 | 5937.63 | 0.00205263 | 2(Loss) | true |
| Glaze | 449.941 | 0.0751713 | 1122.68ms | 4604 | 40 | 2152.4 | 9758.42 | 0.01563 | 3(Loss) | true |
| simdjson (ondemand) | 377.225 | 0.0674798 | 1311.26ms | 4604 | 80 | 4935.24 | 11639.5 | 0.0712579 | 4(Loss) | true |
