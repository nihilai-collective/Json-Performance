
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 873.378 | 0.204696 | 6966.47ms | 1834197 | 30 | 5.04229e+08 | 2.00283e+06 | 0.143044 | 2.83469 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 814.158 | 0.27714 | 7589.26ms | 1834197 | 160 | 5.67274e+09 | 2.14851e+06 | 14.3025 | 3.04088 | -(Loss) | false |
| Glaze | 688.761 | 0.238906 | 8603.59ms | 1834197 | 80 | 2.94511e+09 | 2.53967e+06 | 0.750018 | 3.59453 | 3(Loss) | true |
| simdjson (ondemand) | 627.838 | 0.0842963 | 9509.85ms | 1834197 | 40 | 2.20635e+08 | 2.78611e+06 | 0.441571 | 3.9433 | 4(Loss) | true |
