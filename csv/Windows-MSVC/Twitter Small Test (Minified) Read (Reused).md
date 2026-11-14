
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.36 | 0.246565 | 187.572ms | 2821 | 4890 | 85826.6 | 1699.12 | 0.353961 | 1.89836 | 1(Win) | true |
| simdjson (ondemand) | 1348.32 | 0.0970734 | 218.391ms | 2821 | 320 | 1200.53 | 1995.31 | 0.607098 | 2.23533 | 2(Loss) | true |
