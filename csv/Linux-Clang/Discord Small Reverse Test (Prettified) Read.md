
----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.988 | 0.0535394 | 1432ms | 6701 | 640 | 9168.12 | 7069.31 | 0.032414 | 5.73259 | 23.6257 | 4.73347 | 0.00554348 | 2.37838e-05 | 2.56492e-06 | 1(Win) | true |
| simdjson (ondemand) | 314.846 | 0.0313846 | 2750.64ms | 6701 | 1280 | 51943 | 20297.5 | 0.00864561 | 16.3583 | 83.9096 | 16.1249 | 0.0329071 | 5.26974e-05 | 1.4107e-05 | 2(Loss) | true |
