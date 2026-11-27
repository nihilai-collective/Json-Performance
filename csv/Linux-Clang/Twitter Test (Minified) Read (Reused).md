
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2165.56 | 0.0381894 | 7009.01ms | 264040 | 2560 | 5.04807e+06 | 116279 | 0.7584 | 2.35701 | 9.03209 | 1.5642 | 0.00639373 | 3.3707e-05 | 1.72885e-05 | 1(Win) | true |
| simdjson (ondemand) | 1875.78 | 0.0802284 | 8023.7ms | 264040 | 640 | 7.42358e+06 | 134242 | 0.0391494 | 2.68788 | 9.81503 | 1.50842 | 0.0100853 | 3.71274e-05 | 1.26401e-05 | 2(Loss) | true |
