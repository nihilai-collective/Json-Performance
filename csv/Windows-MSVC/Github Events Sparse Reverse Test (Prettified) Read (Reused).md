
----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5169.61 | 0.180561 | 1255.36ms | 65103 | 80 | 37620.3 | 12010 | 0.062409 | 0.586752 | 1(Win) | true |
| simdjson (ondemand) | 3944.47 | 0.0524149 | 1620.27ms | 65103 | 4890 | 332846 | 15740.3 | 0.0384996 | 0.769314 | 2(Loss) | true |
