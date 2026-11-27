
----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5439.15 | 0.295658 | 969.292ms | 53331 | 640 | 489166 | 9350.8 | 0.0470327 | 1(Win) | true |
| simdjson (ondemand) | 3924.77 | 0.103367 | 1307.12ms | 53331 | 4890 | 877418 | 12958.8 | 0.0799188 | 2(Loss) | true |
