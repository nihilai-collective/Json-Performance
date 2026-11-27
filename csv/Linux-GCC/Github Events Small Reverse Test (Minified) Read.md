
----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 922.638 | 0.0558628 | 893.701ms | 1691 | 640 | 610.169 | 1747.88 | 0.0498172 | 5.71152 | 20.3761 | 3.99645 | 0.00255119 | 0.000126589 | 5.26685e-05 | 1(Win) | true |
| simdjson (ondemand) | 699.621 | 0.0442605 | 952.392ms | 1691 | 640 | 666.154 | 2305.05 | 0.0524387 | 7.48817 | 27.7037 | 5.41277 | 0.00550894 | 0.000112729 | 2.77203e-05 | 2(Loss) | true |
