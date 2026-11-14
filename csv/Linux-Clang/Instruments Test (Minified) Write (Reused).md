
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18686.2 | 0.0646234 | 1304.69ms | 108313 | 4890 | 62403.3 | 5527.89 | 0.0633494 | 0.27229 | 1.2424 | 0.327145 | 0.000205847 | 5.76607e-06 | 2.77164e-06 | 1(Win) | true |
| Glaze | 5099.14 | 0.130249 | 2773.48ms | 108313 | 2560 | 1.7822e+06 | 20257.4 | 0.179239 | 0.992516 | 3.21806 | 0.400866 | 0.000314612 | 7.28502e-06 | 3.58481e-06 | 2(Loss) | true |
