
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2304.09 | 0.0423251 | 901.169ms | 4390 | 4890 | 2892.26 | 1817.05 | 0.019842 | 2.28587 | 10.3913 | 1.80091 | 0.00225196 | 3.69868e-05 | 1.3183e-05 | 1(Win) | true |
| simdjson (ondemand) | 1950.45 | 0.04453 | 934.029ms | 4390 | 320 | 292.357 | 2146.49 | 0.0664888 | 2.68991 | 11.2506 | 1.85376 | 0.00256193 | 2.56264e-05 | 0 | 2(Loss) | true |
