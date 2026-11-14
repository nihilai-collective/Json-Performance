
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2175.07 | 0.0842642 | 1119.76ms | 25388 | 4890 | 430235 | 11131.6 | 0.145843 | 1.39456 | 1(Win) | true |
| simdjson (ondemand) | 2041.3 | 0.148988 | 1198.93ms | 25388 | 1280 | 399722 | 11861 | 0.116449 | 1.48557 | 2(Loss) | true |
