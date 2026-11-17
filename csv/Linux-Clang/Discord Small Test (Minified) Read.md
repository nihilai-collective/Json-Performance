
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1419 | 0.0250049 | 1054.17ms | 4857 | 4890 | 3257.84 | 3264.27 | 0.094966 | 3.67286 | 14.5713 | 2.86236 | 0.00190049 | 5.34299e-05 | 1.39785e-05 | 1(Win) | true |
| simdjson (ondemand) | 1330.81 | 0.0334122 | 1072.09ms | 4857 | 2560 | 3462.2 | 3480.57 | 0.00415269 | 3.91177 | 15.5164 | 2.61952 | 0.00182742 | 3.30547e-05 | 2.89531e-06 | 2(Loss) | true |
