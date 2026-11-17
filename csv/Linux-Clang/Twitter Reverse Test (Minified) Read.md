
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 676.829 | 0.0988893 | 9629.97ms | 264040 | 160 | 2.16571e+07 | 372041 | 0.0857411 | 7.47239 | 28.4742 | 5.30754 | 0.0254246 | 0.000622183 | 2.49962e-05 | 1(Win) | true |
| simdjson (ondemand) | 275.391 | 0.143657 | 5855ms | 264040 | 160 | 2.76064e+08 | 914365 | 0.0175105 | 18.3083 | 72.7168 | 12.735 | 0.0932338 | 0.000204728 | 0.000114542 | 2(Loss) | true |
