
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5365 | 0.210206 | 1175.77ms | 65103 | 4890 | 2.89375e+06 | 11572.6 | 0.150013 | 1(Win) | true |
| simdjson (ondemand) | 4856.01 | 0.260462 | 1380.41ms | 65103 | 160 | 177439 | 12785.6 | 0.0876754 | 2(Loss) | true |
