
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1804.05 | 0.0602438 | 958.577ms | 4390 | 2560 | 5003.77 | 2320.69 | 0.0632158 | 2.89977 | 13.4688 | 2.51298 | 0.00336409 | 4.71597e-05 | 1.98427e-05 | 1(Win) | true |
| simdjson (ondemand) | 1674.39 | 0.195743 | 972.367ms | 4390 | 320 | 7665.46 | 2500.4 | 0.109978 | 3.12242 | 14.1772 | 2.31595 | 0.00353716 | 3.48804e-05 | 1.13895e-05 | 2(Loss) | true |
