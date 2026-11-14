
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 557.409 | 0.523529 | 5307.19ms | 4203059 | 40 | 5.66924e+10 | 7.19103e+06 | 0.745996 | 1(Win) | true |
| simdjson (ondemand) | 481.69 | 0.628771 | 6082.68ms | 4203059 | 30 | 8.213e+10 | 8.32143e+06 | 0.184204 | 2(Loss) | true |
