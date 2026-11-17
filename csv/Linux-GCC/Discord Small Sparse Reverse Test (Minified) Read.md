
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2951.7 | 0.0657964 | 878.281ms | 4857 | 4890 | 5213.2 | 1569.26 | 0.0609712 | 1.78668 | 7.50525 | 1.32592 | 0.00044727 | 3.322e-05 | 1.77679e-05 | 1(Win) | true |
| simdjson (ondemand) | 2268.02 | 0.0901665 | 920.753ms | 4857 | 160 | 542.566 | 2042.31 | 0.0339805 | 2.31485 | 10.2399 | 1.70764 | 0.00179766 | 2.57361e-05 | 0 | 2(Loss) | true |
