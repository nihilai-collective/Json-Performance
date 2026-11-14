
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2479.77 | 0.148924 | 67.3414ms | 1691 | 4890 | 4586.72 | 650.327 | 0.0217615 | 1.19111 | 1(Win) | true |
| simdjson (ondemand) | 1942.35 | 0.126856 | 85.6022ms | 1691 | 4890 | 5424.56 | 830.266 | 0.0808305 | 1.53072 | 2(Loss) | true |
