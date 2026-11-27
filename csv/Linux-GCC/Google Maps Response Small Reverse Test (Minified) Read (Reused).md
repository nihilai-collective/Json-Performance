
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 880.53 | 0.060582 | 1228.74ms | 4390 | 640 | 5310.18 | 4754.67 | 0.229771 | 5.89594 | 26.9683 | 5.40319 | 0.0120918 | 6.62016e-05 | 2.81179e-05 | 1(Win) | true |
| simdjson (ondemand) | 754.578 | 0.0759891 | 1302.33ms | 4390 | 320 | 5688.19 | 5548.31 | 0.0665623 | 6.87342 | 29.7927 | 5.74055 | 0.0127093 | 2.42027e-05 | 5.69476e-06 | 2(Loss) | true |
