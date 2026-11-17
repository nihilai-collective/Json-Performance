
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 703.87 | 0.043824 | 9725.54ms | 264040 | 1280 | 3.14621e+07 | 357748 | 0.302335 | 7.26615 | 27.2618 | 5.12025 | 0.0224937 | 5.45816e-05 | 2.9464e-05 | 1(Win) | true |
| simdjson (ondemand) | 319.519 | 0.134254 | 5098.47ms | 264040 | 160 | 1.7911e+08 | 788086 | 0.272323 | 15.8694 | 62.9719 | 12.774 | 0.0889232 | 4.90929e-05 | 2.87362e-05 | 2(Loss) | true |
