
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 919.649 | 0.0543259 | 1268.19ms | 4926 | 1280 | 9857.56 | 5108.26 | 0.0324583 | 5.64269 | 24.8238 | 4.93037 | 0.00962289 | 7.18445e-05 | 1.77629e-05 | 1(Win) | true |
| simdjson (ondemand) | 541.334 | 0.0332363 | 1624.61ms | 4926 | 2560 | 21297.3 | 8678.19 | 0.12095 | 9.55254 | 42.8547 | 8.53776 | 0.0202399 | 3.91735e-05 | 3.88563e-06 | 2(Loss) | true |
