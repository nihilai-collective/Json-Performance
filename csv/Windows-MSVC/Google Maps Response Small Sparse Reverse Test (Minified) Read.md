
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1152.3 | 0.187706 | 367.867ms | 4390 | 640 | 29767 | 3633.28 | 0.141716 | 2.6237 | 1(Win) | true |
| simdjson (ondemand) | 1048.62 | 0.165062 | 400.623ms | 4390 | 40 | 1737.18 | 3992.5 | 0.146321 | 2.87486 | 2(Loss) | true |
