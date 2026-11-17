
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7282.72 | 0.113634 | 776.469ms | 4630 | 160 | 75.9472 | 606.3 | 0.0164908 | 0.754332 | 3.56566 | 0.463715 | 0.000433315 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6530.21 | 0.0508742 | 781.517ms | 4630 | 640 | 75.7326 | 676.167 | 0.0358049 | 0.837685 | 4.11512 | 0.492009 | 0.000431965 | 9.11177e-06 | 0 | 2(Loss) | true |
