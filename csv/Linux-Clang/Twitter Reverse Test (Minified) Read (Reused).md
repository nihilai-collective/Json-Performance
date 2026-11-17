
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 743.923 | 0.12288 | 9247.24ms | 264040 | 80 | 1.384e+07 | 338487 | 0.218184 | 6.92036 | 27.0501 | 4.97757 | 0.0214448 | 8.39835e-05 | 5.96027e-05 | 1(Win) | true |
| simdjson (ondemand) | 284.645 | 0.154902 | 5746.54ms | 264040 | 80 | 1.50224e+08 | 884640 | 0.0925846 | 17.6789 | 71.2958 | 12.4072 | 0.0879522 | 7.15801e-05 | 1.23087e-05 | 2(Loss) | true |
