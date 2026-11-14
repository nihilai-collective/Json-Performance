
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 999.406 | 0.0500785 | 886.532ms | 1691 | 320 | 208.957 | 1613.62 | 0.0334926 | 5.28414 | 19.3631 | 3.75931 | 0.00207717 | 8.50089e-05 | 3.69604e-06 | 1(Win) | true |
| simdjson (ondemand) | 803.763 | 0.0775094 | 926.028ms | 1691 | 1280 | 3095.63 | 2006.39 | 0.0106679 | 6.53016 | 26.2673 | 5.05677 | 0.00144238 | 4.15804e-05 | 1.38601e-06 | 2(Loss) | true |
