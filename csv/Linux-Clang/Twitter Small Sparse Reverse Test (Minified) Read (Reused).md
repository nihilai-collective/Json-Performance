
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4137.61 | 0.0454137 | 780.23ms | 2821 | 2560 | 223.214 | 650.209 | 0.0563203 | 1.32077 | 5.35449 | 0.85041 | 0.000710907 | 2.38169e-05 | 7.06199e-06 | 1(Win) | true |
| simdjson (ondemand) | 3895.73 | 0.0799099 | 783.761ms | 2821 | 4890 | 1489.15 | 690.581 | 0.0437173 | 1.39907 | 6.17193 | 0.882312 | 0.000825028 | 3.11714e-05 | 1.44983e-06 | 2(Loss) | true |
