
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 657.853 | 0.0806158 | 719.012ms | 4926 | 4890 | 162061 | 7141.1 | 0.311223 | 4.60604 | 1(Win) | true |
| simdjson (ondemand) | 591.467 | 0.0809818 | 796.338ms | 4926 | 4890 | 202307 | 7942.62 | 0.0546256 | 5.12438 | 2(Loss) | true |
