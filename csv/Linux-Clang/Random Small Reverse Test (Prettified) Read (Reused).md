
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.35 | 0.0780182 | 1337.88ms | 8150 | 320 | 6501.05 | 5777.25 | 0.00129818 | 3.85474 | 16.0353 | 3.15865 | 0.00625422 | 2.76074e-05 | 2.68405e-06 | 1(Win) | true |
| simdjson (ondemand) | 820.222 | 0.0580916 | 1715.01ms | 8150 | 640 | 19393.6 | 9476.02 | 0.151403 | 6.30379 | 28.373 | 5.0389 | 0.0141493 | 2.31979e-05 | 2.87577e-06 | 2(Loss) | true |
