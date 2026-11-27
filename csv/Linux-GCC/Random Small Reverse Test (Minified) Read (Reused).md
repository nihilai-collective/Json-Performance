
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 985.403 | 0.043419 | 1237.99ms | 4926 | 1280 | 5484.43 | 4767.39 | 0.0110955 | 5.26997 | 23.9896 | 4.70443 | 0.00973628 | 5.99498e-05 | 2.61685e-05 | 1(Win) | true |
| simdjson (ondemand) | 502.485 | 0.0821404 | 1702.08ms | 4926 | 640 | 37743 | 9349.14 | 0.0379737 | 10.2453 | 42.8488 | 8.50345 | 0.0269323 | 4.69448e-05 | 1.26878e-05 | 2(Loss) | true |
