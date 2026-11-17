
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2192.37 | 0.220746 | 10084.7ms | 7351818 | 160 | 7.97384e+09 | 3.19802e+06 | 0.978177 | 1.12927 | 1(Win) | true |
| Jsonifier | 2104.69 | 0.257531 | 5064.69ms | 7351818 | 80 | 5.8879e+09 | 3.33124e+06 | 1.02706 | 1.17632 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 803.888 | 0.594751 | 6283.23ms | 7351818 | 40 | 1.07629e+11 | 8.72166e+06 | 3.82863 | 3.07979 | -(Loss) | false |
| Glaze | 715.423 | 0.268034 | 7060.82ms | 7351818 | 40 | 2.75996e+10 | 9.80014e+06 | 2.03999 | 3.46062 | 4(Loss) | true |
