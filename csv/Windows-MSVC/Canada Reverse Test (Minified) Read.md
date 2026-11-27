
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 389.479 | 0.683162 | 7780.36ms | 2090234 | 40 | 4.89022e+10 | 5.11812e+06 | 0.329856 | 7.80318 | 1(Win) | true |
| simdjson (ondemand) | 379.004 | 0.628758 | 8000.51ms | 2090234 | 40 | 4.37451e+10 | 5.25958e+06 | 0.520763 | 8.01884 | 2(Loss) | true |
