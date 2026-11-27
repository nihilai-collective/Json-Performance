
----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1070.34 | 0.0764705 | 456.21ms | 4926 | 4890 | 55086.3 | 4389.08 | 0.108069 | 2.82794 | 1(Win) | true |
| simdjson (ondemand) | 893.118 | 1.74531 | 549.64ms | 4926 | 160 | 1.34845e+06 | 5260 | 0.0475059 | 3.39371 | 2(Loss) | true |
