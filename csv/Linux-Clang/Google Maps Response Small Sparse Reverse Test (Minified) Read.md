
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1718.89 | 0.0610025 | 966.693ms | 4390 | 2560 | 5651.54 | 2435.65 | 0.0853778 | 3.0203 | 13.8132 | 2.59339 | 0.0037161 | 3.90625e-05 | 1.49487e-05 | 1(Win) | true |
| simdjson (ondemand) | 1634.3 | 0.121022 | 978.233ms | 4390 | 40 | 384.461 | 2561.72 | 0.00227716 | 3.20373 | 14.4604 | 2.38451 | 0.00345103 | 3.41686e-05 | 1.13895e-05 | 2(Loss) | true |
