
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5745.83 | 0.0506628 | 3072.03ms | 183677 | 4890 | 1.16652e+06 | 30486.1 | 0.275865 | 0.528488 | 1(Win) | true |
| simdjson (ondemand) | 5253.4 | 0.167435 | 3373.38ms | 183677 | 160 | 498703 | 33343.8 | 0.0187477 | 0.578134 | 2(Loss) | true |
