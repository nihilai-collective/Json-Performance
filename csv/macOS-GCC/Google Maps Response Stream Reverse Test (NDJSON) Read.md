
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 620.769 | 0.576937 | 10419ms | 4203059 | 30 | 4.16341e+10 | 6.45707e+06 | 1.47535 | 1(Win) | true |
| simdjson (ondemand) | 497.256 | 0.726509 | 5860.87ms | 4203059 | 30 | 1.02891e+11 | 8.06095e+06 | 1.1857 | 2(Loss) | true |
