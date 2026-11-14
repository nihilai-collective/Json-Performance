
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 632.417 | 0.313977 | 256.06ms | 1691 | 40 | 2564.1 | 2550 | 0.262123 | 4.75266 | 1(Win) | true |
| simdjson (ondemand) | 492.203 | 0.0960223 | 331.847ms | 1691 | 4890 | 48400.8 | 3276.42 | 0.289605 | 6.14097 | 2(Loss) | true |
