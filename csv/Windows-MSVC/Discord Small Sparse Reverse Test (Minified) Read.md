
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1987.37 | 0.0924945 | 235.238ms | 4857 | 4890 | 22725.8 | 2330.72 | 0.33354 | 1.51691 | 1(Win) | true |
| simdjson (ondemand) | 1448.7 | 0.990129 | 352.551ms | 4857 | 1280 | 1.28284e+06 | 3197.34 | 0.446692 | 2.08599 | 2(Loss) | true |
