
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2004.29 | 0.059615 | 961.488ms | 4926 | 320 | 624.783 | 2343.87 | 0.0425492 | 2.61466 | 11.7343 | 2.14576 | 0.00493681 | 2.47412e-05 | 6.97828e-06 | 1(Win) | true |
| simdjson (ondemand) | 1560.78 | 0.0336645 | 1032.61ms | 4926 | 2560 | 2628.39 | 3009.9 | 0.029192 | 3.34685 | 13.393 | 2.34998 | 0.00732688 | 4.87687e-05 | 1.57804e-05 | 2(Loss) | true |
