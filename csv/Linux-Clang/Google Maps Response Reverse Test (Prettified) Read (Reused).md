
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1641.56 | 0.0435208 | 2284.66ms | 25388 | 1280 | 52741.2 | 14749.3 | 0.113603 | 3.12137 | 14.1985 | 2.78395 | 0.00666343 | 2.67105e-05 | 1.73249e-05 | 1(Win) | true |
| simdjson (ondemand) | 1484.73 | 0.106755 | 2418.22ms | 25388 | 320 | 96980.3 | 16307.2 | 0.283367 | 3.4299 | 15.3514 | 2.72645 | 0.00645064 | 1.46477e-05 | 4.30814e-06 | 2(Loss) | true |
