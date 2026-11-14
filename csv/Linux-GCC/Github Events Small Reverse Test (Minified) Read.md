
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 908.174 | 0.0527933 | 895.665ms | 1691 | 2560 | 2249.82 | 1775.72 | 0.0461088 | 5.79555 | 20.67 | 4.0893 | 0.00210212 | 5.65956e-05 | 3.00303e-06 | 1(Win) | true |
| simdjson (ondemand) | 742.747 | 0.0452013 | 934.057ms | 1691 | 2560 | 2465.74 | 2171.21 | 0.014089 | 7.05573 | 27.5801 | 5.38676 | 0.00120514 | 6.09846e-05 | 7.85408e-06 | 2(Loss) | true |
