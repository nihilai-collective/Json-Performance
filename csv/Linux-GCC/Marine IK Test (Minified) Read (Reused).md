
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 975.552 | 0.0629995 | 6299.9ms | 1834197 | 80 | 1.02083e+08 | 1.79306e+06 | 0.0432303 | 5.17821 | 22.4717 | 4.72702 | 0.0306659 | 0.0570952 | 3.93565e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 823.805 | 0.0330409 | 7356.85ms | 1834197 | 160 | 7.87528e+07 | 2.12335e+06 | 0.173487 | 6.1296 | 25.9312 | 5.17251 | 0.0366105 | 0.120704 | 5.56715e-05 | 2(Loss) | true |
| Glaze | 723.232 | 0.0641825 | 8282.45ms | 1834197 | 40 | 9.63897e+07 | 2.41863e+06 | 0.0214862 | 6.98338 | 29.3558 | 5.62414 | 0.0336529 | 0.0598081 | 3.18259e-05 | 3(Loss) | true |
| simdjson (reflection) | 694.034 | 0.0250374 | 8543.68ms | 1834197 | 160 | 6.37133e+07 | 2.52038e+06 | 0.00612148 | 7.27825 | 31.8444 | 5.81342 | 0.0319422 | 0.112362 | 0.000753293 | 4(Loss) | true |
| simdjson (ondemand) | 572.169 | 0.0743607 | 10242.3ms | 1834197 | 30 | 1.55043e+08 | 3.05718e+06 | 0.0217099 | 8.80983 | 34.453 | 6.64592 | 0.0372044 | 0.118953 | 0.000145513 | 5(Loss) | true |
