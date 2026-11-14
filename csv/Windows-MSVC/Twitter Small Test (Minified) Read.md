
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1396.36 | 0.426216 | 200.087ms | 2821 | 30 | 2022.99 | 1926.67 | 0 | 2.16017 | 1(Win) | true |
| simdjson (ondemand) | 1228.45 | 0.219354 | 222.342ms | 2821 | 40 | 923.077 | 2190 | 0 | 2.43239 | 2(Loss) | true |
