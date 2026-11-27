
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 521.402 | 0.858333 | 5779.48ms | 4203059 | 30 | 1.30623e+11 | 7.68763e+06 | 2.34149 | 5.82876 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 459.933 | 0.646773 | 6202.52ms | 4203059 | 30 | 9.53163e+10 | 8.71507e+06 | 4.45578 | 6.60793 | -(Loss) | false |
