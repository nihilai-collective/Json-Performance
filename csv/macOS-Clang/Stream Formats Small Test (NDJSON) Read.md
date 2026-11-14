
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2419.75 | 0.437268 | 9559.93ms | 16002592 | 40 | 3.04223e+10 | 6.30695e+06 | 2.98517 | 1(Win) | true |
| simdjson (ondemand) | 2174.63 | 0.101275 | 10822ms | 16002592 | 30 | 1.51543e+09 | 7.01788e+06 | 0.875836 | 2(Loss) | true |
