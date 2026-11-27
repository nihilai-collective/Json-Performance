
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.9 | 0.142799 | 2194.54ms | 25388 | 320 | 124493 | 13812.5 | 0.0466282 | 2.91562 | 13.7775 | 2.66772 | 0.00645507 | 5.34209e-05 | 3.23726e-05 | 1(Win) | true |
| simdjson (ondemand) | 1577.8 | 0.0841556 | 2356.21ms | 25388 | 320 | 53366.8 | 15345.4 | 0.0288481 | 3.27149 | 14.7003 | 2.74484 | 0.00726487 | 1.40322e-05 | 5.66212e-06 | 2(Loss) | true |
