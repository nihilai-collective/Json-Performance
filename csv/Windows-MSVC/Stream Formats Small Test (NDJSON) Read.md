
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3331.03 | 0.262739 | 6905.14ms | 16002592 | 40 | 5.79607e+09 | 4.58154e+06 | 0.348608 | 0.743231 | 1(Win) | true |
| simdjson (ondemand) | 2439.97 | 1.08256 | 9375.92ms | 16002592 | 80 | 3.66777e+11 | 6.25468e+06 | 2.05978 | 1.01465 | 2(Loss) | true |
