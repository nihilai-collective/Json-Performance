
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1132.3 | 0.752978 | 9652.73ms | 1834197 | 160 | 2.16498e+10 | 1.54484e+06 | 0.718526 | 4.49525 | 12.5637 | 0.909502 | 0.00167447 | 0.0583678 | 0.000498256 | 1(Win) | true |
| Glaze | 641.663 | 0.31594 | 8509.82ms | 1833577 | 160 | 1.18608e+10 | 2.72516e+06 | 0.169162 | 7.99149 | 16.0113 | 0.996381 | 0.00111013 | 0.04935 | 0.00119472 | 2(Loss) | true |
