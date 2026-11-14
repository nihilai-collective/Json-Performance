
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5472.11 | 0.356111 | 1917.68ms | 108313 | 4890 | 2.20968e+07 | 18876.7 | 0.529711 | 1(Win) | true |
| simdjson (stage-1) | 5105.84 | 0.387717 | 2127.91ms | 108313 | 2560 | 1.57505e+07 | 20230.8 | 0.408589 | 2(Loss) | true |
