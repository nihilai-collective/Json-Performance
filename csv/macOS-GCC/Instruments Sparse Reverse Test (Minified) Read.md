
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2469.48 | 0.186256 | 4297.27ms | 108313 | 320 | 1.94233e+06 | 41828.8 | 0.110805 | 1(Win) | true |
| simdjson (ondemand) | 1983.95 | 0.143966 | 5354.56ms | 108313 | 320 | 1.79792e+06 | 52065.6 | 0.0338149 | 2(Loss) | true |
