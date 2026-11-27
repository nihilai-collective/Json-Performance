
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 951.617 | 0.0820693 | 7714.18ms | 2090234 | 80 | 2.36438e+08 | 2.09475e+06 | 0.279928 | 5.33094 | 25.0907 | 4.35762 | 0.0219478 | 0.0788239 | 0.000185679 | 1(Win) | true |
| Jsonifier (generic) | 916.141 | 0.112064 | 7969.87ms | 2090234 | 40 | 2.37827e+08 | 2.17587e+06 | 0.159036 | 5.51395 | 24.9876 | 4.95425 | 0.0260968 | 0.0785777 | 0.00121344 | 2(Loss) | true |
