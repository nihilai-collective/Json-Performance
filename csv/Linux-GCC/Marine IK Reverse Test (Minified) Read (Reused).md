
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 952.453 | 0.10658 | 6501.86ms | 1834197 | 40 | 1.53255e+08 | 1.83655e+06 | 0.0704267 | 5.28521 | 22.8799 | 4.85497 | 0.0294873 | 0.0557447 | 0.00235787 | 1(Win) | true |
| Jsonifier (two-stage) | 809.845 | 0.149814 | 7467.78ms | 1834197 | 30 | 3.14134e+08 | 2.15995e+06 | 0.0576796 | 6.20809 | 26.3402 | 5.28156 | 0.0359092 | 0.119045 | 0.00519304 | 2(Loss) | true |
| Glaze | 714.139 | 0.148012 | 8343.17ms | 1834197 | 160 | 2.10301e+09 | 2.44942e+06 | 0.032158 | 7.03866 | 29.3656 | 5.62362 | 0.0329781 | 0.0599391 | 0.00245458 | 3(Loss) | true |
| simdjson (reflection) | 691.038 | 0.0754897 | 8504.01ms | 1834197 | 40 | 1.46057e+08 | 2.5313e+06 | 0.00859563 | 7.31846 | 31.8035 | 5.77319 | 0.0321438 | 0.111769 | 0.00023558 | 4(Loss) | true |
| simdjson (ondemand) | 578.218 | 0.0843846 | 10094.5ms | 1834197 | 40 | 2.60672e+08 | 3.0252e+06 | 0.145121 | 8.73813 | 35.013 | 6.65235 | 0.0370686 | 0.118575 | 0.0178394 | 5(Loss) | true |
