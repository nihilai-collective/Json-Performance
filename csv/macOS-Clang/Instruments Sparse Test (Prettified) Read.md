
----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4283.27 | 0.0595104 | 4124.71ms | 183677 | 2560 | 1.5163e+06 | 40895.9 | 0.0513006 | 1(Win) | true |
| simdjson (ondemand) | 4157.06 | 0.159752 | 4390.44ms | 183677 | 40 | 181254 | 42137.4 | 0.0129355 | 2(Loss) | true |
