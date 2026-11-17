
----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.015 | 0.0219679 | 8148.41ms | 56369 | 2560 | 616466 | 70639.4 | 0.215898 | 6.7167 | 33.1011 | 6.7667 | 0.0097834 | 1.00828e-05 | 1.57999e-06 | 1(Win) | true |
| simdjson (ondemand) | 204.863 | 0.0608409 | 6998.7ms | 56369 | 640 | 1.63127e+07 | 262408 | 0.208623 | 24.9751 | 137.674 | 27.6535 | 0.0315694 | 3.14612e-05 | 1.25845e-05 | 2(Loss) | true |
