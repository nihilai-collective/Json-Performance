
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4645.66 | 0.105986 | 166.158ms | 7932 | 4890 | 14563.9 | 1628.3 | 0.326276 | 0.646959 | 1(Win) | true |
| simdjson (ondemand) | 3703 | 0.280156 | 209.517ms | 7932 | 320 | 10481.1 | 2042.81 | 0.0765462 | 0.812219 | 2(Loss) | true |
