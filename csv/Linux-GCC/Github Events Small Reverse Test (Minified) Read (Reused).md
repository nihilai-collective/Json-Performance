
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1056 | 0.105139 | 882.798ms | 1691 | 1280 | 3299.88 | 1527.14 | 0.00434821 | 4.99736 | 18.8705 | 3.61916 | 0.00183924 | 0.000144145 | 4.80485e-05 | 1(Win) | true |
| simdjson (ondemand) | 773.94 | 0.0399254 | 938.417ms | 1691 | 640 | 442.947 | 2083.7 | 0.0895288 | 6.78672 | 26.1898 | 5.0343 | 0.00434931 | 0.000112729 | 2.95683e-05 | 2(Loss) | true |
