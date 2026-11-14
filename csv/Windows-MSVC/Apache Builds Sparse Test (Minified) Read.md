
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1216.34 | 0.485511 | 7485.29ms | 94653 | 640 | 8.30881e+07 | 74213.1 | 0.209718 | 2.03461 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1212.67 | 0.712291 | 7825.25ms | 94653 | 40 | 1.1245e+07 | 74437.5 | 0.0481157 | 2.04104 | 1(Tie) | true |
