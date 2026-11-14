
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19567 | 0.181857 | 3077.63ms | 475954 | 1280 | 2.27799e+06 | 23197.5 | 0.402926 | 0.257965 | 1.01871 | 0.152632 | 0.000281079 | 0.000735917 | 2.48022e-06 | 1(Win) | true |
| Glaze | 6896.44 | 0.138558 | 7361.84ms | 475954 | 4890 | 4.06679e+07 | 65817.3 | 0.0193264 | 0.732049 | 2.35134 | 0.334375 | 0.000344866 | 0.00183827 | 4.8904e-06 | 2(Loss) | true |
