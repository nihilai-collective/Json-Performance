
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3007.97 | 0.0535136 | 156.786ms | 4857 | 640 | 434.608 | 1539.91 | 0.377865 | 1(Win) | true |
| simdjson (ondemand) | 2500.44 | 0.0788737 | 185.304ms | 4857 | 320 | 683.153 | 1852.47 | 0.288475 | 2(Loss) | true |
