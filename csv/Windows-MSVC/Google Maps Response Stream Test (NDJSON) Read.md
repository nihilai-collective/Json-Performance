
----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 719.677 | 0.746725 | 9266.88ms | 4203059 | 80 | 1.38378e+11 | 5.56965e+06 | 1.72942 | 4.2229 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 552.901 | 1.16311 | 5517.91ms | 4203059 | 40 | 2.84407e+11 | 7.24966e+06 | 5.37205 | 5.49674 | -(Loss) | false |
