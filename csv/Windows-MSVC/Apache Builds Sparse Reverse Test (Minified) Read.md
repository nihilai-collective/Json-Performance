
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1166.52 | 0.15415 | 7744.72ms | 94653 | 4890 | 6.95796e+07 | 77382.4 | 0.107094 | 2.60449 | 1(Win) | true |
| simdjson (ondemand) | 1014.7 | 0.147458 | 8875.28ms | 94653 | 4890 | 8.41476e+07 | 88960.6 | 0.0131423 | 2.99438 | 2(Loss) | true |
