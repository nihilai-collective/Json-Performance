
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 828.204 | 0.0551147 | 1249.15ms | 4390 | 1280 | 9935.73 | 5055.07 | 0.0736962 | 6.26349 | 28.2592 | 5.62756 | 0.0101915 | 3.57702e-05 | 1.60165e-06 | 1(Win) | true |
| simdjson (ondemand) | 730.99 | 0.0354759 | 1313.52ms | 4390 | 1280 | 5284.24 | 5727.34 | 0.0863793 | 7.09408 | 31.7989 | 5.78201 | 0.00954816 | 3.87956e-05 | 4.09311e-06 | 2(Loss) | true |
