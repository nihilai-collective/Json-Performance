
----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11027.4 | 0.0775526 | 5746.2ms | 5212421 | 320 | 3.91089e+07 | 450782 | 0.371852 | 0.275564 | 1(Win) | true |
| simdjson (ondemand) | 8372.04 | 0.204267 | 7485.53ms | 5212421 | 30 | 4.41301e+07 | 593757 | 0.0741594 | 0.362972 | 2(Loss) | true |
