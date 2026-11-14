
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 440.288 | 0.107571 | 951.598ms | 4390 | 4890 | 511627 | 9508.85 | 0.153943 | 6.8884 | 1(Win) | true |
| simdjson (ondemand) | 427.042 | 0.0975158 | 987.256ms | 4390 | 2560 | 233979 | 9803.79 | 0.0521688 | 7.1025 | 2(Loss) | true |
