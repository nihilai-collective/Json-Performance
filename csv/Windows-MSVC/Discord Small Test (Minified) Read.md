
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 759.636 | 0.122009 | 612.314ms | 4857 | 1280 | 70846.7 | 6097.66 | 0.29127 | 3.98466 | 1(Win) | true |
| simdjson (ondemand) | 751.062 | 0.238764 | 622.106ms | 4857 | 1280 | 277544 | 6167.27 | 0.992073 | 4.03243 | 2(Loss) | true |
