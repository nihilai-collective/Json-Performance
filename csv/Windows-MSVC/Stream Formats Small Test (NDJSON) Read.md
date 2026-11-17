
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3049.35 | 0.0472201 | 7523.02ms | 16002592 | 40 | 2.23398e+08 | 5.00476e+06 | 0.125922 | 0.996692 | 1(Win) | true |
| simdjson (ondemand) | 2778.29 | 0.0887852 | 8252.49ms | 16002592 | 40 | 9.51408e+08 | 5.49304e+06 | 0.66087 | 1.09383 | 2(Loss) | true |
