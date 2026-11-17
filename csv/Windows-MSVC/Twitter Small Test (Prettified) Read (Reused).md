
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1955.33 | 0.106414 | 204.274ms | 3808 | 4890 | 19101.2 | 1857.28 | 0.12292 | 1.53802 | 1(Win) | true |
| Glaze | 1935.72 | 0.149532 | 204.934ms | 3808 | 2560 | 20147.3 | 1876.09 | 0.196103 | 1.55425 | 2(Loss) | true |
| simdjson (ondemand) | 1847.77 | 0.109522 | 211.859ms | 3808 | 2560 | 11861.5 | 1965.39 | 0.12704 | 1.62909 | 3(Loss) | true |
| Jsonifier | 1778.8 | 0.108487 | 224.681ms | 3808 | 4890 | 23988.5 | 2041.6 | 0.0232715 | 1.69113 | 4(Loss) | true |
