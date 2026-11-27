
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 961.716 | 0.0619262 | 1254.65ms | 4926 | 1280 | 11712.6 | 4884.81 | 0.112336 | 5.39708 | 24.1768 | 4.86764 | 0.00806213 | 0.000133856 | 7.26375e-05 | 1(Win) | true |
| simdjson (ondemand) | 488.32 | 0.0411497 | 1727.05ms | 4926 | 2560 | 40119.3 | 9620.34 | 0.0231227 | 10.5615 | 46.528 | 8.34755 | 0.0279639 | 0.000101344 | 4.58346e-05 | 2(Loss) | true |
