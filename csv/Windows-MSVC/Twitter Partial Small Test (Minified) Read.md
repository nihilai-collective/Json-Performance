
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5207.64 | 0.48051 | 56.9153ms | 2889 | 320 | 2068.08 | 529.062 | 0.294464 | 0.449367 | 1(Win) | true |
| Jsonifier (two-stage) | 5089.82 | 0.399951 | 57.3778ms | 2889 | 4890 | 22919.9 | 541.309 | 0.249621 | 0.460963 | 2(Loss) | true |
| Glaze | 2877.46 | 0.580866 | 100.828ms | 2889 | 80 | 2474.68 | 957.5 | 0.789474 | 0.842004 | 3(Loss) | true |
| simdjson (ondemand) | 2774.24 | 0.179632 | 104.333ms | 2889 | 320 | 1018.42 | 993.125 | 0 | 0.86698 | 4(Loss) | true |
