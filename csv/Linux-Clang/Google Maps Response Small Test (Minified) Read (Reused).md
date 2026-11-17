
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1430.2 | 0.0510998 | 1038.74ms | 4390 | 320 | 716.018 | 2927.3 | 0.0573595 | 3.65229 | 16.5267 | 3.17084 | 0.00269433 | 4.1287e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1170.97 | 0.0244166 | 1097.29ms | 4390 | 4890 | 3726.6 | 3575.34 | 0.0352137 | 4.44696 | 19.1638 | 3.25034 | 0.00240419 | 3.40055e-05 | 5.40362e-06 | 2(Loss) | true |
