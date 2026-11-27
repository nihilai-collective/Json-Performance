
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 571.866 | 0.331507 | 874.535ms | 5092 | 4890 | 3.87509e+06 | 8491.7 | 0.477203 | 5.30119 | 1(Win) | true |
| simdjson (ondemand) | 523.457 | 0.0704764 | 927.471ms | 5092 | 2560 | 109431 | 9276.99 | 0.219859 | 5.79129 | 2(Loss) | true |
