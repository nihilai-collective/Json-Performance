
----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.162 | 0.0440369 | 7852.22ms | 56369 | 640 | 575920 | 68119.9 | 0.179194 | 6.5108 | 33.074 | 6.7659 | 0.00944097 | 9.84029e-06 | 1.74631e-06 | 1(Win) | true |
| simdjson (ondemand) | 215.774 | 0.125346 | 6651.28ms | 56369 | 80 | 7.80173e+06 | 249138 | 0.0743812 | 23.7649 | 137.612 | 27.6215 | 0.0326857 | 4.05808e-05 | 2.04013e-05 | 2(Loss) | true |
