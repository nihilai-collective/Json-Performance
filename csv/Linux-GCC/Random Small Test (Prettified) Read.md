
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2206.84 | 0.0544843 | 1085.83ms | 8150 | 1280 | 4713.29 | 3521.97 | 0.0123348 | 2.35939 | 10.0956 | 1.8535 | 0.0022985 | 4.11235e-05 | 1.7638e-05 | 1(Win) | true |
| simdjson (ondemand) | 1696.03 | 0.130882 | 1189.16ms | 8150 | 80 | 2878.07 | 4582.74 | 0.235402 | 3.0637 | 11.7348 | 2.0989 | 0.00282055 | 3.37423e-05 | 1.53374e-05 | 2(Loss) | true |
