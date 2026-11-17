
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5753.71 | 0.224463 | 779.112ms | 2889 | 160 | 184.845 | 478.85 | 0.218796 | 0.956012 | 3.75666 | 0.480789 | 0.000356957 | 7.13915e-05 | 3.24507e-05 | 1(Win) | true |
| Jsonifier | 5721.75 | 0.14687 | 777.959ms | 2889 | 640 | 320.1 | 481.525 | 0.280866 | 0.95605 | 3.75666 | 0.480789 | 0.000346681 | 4.97577e-05 | 1.67662e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5611.33 | 0.123396 | 778.33ms | 2889 | 2560 | 939.729 | 491 | 0.106731 | 0.976239 | 3.82624 | 0.399792 | 0.000715943 | 1.7307e-05 | 3.24507e-06 | 3(Loss) | true |
| simdjson (reflection) | 5371.08 | 0.225054 | 781.937ms | 2889 | 80 | 106.619 | 512.962 | 0.0754846 | 1.01775 | 3.81308 | 0.406369 | 0.000891312 | 8.65351e-06 | 0 | 4(Loss) | true |
| Glaze | 3147.95 | 0.283213 | 815.146ms | 2889 | 40 | 245.769 | 875.225 | 0.0504378 | 1.71327 | 7.17965 | 1.22603 | 0.000346141 | 8.65351e-06 | 8.65351e-06 | 5(Loss) | true |
