
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1847.91 | 0.0254513 | 1335.77ms | 11812 | 4890 | 11771 | 6095.97 | 0.00110426 | 2.80375 | 13.4944 | 2.54055 | 0.00674519 | 1.68107e-05 | 2.80468e-06 | 1(Win) | true |
| simdjson (ondemand) | 1679.88 | 0.026338 | 1399.06ms | 11812 | 2560 | 7985.35 | 6705.72 | 0.0176591 | 3.08459 | 13.7803 | 2.38859 | 0.00744899 | 3.31694e-05 | 1.03179e-05 | 2(Loss) | true |
