
----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5458.11 | 0.132814 | 5971.62ms | 5212421 | 40 | 5.85247e+07 | 910746 | 0.454227 | 1(Win) | true |
| simdjson (ondemand) | 4953.61 | 0.110862 | 6909.91ms | 5212421 | 40 | 4.95062e+07 | 1.0035e+06 | 0.145412 | 2(Loss) | true |
