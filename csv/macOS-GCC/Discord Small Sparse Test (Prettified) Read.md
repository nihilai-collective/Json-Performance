
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2903.62 | 0.45367 | 219.823ms | 6701 | 2560 | 255224 | 2200.9 | 0.0227231 | 1(Win) | true |
| simdjson (ondemand) | 2562.48 | 0.426373 | 247.302ms | 6701 | 2560 | 289453 | 2493.9 | 0.479452 | 2(Loss) | true |
