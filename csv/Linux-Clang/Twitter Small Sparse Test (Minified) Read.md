
----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5732.11 | 0.0540991 | 759.748ms | 2821 | 4890 | 315.258 | 469.341 | 0.0442327 | 0.973819 | 3.72847 | 0.511521 | 0.000397037 | 2.92866e-05 | 5.65435e-06 | 1(Win) | true |
| simdjson (ondemand) | 5464.57 | 0.0842791 | 760.635ms | 2821 | 2560 | 440.732 | 492.32 | 0.214529 | 1.02178 | 3.99646 | 0.449132 | 0.000521203 | 1.93859e-05 | 2.90788e-06 | 2(Loss) | true |
