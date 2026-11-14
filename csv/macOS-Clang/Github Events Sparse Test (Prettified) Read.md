
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5091.32 | 0.0517787 | 1388.03ms | 65103 | 80 | 3189.58 | 12194.7 | 0.248367 | 1(Win) | true |
| simdjson (ondemand) | 4444.18 | 0.484946 | 1457.17ms | 65103 | 320 | 1.46878e+06 | 13970.4 | 0.00865592 | 2(Loss) | true |
