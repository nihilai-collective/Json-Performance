
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11039.3 | 0.240967 | 5745.47ms | 5212421 | 30 | 3.5321e+07 | 450297 | 0.413564 | 0.275224 | 1(Win) | true |
| simdjson (ondemand) | 8499.21 | 0.0864152 | 7434.91ms | 5212421 | 320 | 8.17433e+07 | 584872 | 0.0785345 | 0.357488 | 2(Loss) | true |
