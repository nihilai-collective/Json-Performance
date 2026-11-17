
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1083.11 | 0.092267 | 151.926ms | 1691 | 4890 | 9228.73 | 1488.92 | 0.216263 | 2.77084 | 1(Win) | true |
| Glaze | 1075.64 | 0.138308 | 153.208ms | 1691 | 4890 | 21026.3 | 1499.26 | 0.136068 | 2.7927 | 2(Loss) | true |
| Jsonifier (two-stage) | 923.097 | 0.0790721 | 177.998ms | 1691 | 4890 | 9331.44 | 1747.01 | 0.0728703 | 3.25759 | 3(Loss) | true |
| simdjson (ondemand) | 679.704 | 0.080904 | 239.929ms | 1691 | 4890 | 18017.6 | 2372.6 | 0.284791 | 4.43662 | 4(Loss) | true |
