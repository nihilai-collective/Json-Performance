
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1194.52 | 0.0817414 | 2040.25ms | 25388 | 2560 | 702743 | 20269.2 | 0.138934 | 1(Win) | true |
| simdjson (ondemand) | 973.522 | 0.112436 | 2503.94ms | 25388 | 1280 | 1.00088e+06 | 24870.4 | 0.0899859 | 2(Loss) | true |
