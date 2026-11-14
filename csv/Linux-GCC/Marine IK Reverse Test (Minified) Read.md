
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 855.896 | 0.0680093 | 6412.8ms | 1834197 | 160 | 3.09105e+08 | 2.04374e+06 | 0.018011 | 5.86722 | 25.8828 | 5.55398 | 0.0301936 | 0.082353 | 0.0028913 | 1(Win) | true |
| Jsonifier (two-stage) | 722.648 | 0.065 | 7625.79ms | 1834197 | 160 | 3.96082e+08 | 2.42058e+06 | 0.928629 | 6.95253 | 29.3424 | 5.98071 | 0.0368552 | 0.14529 | 0.0222914 | 2(Loss) | true |
| Glaze | 644.696 | 0.438977 | 8322.05ms | 1834197 | 40 | 5.67448e+09 | 2.71326e+06 | 0.491059 | 7.7368 | 32.3736 | 6.32381 | 0.0345806 | 0.0837062 | 0.00606429 | 3(Loss) | true |
| simdjson (reflection) | 620.652 | 0.0565425 | 8767.06ms | 1834197 | 40 | 1.01579e+08 | 2.81837e+06 | 0.0998789 | 8.13161 | 34.8333 | 6.48953 | 0.0370935 | 0.135875 | 0.00846875 | 4(Loss) | true |
| simdjson (ondemand) | 515.522 | 0.349963 | 5064.47ms | 1834197 | 80 | 1.12806e+10 | 3.39312e+06 | 0.3396 | 9.84682 | 38.0357 | 7.35418 | 0.0418221 | 0.147086 | 0.0382246 | 5(Loss) | true |
