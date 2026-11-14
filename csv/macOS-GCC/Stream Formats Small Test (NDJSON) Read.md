
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2081.88 | 1.53897 | 10868.6ms | 16002592 | 30 | 3.81814e+11 | 7.33051e+06 | 1.26331 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 1855.34 | 1.25565 | 5248.17ms | 16002592 | 40 | 4.26709e+11 | 8.22557e+06 | 7.5586 | -(Loss) | false |
