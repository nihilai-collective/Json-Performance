
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 428.441 | 4.43526 | 7347.24ms | 4203059 | 30 | 5.16546e+12 | 9.35567e+06 | 3.17418 | 5.77853 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 389.167 | 4.03421 | 7927.22ms | 4203059 | 30 | 5.17962e+12 | 1.02998e+07 | 1.02148 | 6.36162 | 1(Tie) | true |
