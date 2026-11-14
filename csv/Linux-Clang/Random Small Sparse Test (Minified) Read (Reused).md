
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2754.59 | 0.112183 | 896.893ms | 4926 | 640 | 2342.68 | 1705.45 | 0.00531357 | 1.91353 | 8.32318 | 1.51786 | 0.00286236 | 2.69615e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2331.29 | 0.0385093 | 928.071ms | 4926 | 4890 | 2944.68 | 2015.11 | 0.0318467 | 2.25725 | 9.67053 | 1.47848 | 0.00138923 | 2.60294e-05 | 2.40782e-06 | 2(Loss) | true |
